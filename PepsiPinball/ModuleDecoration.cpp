#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleDecoration.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"

ModuleDecoration::ModuleDecoration(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleDecoration::~ModuleDecoration()
{}

// Load assets
bool ModuleDecoration::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;	

	mapInteractions = App->textures->Load("Assets/Textures/bonus.png");
	decoration = App->textures->Load("Assets/Textures/decoration1.png");
	scoreScreen = App->textures->Load("Assets/Textures/scoreScreen.png");

	return ret;
}

// Load assets
bool ModuleDecoration::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(decoration);
	App->textures->Unload(mapInteractions);

	return true;
}

// Update: draw background
update_status ModuleDecoration::Update()
{
	App->renderer->Blit(decoration, 26, 82);

	if (App->player->balls == 6) {
		App->renderer->Blit(scoreScreen, 170, 100);

		sprintf_s(App->player->scoreText, 10, "%7d", App->player->playerScore);
		App->fonts->BlitText(280, 130, App->player->fontScore, App->player->scoreText);

		sprintf_s(App->player->scoreText, 10, "%7d", App->player->highScore);
		App->fonts->BlitText(280, 160, App->player->fontScore, App->player->scoreText);
	}


	return UPDATE_CONTINUE;
}

void ModuleDecoration::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	//App->audio->PlayFx(bonus_fx);
}