#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	// Triangles at the top of the map
	flag1 = { 67, 6, 64, 36 }; 
	flag1_active = { 2, 6, 64, 36 };
	flag2 = { 75, 57, 50, 41 }; 
	flag2_active = { 17, 57, 50, 41 };
	flag3 = { 67, 117, 38, 46 };
	flag3_active = { 15, 117, 38, 46 };

	activeMultiplier_x2 = { 63, 221, 26, 19 };
	activeMultiplier_x4 = { 27, 221, 26, 19 };
	activeMultiplier_x6 = { 63, 191, 26, 19 };
	activeMultiplier_x8 = { 101, 220, 26, 19 };
	activeMultiplier_x10 = { 28, 191, 26, 19 };
	activeMultiplier_hold = { 101, 190, 26, 19 };
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");

	background = App->textures->Load("Assets/Textures/Map.png");
	leftBarrels = App->textures->Load("Assets/Textures/leftBarrels.png");
	bonus = App->textures->Load("Assets/Textures/bonus.png");
	idleMultipliers = App->textures->Load("Assets/Textures/idleMultipliers.png");

	initialSong = App->audio->LoadFx("Assets/SoundFX/initialSong.wav");
	touchingHat = App->audio->LoadFx("Assets/SoundFX/touchingHat.wav");
	beatingAllCowboys = App->audio->LoadFx("Assets/SoundFX/beatingAllCowboys.wav");

	// Each score increaser is given a value
	collisionScore = 500;
	flagScore = 1000;
	cowboyScore = 1000;
	pathScore = 250000;

	playerScore = 0;

	//App->audio->PlayFx(initialSong);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(bonus);
	App->textures->Unload(leftBarrels);
	App->textures->Unload(background);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->Blit(background, 0, 0);
	App->renderer->Blit(leftBarrels, 146, 340);

	//Blitting bonuses
	App->renderer->Blit(idleMultipliers, 193, 233);

	//if(x4)
		App->renderer->Blit(bonus, 310, 432, &activeMultiplier_x4);

	if(activatedFlag1)
		App->renderer->Blit(bonus, 409, 102, &flag1_active);
	else
		App->renderer->Blit(bonus, 409, 102, &flag1);

	if (activatedFlag2)
		App->renderer->Blit(bonus, 455, 110, &flag2_active);
	else
		App->renderer->Blit(bonus, 455, 110, &flag2);

	if (activatedFlag3)
		App->renderer->Blit(bonus, 500, 118, &flag3_active);
	else
		App->renderer->Blit(bonus, 500, 118, &flag3);

	// Move right flippers
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		
	}

	// Move left flipper
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		
	}

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 15));
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64, b2_dynamicBody));
	}

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(App->player->ball, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	//App->audio->PlayFx(bonus_fx);
}
