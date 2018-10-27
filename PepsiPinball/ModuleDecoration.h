#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

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
	SDL_Texture* hat = nullptr;
	SDL_Texture* gate = nullptr;
	SDL_Texture* entrance = nullptr;
	SDL_Texture* carruage = nullptr;
	SDL_Texture* leftBarrels = nullptr;
	SDL_Texture* rightBarrels = nullptr;
	SDL_Texture* leaves = nullptr;
	SDL_Texture* plant = nullptr;
	SDL_Texture* cactus = nullptr;
	SDL_Texture* tree = nullptr;
	SDL_Texture* cowboy = nullptr;
	SDL_Texture* mineWall = nullptr;
};