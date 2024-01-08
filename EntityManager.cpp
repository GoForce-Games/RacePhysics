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

Entity* EntityManager::AddEntity(EntityType type)
{
	Entity* entity = nullptr;

	switch (type)
	{
	case EntityType::CHECKPOINT:
		break;
	case EntityType::FINISH_LINE:
		break;
	case EntityType::UNKNOWN:
		break;
	default:
		break;
	}

	if (entity) {
		entities.add(entity);
	}

	return entity;
}

void EntityManager::RemoveEntity(Entity* entity)
{
	if (!cleaning_up)
	entities.del(entities.findNode(entity));
}
