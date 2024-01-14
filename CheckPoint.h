#pragma once
#include "Entity.h"

enum class CheckpointType
{
	START_LINE,
	CHECKPOINT,
	FINISH_LINE,
	CIRCUIT_START,
	UNKNOWN
};

class Checkpoint : public Entity
{
public:

	Checkpoint(Application* parent, btVector3 size);
	~Checkpoint();

	bool Init() override;
	bool EntityUpdate(float dt) override;
	bool CleanUp();
	void OnCollision(PhysBody3D* bodyA, PhysBody3D* bodyB);

	bool CheckpointBehavior(float dt);
	bool StartLineBehavior(float dt);
	bool FinishLineBehavior(float dt);
	bool CircuitStartBehavior(float dt);

};

