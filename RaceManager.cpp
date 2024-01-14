#include "RaceManager.h"
#include "CheckPoint.h"

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
