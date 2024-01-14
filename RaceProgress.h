#pragma once
#include "CheckPoint.h"
#include "p2List.h"
#include "SString.h"

struct RaceProgress {
	SString name;
	bool finished = false;
	int checkpoint_progress = 0;
	int laps = 0;
	p2List_item<Checkpoint*>* current_checkpoint = nullptr;
};