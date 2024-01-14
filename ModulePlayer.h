#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "CheckPoint.h"
#include "RaceProgress.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 5000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 0.0f

class Atmosphere
{
public:
	float wind = 100;

	float density = 0.225;
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2) override;
	bool CleanUp();

	void ResetOrientation();
	void BackToLastCp();

	void DragForce();
	void LiftForce();
	void BouyancyForce();

public:

	PhysVehicle3D* vehicle;
	float turn;
	int state;
	float acceleration;
	float brake;

	RaceProgress raceData;
	p2List_item<Checkpoint*>* currentCheckpoint;

	Atmosphere atmosphere;

};