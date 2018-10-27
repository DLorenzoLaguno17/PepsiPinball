#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleDecoration : public Module
{
public:
	ModuleDecoration(Application* app, bool start_enabled = true);
	~ModuleDecoration();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	// Textures
	SDL_Texture* decoration = nullptr;
	SDL_Texture* mapInteractions = nullptr;
};