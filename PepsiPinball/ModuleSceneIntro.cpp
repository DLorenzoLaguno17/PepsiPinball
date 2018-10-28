#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModuleFonts.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	// Triangles at the top of the map
	littleHat = { 80, 29, 34, 29 };
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
	Cowboy_Hat = App->textures->Load("Assets/Textures/mapInteractions.png");
	Barrels = App->textures->Load("Assets/Textures/rightBarrels.png");

	// Textures are loaded
	background = App->textures->Load("Assets/Textures/Map.png");
	leftBarrels = App->textures->Load("Assets/Textures/leftBarrels.png");
	bonus = App->textures->Load("Assets/Textures/bonus.png");
	idleMultipliers = App->textures->Load("Assets/Textures/idleMultipliers.png");

	// Audios are loaded
	initialSong = App->audio->LoadFx("Assets/SoundFX/initialSong.wav");
	touchingHat = App->audio->LoadFx("Assets/SoundFX/touchingHat.wav");
	beatingAllCowboys = App->audio->LoadFx("Assets/SoundFX/beatingAllCowboys.wav");

	App->audio->PlayFx(initialSong);

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

	App->renderer->Blit(Barrels, 409, 347);

	App->renderer->Blit(Cowboy_Hat, 405, 186, &littleHat);
	App->renderer->Blit(Cowboy_Hat, 400, 147, &littleHat);
	App->renderer->Blit(Cowboy_Hat, 455, 162, &littleHat);

	//if(x4)
	if(x2)
		App->renderer->Blit(bonus, 310, 467, &activeMultiplier_x2);

	if(x4)
		App->renderer->Blit(bonus, 310, 432, &activeMultiplier_x4);

	if(x6)
		App->renderer->Blit(bonus, 267, 421, &activeMultiplier_x6);

	if(x8)
		App->renderer->Blit(bonus, 350, 421, &activeMultiplier_x8);

	if(x10)
		App->renderer->Blit(bonus, 207, 332, &activeMultiplier_x10);

	if(hold)
		App->renderer->Blit(bonus, 448, 332, &activeMultiplier_hold);


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

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 15, b2_dynamicBody));
		circles.getLast()->data->listener = this;
	}

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// Draw circles of F1 ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(App->player->ballTexture, x, y);
		c = c->next;
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	
}
