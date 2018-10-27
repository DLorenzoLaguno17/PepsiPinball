#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleDecoration.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

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
	decoration = App->textures->Load("Assets/Textures/decoration.png");

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
	App->renderer->Blit(decoration, 53, 81);

	//All cowoys
	//App->renderer->Blit(cowboy, 242, 100);


	return UPDATE_CONTINUE;
}

void ModuleDecoration::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	//App->audio->PlayFx(bonus_fx);
}