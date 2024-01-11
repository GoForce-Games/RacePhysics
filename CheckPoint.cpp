#include "CheckPoint.h"
#include "Application.h"

Checkpoint::Checkpoint(Application* parent, CheckpointType type) : Entity(EntityType::CHECKPOINT, parent), cpType(type)
{
	switch (type)
	{
	case CheckpointType::START_LINE:
		name.Create("start_line");
		break;
	case CheckpointType::CHECKPOINT:
		name.Create("checkpoint");
		break;
	case CheckpointType::FINISH_LINE:
		name.Create("finish_line");
		break;
	case CheckpointType::CIRCUIT_START:
		name.Create("circuit_start");
		break;
	default:
		name.Create("unknown_checkpoint");
		break;
	}
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
