#pragma once
#include "Module.h"
#include "p2List.h"
#include "RaceProgress.h"

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

	Checkpoint* GetFirstCheckpoint();
	Checkpoint* GetLastCheckpoint();

	void CheckFinished(RaceProgress& data);

	//MUST BE CALLED AFTER CREATING THE CHECKPOINTS
	RaceProgress CreatePlayer(SString name);

	int max_laps = 4;

private:

	p2List<Checkpoint*> checkpoints;

	friend class Checkpoint;

};

