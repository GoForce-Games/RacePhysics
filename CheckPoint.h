#pragma once
#include "Entity.h"

enum class CheckpointType
{
	START_LINE,
	CHECKPOINT,
	FINISH_LINE,
	UNKNOWN
};

class Checkpoint : public Entity
{
	Checkpoint(Application* parent, CheckpointType type = CheckpointType::CHECKPOINT);
	~Checkpoint();

	bool Init() override;
	bool EntityUpdate(float dt) override;
	bool CleanUp();
	void OnCollision(PhysBody3D* bodyA, PhysBody3D* bodyB);


public:

	CheckpointType cpType;

};

