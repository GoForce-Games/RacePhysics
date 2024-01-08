#include "Entity.h"
#include "Application.h"
#include "ModulePhysics3D.h"
#include "PhysBody3D.h"

Entity::Entity(EntityType type, Application* application, bool start_enabled) : eType(type), App(application)
{
	App->entities->AddEntity(this);
}

Entity::~Entity()
{
	Entity::CleanUp();
}

bool Entity::CleanUp()
{
	if (pbody) {
		delete pbody;
		pbody = nullptr;
	}
	App->entities->RemoveEntity(this);
	return true;
}
