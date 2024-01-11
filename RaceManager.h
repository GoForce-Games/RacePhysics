#pragma once
#include "Module.h"
#include "p2List.h"

class Checkpoint;

class RaceManager :
    public Module
{
public:

	RaceManager(Application* parent, bool start_enabled = true);
	~RaceManager();

	bool Init() override;
	bool Start() override;

	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;

	bool CleanUp() override;

	Checkpoint* AddCheckpoint(Checkpoint* cp);
	void RemoveCheckpoint(Checkpoint* cp);

private:

	float raceProgress = 0;
	p2List<Checkpoint*> checkpoints;

	friend class Checkpoint;

};

