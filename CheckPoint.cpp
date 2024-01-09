#include "CheckPoint.h"

Checkpoint::Checkpoint(Application* parent, CheckpointType type) : Entity(EntityType::CHECKPOINT, parent), cpType(type)
{}

Checkpoint::~Checkpoint()
{
	CleanUp();
}

bool Checkpoint::Init()
{
	return true;
}

bool Checkpoint::EntityUpdate(float dt)
{
	return false;
}

bool Checkpoint::CleanUp()
{
	return true;
}

void Checkpoint::OnCollision(PhysBody3D* bodyA, PhysBody3D* bodyB)
{
}
