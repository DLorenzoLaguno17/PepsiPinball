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
	littleHat = { 61, 12, 36, 30 };
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

	//Cowboys Pushbacks

	cowboyDown = { 0,0,21,46 };
	cowboyUp = { 30, 0, 21,46 };

	Cowboy1.PushBack(cowboyUp);
	Cowboy1.PushBack(cowboyDown);
	Cowboy1.loop = false;
	Cowboy1.speed = 1.0f;

	Cowboy2.PushBack(cowboyUp);
	Cowboy2.PushBack(cowboyDown);
	Cowboy2.loop = false;
	Cowboy2.speed = 1.0f;

	Cowboy3.PushBack(cowboyUp);
	Cowboy3.PushBack(cowboyDown);
	Cowboy3.loop = false;
	Cowboy3.speed = 1.0f;

	Cowboy4.PushBack(cowboyUp);
	Cowboy4.PushBack(cowboyDown);
	Cowboy4.loop = false;
	Cowboy4.speed = 1.0f;

	Cowboy5.PushBack(cowboyUp);
	Cowboy5.PushBack(cowboyDown);
	Cowboy5.loop = false;
	Cowboy5.speed = 1.0f;

	Cowboy6.PushBack(cowboyUp);
	Cowboy6.PushBack(cowboyDown);
	Cowboy6.loop = false;
	Cowboy6.speed = 1.0f;

	Cowboy7.PushBack(cowboyUp);
	Cowboy7.PushBack(cowboyDown);
	Cowboy7.loop = false;
	Cowboy7.speed = 1.0f;

	Cowboy8.PushBack(cowboyUp);
	Cowboy8.PushBack(cowboyDown);
	Cowboy8.loop = false;
	Cowboy8.speed = 1.0f;

	Cowboy9.PushBack(cowboyUp);
	Cowboy9.PushBack(cowboyDown);
	Cowboy9.loop = false;
	Cowboy9.speed = 1.0f;

	Cowboy10.PushBack(cowboyUp);
	Cowboy10.PushBack(cowboyDown);
	Cowboy10.loop = false;
	Cowboy10.speed = 1.0f;

	Cowboy11.PushBack(cowboyUp);
	Cowboy11.PushBack(cowboyDown);
	Cowboy11.loop = false;
	Cowboy11.speed = 1.0f;

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
	beatingAllCowboys = App->audio->LoadFx("Assets/SoundFX/beatingAllCowboys.wav");

	bonuses = 0;

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
	//blitting cowboys

	Cowboyrect1 = Cowboy1.GetCurrentFrame();
	Cowboyrect2 = Cowboy2.GetCurrentFrame();
	Cowboyrect3 = Cowboy3.GetCurrentFrame();
	Cowboyrect4 = Cowboy4.GetCurrentFrame();
	Cowboyrect5 = Cowboy5.GetCurrentFrame();
	Cowboyrect6 = Cowboy6.GetCurrentFrame();
	Cowboyrect7 = Cowboy7.GetCurrentFrame();
	Cowboyrect8 = Cowboy8.GetCurrentFrame();
	Cowboyrect9 = Cowboy9.GetCurrentFrame();
	Cowboyrect10 = Cowboy10.GetCurrentFrame();
	Cowboyrect11 = Cowboy11.GetCurrentFrame();


	App->renderer->Blit(Cowboy_Hat, 325, 143, &Cowboyrect1);
	App->renderer->Blit(Cowboy_Hat, 304, 155, &Cowboyrect2);
	App->renderer->Blit(Cowboy_Hat, 284, 166, &Cowboyrect3);
	App->renderer->Blit(Cowboy_Hat, 265, 175, &Cowboyrect4);
	App->renderer->Blit(Cowboy_Hat, 245, 187, &Cowboyrect5);
	App->renderer->Blit(Cowboy_Hat, 224, 199, &Cowboyrect6);
	App->renderer->Blit(Cowboy_Hat, 337, 171, &Cowboyrect7);
	App->renderer->Blit(Cowboy_Hat, 319, 181, &Cowboyrect8);
	App->renderer->Blit(Cowboy_Hat, 301, 194, &Cowboyrect9);
	App->renderer->Blit(Cowboy_Hat, 282, 204, &Cowboyrect10);
	App->renderer->Blit(Cowboy_Hat, 266, 214, &Cowboyrect11);
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
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 12, b2_dynamicBody));
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

	setBonuses();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::setBonuses() {

	if (activatedFlag1 == true && activatedFlag2 == true && activatedFlag3 == true) {
		bonuses++;
		App->player->playerScore += App->player->flagScore;
		activatedFlag1 = false;
		activatedFlag2 = false;
		activatedFlag3 = false;

		switch (bonuses) {
		case 1: x2 = true;
			break;
		case 2: x4 = true;
			break;
		case 3: x6 = true;
			break;
		case 4: x8 = true;
			break;
		case 5: x10 = true;
			break;
		case 6: hold = true;
			break;
		}
		
	}
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	
}
