#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Box2D/Box2D/Box2D.h"

struct SDL_Texture;
class PhysBody;
struct SDL_Rect;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

private:
	void putRightFlippers();
	void putLeftFlipper();
	void addBall(uint x, uint y);

public:
	SDL_Texture* ballTexture = nullptr;
	SDL_Texture* flippersTexture = nullptr;

	// Flipers section of the texture
	SDL_Rect rf_Section;
	SDL_Rect lf_Section;

	// Audios
	uint flipperSound;
	bool playedRight = false;
	bool playedLeft = false;

	iPoint startingPosition;
	iPoint position;
	uint balls;

private:
	PhysBody* ball = nullptr;
	PhysBody* leftFlipper = nullptr;
	PhysBody* leftFlipper_pivot = nullptr;
	PhysBody* rightFlipper1 = nullptr;
	PhysBody* rightFlipper1_pivot = nullptr;
	PhysBody* rightFlipper2 = nullptr;
	PhysBody* rightFlipper2_pivot = nullptr;

	b2RevoluteJoint* leftFlipperJoint = nullptr;
	b2RevoluteJoint* rightFlipperJoint1 = nullptr;
	b2RevoluteJoint* rightFlipperJoint2 = nullptr;
};