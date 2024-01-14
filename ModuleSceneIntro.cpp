#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	musicaFondoFx = App->audio->LoadFx("Assets/musicafondo.wav");
	App->audio->PlayFx(musicaFondoFx);
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));


	// Create sensor cube (will trigger with car)
	sensor_cube = App->physics->AddBody(Cube(5, 5, 5), 0.0);
	sensor_cube->SetAsSensor(true);
	sensor_cube->SetPos(0, 3, 0);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{

	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	Cube suelo(400, 0, 400);
	suelo.Render();

	Cube c(40, 30, 135);
	c.SetPos(-31, 15, -37.5);
	c.Render();

	Cube c1(20, 30, 60);
	c1.SetPos(20, 15, 30);
	c1.Render();

	Cube c2(100, 30, 20);
	c2.SetPos(-35, 15, 70);
	c2.Render();

	Cube c3(80, 30, 100);
	c3.SetPos(-125, 15, 15);
	c3.Render();

	Cube c4(90, 30, 40);
	c4.SetPos(-96, 15, -85);
	c4.Render();

	Cube c5(40, 30, 90);
	c5.SetPos(-185, 15, -80);
	c5.Render();

	Cube c6(150, 30, 30);
	c6.SetPos(-90, 15, -138);
	c6.Render();

	Cube c7(80, 30, 80);
	c7.SetPos(29, 15, -65);
	c7.Render();

	Cube c8(70, 30, 80);
	c8.SetPos(35, 15, -145);
	c8.Render();

	Cube c9(140, 30, 30);
	c9.SetPos(35, 15, -215);
	c9.Render();

	Cube c10(10, 30, 49);
	c10.SetPos(-20, 15, -175);
	c10.Render();

	Cube c12(40, 30, 100);
	c12.SetPos(125, 15, -159);
	c12.Render();

	Cube c13(20, 30, 140);
	c13.SetPos(58, 15, 45);
	c13.Render();

	Cube c14(10, 30, 140);
	c14.SetPos(26, 15, 130);
	c14.Render();

	Cube c15(140, 30, 30);
	c15.SetPos(100, 15, 156);
	c15.Render();

	Cube c16(70, 30, 210);
	c16.SetPos(94, 15, 10);
	c16.Render();

	Cube c11(20, 30, 255);
	c11.SetPos(155, 15, 17);
	c11.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

