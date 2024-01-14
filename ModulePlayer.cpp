#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"
#include "ModuleSceneIntro.h"
#include "ModuleCamera3D.h"
#include "ModuleInput.h"
#include "ModulePhysics3D.h"
#include "RaceManager.h"
#include "RaceProgress.h"
#include "Checkpoint.h"
#include "ModuleAudio.h"
#include "PhysVehicle3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2.0f, 0.55f, 3.0f);
	car.chassis_offset.Set(0.0f, 0.5f, 0.0f);
	car.rear_wing_size.Set(1.7f, 0.05f, 0.5f);
	car.rear_wing_offset.Set(0.0f, 1.55f, -1.5f);
	car.vertical_wing_size.Set(0.05f, 0.5f, 0.5);
	car.vertical_wing_offset.Set(0.8f, 1.5f, -1.5f);
	car.person_size.Set(0.9f, 0.7f, 1.2f);
	car.person_offset.Set(0.0f, 1.5f, 0.0f);


	car.mass = 1000.0f;
	car.suspensionStiffness = 25.88f;
	car.suspensionCompression = 1.83f;
	car.suspensionDamping = 2.88f;
	car.maxSuspensionTravelCm = 500.0f;
	car.frictionSlip = 30.5f;
	car.maxSuspensionForce = 1500.0f;


	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float front_wheel_radius = 0.5f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	//float half_width = car.chassis_size.x*0.5f;
	//float half_length = car.chassis_size.z*0.5f;

	float half_width = car.chassis_size.x * 0.6;  // 0.5f
	float front_wheels = (car.chassis_size.z * 1.2) - 1.5;
	float rear_wheels = car.chassis_size.z * 0.6;

	vec3 direction(0, -1, 0);
	vec3 axis(-1, 0, 0);

	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, front_wheels - front_wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = front_wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, front_wheels - front_wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = front_wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -rear_wheels + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -rear_wheels + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->surface = (car.chassis_size.x * car.chassis_size.y * car.chassis_size.z) * 0.5;
	vehicle->SetPos(0, 12, 10);
	vehicle->collision_listeners.add(this); // Add this module as listener to callbacks from vehicle

	initial_gravity = vehicle->vehicle->getRigidBody()->getGravity();
	initial_scaling = vehicle->vehicle->getRigidBody()->getCollisionShape()->getLocalScaling();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

void ModulePlayer::ResetOrientation()
{
	btQuaternion q = vehicle->vehicle->getChassisWorldTransform().getRotation();
	q.setX(0);
	q.setZ(0);
	q.normalize();
	btTransform initialTransform = btTransform::getIdentity();
	initialTransform.setOrigin(vehicle->vehicle->getChassisWorldTransform().getOrigin());
	initialTransform.setRotation(q);
	mat4x4 m;
	initialTransform.getOpenGLMatrix(m.M);
	vehicle->SetTransform(m.M);
}

