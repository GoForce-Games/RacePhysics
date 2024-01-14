#pragma once
#include "CheckPoint.h"
#include "p2List.h"
#include "SString.h"

struct RaceProgress {
	SString name;
	bool finished = false;
	int total_checkpoints = 0;
	int laps = 0;
	p2List_item<Checkpoint*>* currentCheckpoint = nullptr;
};