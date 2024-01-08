#pragma once
#include "Module.h"
#include "p2List.h"
#include "Entity.h"
class EntityManager :
    public Module
{
public:

	EntityManager(Application* parent, bool start_enabled = true);
	~EntityManager();

	bool Init();

	bool Start();

	update_status PreUpdate(float dt);

	update_status Update(float dt);

	update_status PostUpdate(float dt);

	bool CleanUp();

	bool AddEntity(Entity* type);

	void RemoveEntity(Entity* entity);

private:

	p2List<Entity*> entities;

	bool cleaning_up = false;

};

