#pragma once
#include "Bullet/include/btBulletCollisionCommon.h"

class Application;
struct PhysBody3D;

enum class EntityType {
	CHECKPOINT,
	FINISH_LINE,
	UNKNOWN
};

class Entity
{
public:
	Application* App;

	Entity(EntityType type, Application* application, bool start_enabled = true);
	~Entity();

	virtual bool Init() = 0;
	virtual bool Update(float dt) = 0;

	virtual bool CleanUp();

	virtual void OnCollision(PhysBody3D* bodyA, PhysBody3D* bodyB) {}

	virtual btVector3 GetPosition() { return position; }

	virtual btVector3 GetRotation() { return btVector3(0,0,0); }

public:

	EntityType eType;


private:

	btVector3 position;

	PhysBody3D* pbody = nullptr;
};

