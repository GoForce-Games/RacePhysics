#include "CheckPoint.h"
#include "Application.h"

Checkpoint::Checkpoint(Application* parent,btVector3 size) : Entity(EntityType::CHECKPOINT, parent)
{
	pbody = App->physics->AddBody(Cube(size.x(), size.y(), size.z()), 0, true);
	App->race_manager->checkpoints += this;
}

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
	return true;
}

bool Checkpoint::CleanUp()
{
	App->race_manager->checkpoints -= this;
	return true;
}

void Checkpoint::OnCollision(PhysBody3D* bodyA, PhysBody3D* bodyB)
{
}

bool Checkpoint::CheckpointBehavior(float dt)
{
	return true;
}

bool Checkpoint::StartLineBehavior(float dt)
{
	return true;
}

bool Checkpoint::FinishLineBehavior(float dt)
{
	return true;
}

bool Checkpoint::CircuitStartBehavior(float dt)
{
	return true;
}
