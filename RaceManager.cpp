#include "RaceManager.h"
#include "CheckPoint.h"

RaceManager::RaceManager(Application* parent, bool start_enabled)
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
