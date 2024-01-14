#pragma once
#include "Bullet/include/btBulletCollisionCommon.h"
#include "SString.h"

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

	// Initializes the entity. WARNING: Do NOT delete the entity from within this method
	virtual bool Init() = 0;

	// Updates the entity. WARNING: Do NOT delete the entity from within this method
	bool Update(float dt);

	PhysBody3D* GetBody() { return pbody; }

	// Custom logic on a per-entity basis
	virtual bool EntityUpdate(float dt) = 0;

	virtual bool CleanUp();

	virtual void OnCollision(PhysBody3D* bodyA, PhysBody3D* bodyB) {}

	virtual btTransform GetTransform();

	virtual void SetPosition(const btVector3& pos);
	virtual void SetTransform(const btTransform& transform);

public:

	SString name;
	EntityType eType;

protected:

	btVector3 position;
	btVector3 rotation;

	PhysBody3D* pbody = nullptr;
};

