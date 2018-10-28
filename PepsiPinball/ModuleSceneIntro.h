#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;
	
	// Textures
	SDL_Texture* background = nullptr;
	SDL_Texture* leftBarrels = nullptr;
	SDL_Texture* idleMultipliers = nullptr;
	SDL_Texture* Barrels = nullptr;
	SDL_Texture* bonus = nullptr;

	SDL_Texture* box = nullptr;
	SDL_Texture* rick = nullptr;

	//Bonus 
	SDL_Rect multiplier;
	SDL_Rect activeMultiplier_x2;
	SDL_Rect activeMultiplier_x4;
	SDL_Rect activeMultiplier_x6;
	SDL_Rect activeMultiplier_x8;
	SDL_Rect activeMultiplier_x10;
	SDL_Rect activeMultiplier_hold;

	bool x4 = false;
	bool x6 = false;
	bool x8 = false;
	bool x10 = false;
	bool hold = false;

	SDL_Rect flag1;
	SDL_Rect flag1_active;
	SDL_Rect flag2;
	SDL_Rect flag2_active;
	SDL_Rect flag3;
	SDL_Rect flag3_active;

	bool activatedFlag1 = false;
	bool activatedFlag2 = false;
	bool activatedFlag3 = false;

	// Audios
	uint touchingHat;
	uint initialSong;
	uint beatingAllCowboys;

	// Total score
	uint playerScore;

	// Score modifyers
	uint collisionScore;
	uint flagScore;
	uint cowboyScore;
	uint pathScore;
};
