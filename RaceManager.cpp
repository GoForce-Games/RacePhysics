#include "RaceManager.h"
#include "CheckPoint.h"
#include "Entity.h"

#include "Application.h"
#include "PhysVehicle3D.h"

RaceManager::RaceManager(Application* parent, bool start_enabled) : Module(parent,start_enabled)
{
}

RaceManager::~RaceManager()
{
}

bool RaceManager::Init()
{
	


	return true;
}

bool RaceManager::Start()
{
	Checkpoint* inicio = new Checkpoint(App, btVector3(10, 10, 10)); // Tampoco se de que tamaño hay que hacerlos
	Checkpoint* cp1 = new Checkpoint(App, btVector3(10, 10, 10)); // Tampoco se de que tamaño hay que hacerlos
	Checkpoint* cp2 = new Checkpoint(App, btVector3(10, 10, 10)); // Tampoco se de que tamaño hay que hacerlos
	Checkpoint* cp3 = new Checkpoint(App, btVector3(10, 10, 10));
	Checkpoint* cp4 = new Checkpoint(App, btVector3(10, 10, 10));
	Checkpoint* cp5 = new Checkpoint(App, btVector3(10, 10, 10));
	Checkpoint* cp6 = new Checkpoint(App, btVector3(10, 10, 10));
	Checkpoint* cp7 = new Checkpoint(App, btVector3(10, 10, 10));
	Checkpoint* cp8 = new Checkpoint(App, btVector3(10, 10, 10));
	Checkpoint* cp9 = new Checkpoint(App, btVector3(10, 10, 10));
	Checkpoint* cp10 = new Checkpoint(App, btVector3(10, 10, 10));
	Checkpoint* cp11 = new Checkpoint(App, btVector3(10, 10, 10));
	Checkpoint* cp12 = new Checkpoint(App, btVector3(10, 10, 10));


	vec3 pos = App->player->vehicle->GetPos();
	inicio->SetPosition(btVector3(0, 0, 45));
	cp1->SetPosition(btVector3(-60, 0, 45));
	cp2->SetPosition(btVector3(-75, 0, -50));
	cp3->SetPosition(btVector3(-150, 0, -50));
	cp4->SetPosition(btVector3(-150, 0, -100));
	cp5->SetPosition(btVector3(-30, 0, -115));
	cp6->SetPosition(btVector3(-7, 0, -185));
	cp7->SetPosition(btVector3(85, 0, -180));
	cp8->SetPosition(btVector3(95, 0, -110));
	cp9->SetPosition(btVector3(135, 0, -90));
	cp10->SetPosition(btVector3(135, 0, 120));
	cp11->SetPosition(btVector3(45, 0, 120));
	cp12->SetPosition(btVector3(20, 0, -15));

	return true;
}

update_status RaceManager::PreUpdate(float dt)
{
	return update_status::UPDATE_CONTINUE;
}

update_status RaceManager::Update(float dt)
{
	return update_status::UPDATE_CONTINUE;
}

update_status RaceManager::PostUpdate(float dt)
{
	return update_status::UPDATE_CONTINUE;
}

bool RaceManager::CleanUp()
{
	return true;
}

//NOTE: Add checkpoints in the order you want them to be checked for proper lap tracking (proper lap tracking not implemented yet)
Checkpoint* RaceManager::AddCheckpoint(Checkpoint* cp)
{
	return (checkpoints+=cp)->data;
}

void RaceManager::RemoveCheckpoint(Checkpoint* cp)
{
	checkpoints -= cp;
}

void RaceManager::CheckFinished(RaceProgress& data)
{
	if (!data.finished && data.laps >= max_laps) {
		LOG("Player %s has finished the race!", data.name.GetString());
	}
	else if (data.currentCheckpoint != nullptr && data.currentCheckpoint->next == nullptr) {
		//End of lap reached
		data.currentCheckpoint = checkpoints.getFirst();
		data.laps++;
	}
}

RaceProgress RaceManager::CreatePlayer(SString name)
{
	RaceProgress ret;
	ret.name = name;
	ret.currentCheckpoint = checkpoints.getFirst();
	return ret;
}
