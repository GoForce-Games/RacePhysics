#include "EntityManager.h"

EntityManager::EntityManager(Application* parent, bool start_enabled) : Module(parent, start_enabled)
{
}

EntityManager::~EntityManager()
{
}

bool EntityManager::Init()
{
	return true;
}

bool EntityManager::Start()
{
	return true;
}

update_status EntityManager::PreUpdate(float dt)
{
	return update_status::UPDATE_CONTINUE;
}

update_status EntityManager::Update(float dt)
{
	for (p2List_item<Entity*>* item = entities.getFirst(); item ; item=item->next)
	{
		if (item->data) item->data->Update(dt);
	}
	return update_status::UPDATE_CONTINUE;
}

update_status EntityManager::PostUpdate(float dt)
{
	return update_status::UPDATE_CONTINUE;
}

bool EntityManager::CleanUp()
{
	cleaning_up = true;

	for (p2List_item<Entity*>* item = entities.getFirst(); item; item=item->next)
	{
		delete item->data;
	}
	entities.clear();

	cleaning_up = false;
	return true;
}

bool EntityManager::AddEntity(Entity* entity)
{
	if (entity) {
		return entities+=entity;
	}
	return false;
}

void EntityManager::RemoveEntity(Entity* entity)
{
	if (!cleaning_up)
		entities-=entity;
}