void ModulePlayer::BackToLastCp()
{
	if (raceData.current_checkpoint != nullptr) {
		Checkpoint* cp = nullptr;
		if (raceData.current_checkpoint->prev != nullptr && raceData.current_checkpoint->prev->data != nullptr)
			cp = raceData.current_checkpoint->prev->data;
		/*if (raceData.current_checkpoint != nullptr && raceData.current_checkpoint->data != nullptr)
			cp = raceData.current_checkpoint->data;*/
		else
			cp = App->race_manager->GetLastCheckpoint();

		mat4x4 m;
		cp->GetBody()->GetTransform(m.M);
		vehicle->SetTransform(m.M);
		vehicle->vehicle->getRigidBody()->clearForces();
	}
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	vec3 pos = vehicle->GetPos();
	if (pos.y < -500) {
		btRigidBody* rb = vehicle->vehicle->getRigidBody();
		btVector3 g = rb->getGravity();
		g.setY(g.y() - 1);
		rb->setGravity(g);
		btVector3 currentScale = vehicle->vehicle->getRigidBody()->getCollisionShape()->getLocalScaling();
		currentScale *= 0.8f;
		vehicle->vehicle->getRigidBody()->getCollisionShape()->setLocalScaling(currentScale);
		
		if (pos.y < -10000) {
			rb->setGravity(initial_gravity);
			vehicle->vehicle->getRigidBody()->getCollisionShape()->setLocalScaling(currentScale);
			BackToLastCp();
		}
	}


	//App->camera->LookAt(vehicle->GetPos().y);
	
	turn = acceleration = brake = 0.0f;
	
	App->camera->LookAt(vehicle->GetPos());

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		//App->camera->LookAt(vehicle->GetPos().x);
		acceleration = MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		acceleration = -MAX_ACCELERATION;
		brake = BRAKE_POWER;
	}

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) {
		ResetOrientation();
	}
	else if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) {
		BackToLastCp();
	}

	if (App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN) {
		vehicle->SetPos(0, -500, 0);
		vehicle->vehicle->getRigidBody()->clearForces();
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake); 

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h, checkpoint %i, lap %i/%i%s, mass %f", vehicle->GetKmh(), raceData.checkpoint_progress,raceData.laps+1,App->race_manager->max_laps,(raceData.finished? ", RACE FINISHED":"  "), 1 / vehicle->vehicle->getRigidBody()->getInvMass());
	App->window->SetTitle(title);

	DragForce();
	LiftForce();

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {

		vehicle->vehicle->getRigidBody()->setMassProps(2000, vehicle->vehicle->getRigidBody()->getLocalInertia());

	}
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {

		vehicle->vehicle->getRigidBody()->setMassProps(1000, vehicle->vehicle->getRigidBody()->getLocalInertia());
	}
	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {

		physicsEnabled = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN) {

		physicsEnabled = true;
	}
	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body2->bound_entity && body2->bound_entity->eType == EntityType::CHECKPOINT && raceData.current_checkpoint != nullptr) {
		Checkpoint* cp = (Checkpoint*)body2->bound_entity;
		if (cp && cp == raceData.current_checkpoint->data) {
			LOG("Next checkpoint");
			App->race_manager->CheckFinished(raceData);
		}
	}
	else {
		// Randomly teleport the sensor cube around 1st quadrant
		if (body1 == App->scene_intro->sensor_cube)	body1->SetPos(20 * rand() / RAND_MAX, 3, 20 * rand() / RAND_MAX);
		if (body2 == App->scene_intro->sensor_cube)	body2->SetPos(20 * rand() / RAND_MAX, 3, 20 * rand() / RAND_MAX);
	}
}

void ModulePlayer::DragForce() {
	if (physicsEnabled)
	{
		float vel = vehicle->GetKmh() * 0.2778; //en m/s
		float speed = vel;
		double fdrag = 0.5 * atmosphere.density * speed * speed * vehicle->surface * vehicle->cd;
		double fd = (-speed) * fdrag;
		acceleration += fd;

		const btMatrix3x3& t = vehicle->vehicle->getRigidBody()->getCenterOfMassTransform().getBasis();
		btRigidBody* rb = vehicle->vehicle->getRigidBody();
		rb->applyCentralForce(t.getColumn(vehicle->vehicle->getForwardAxis())*fd);
	}
}

void ModulePlayer::LiftForce() {
	if (physicsEnabled)
	{
		float vel = vehicle->GetKmh() *0.2778; //en m/s
		float speed = vel;
		double flift = 0.5 * atmosphere.density * speed * speed * vehicle->surface * vehicle->cl;
		double fl = speed * flift;
		acceleration += fl;

		const btMatrix3x3& t = vehicle->vehicle->getRigidBody()->getCenterOfMassTransform().getBasis();
		btRigidBody* rb = vehicle->vehicle->getRigidBody();
		rb->applyCentralForce(t.getColumn(vehicle->vehicle->getUpAxis()) * fl);
	}
}

