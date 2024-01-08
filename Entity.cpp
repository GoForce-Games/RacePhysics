#include "Entity.h"
#include "Application.h"
#include "ModulePhysics3D.h"
#include "PhysBody3D.h"

Entity::Entity(EntityType type, Application* application, bool start_enabled) : eType(type), App(application)
{
}

Entity::~Entity()
{
	CleanUp();
	App->entities->RemoveEntity(this);
}

bool Entity::CleanUp()
{
	if (pbody) {
		delete pbody;
		pbody = nullptr;
	}
	return true;
}
