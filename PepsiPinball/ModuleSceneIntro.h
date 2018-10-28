#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include "Animation.h"

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
	void setBonuses();

public:
	p2List<PhysBody*> circles;
	
	// Textures
	SDL_Texture* background = nullptr;
	SDL_Texture* leftBarrels = nullptr;
	SDL_Texture* idleMultipliers = nullptr;
	SDL_Texture* rightBarrels = nullptr;
	SDL_Texture* bonus = nullptr;
	SDL_Texture* hat = nullptr;
	SDL_Texture* tires = nullptr;

	//Animation Cowboys
	Animation Cowboy1;
	Animation Cowboy2;
	Animation Cowboy3;
	Animation Cowboy4;
	Animation Cowboy5;
	Animation Cowboy6;
	Animation Cowboy7;
	Animation Cowboy8;
	Animation Cowboy9;
	Animation Cowboy10;
	Animation Cowboy11;

	SDL_Rect Cowboyrect1;
	SDL_Rect Cowboyrect2;
	SDL_Rect Cowboyrect3;
	SDL_Rect Cowboyrect4;
	SDL_Rect Cowboyrect5;
	SDL_Rect Cowboyrect6;
	SDL_Rect Cowboyrect7;
	SDL_Rect Cowboyrect8;
	SDL_Rect Cowboyrect9;
	SDL_Rect Cowboyrect10;
	SDL_Rect Cowboyrect11;

	// Animation Hats
	Animation Hat1;
	Animation Hat2;
	Animation Hat3;

	//Bonus 
	SDL_Rect multiplier;
	SDL_Rect bigHat;
	SDL_Rect littleHat;
	SDL_Rect cowboyUp;
	SDL_Rect cowboyDown;
	SDL_Rect activeMultiplier_x2;
	SDL_Rect activeMultiplier_x4;
	SDL_Rect activeMultiplier_x6;
	SDL_Rect activeMultiplier_x8;
	SDL_Rect activeMultiplier_x10;
	SDL_Rect activeMultiplier_hold;

	bool x2 = false;
	bool x4 = false;
	bool x6 = false;
	bool x8 = false;
	bool x10 = false;
	bool hold = false;
	uint bonuses;

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
	uint initialSong;
	uint beatingAllCowboys;
};