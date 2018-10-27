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
	
	leftBarrels = App->textures->Load("Assets/Textures/leftBarrels.png");
	rightBarrels = App->textures->Load("Assets/Textures/rightBarrels.png");
	hat = App->textures->Load("Assets/Textures/hat.png"); 
	gate = App->textures->Load("Assets/Textures/gate.png");
	entrance = App->textures->Load("Assets/Textures/gate.png");
	carruage = App->textures->Load("Assets/Textures/carruage.png");	
	plant = App->textures->Load("Assets/Textures/plant.png");
	cactus = App->textures->Load("Assets/Textures/cactus.png");
	leaves = App->textures->Load("Assets/Textures/leaves.png");
	tree = App->textures->Load("Assets/Textures/tree.png");
	mineWall = App->textures->Load("Assets/Textures/mineWall.png");
	cowboy = App->textures->Load("Assets/Textures/cowboy.png");

	return ret;
}

// Load assets
bool ModuleDecoration::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(mineWall);
	App->textures->Unload(cowboy);
	App->textures->Unload(tree);
	App->textures->Unload(leaves);
	App->textures->Unload(cactus);
	App->textures->Unload(plant);
	App->textures->Unload(carruage);
	App->textures->Unload(entrance);
	App->textures->Unload(gate);
	App->textures->Unload(hat);
	App->textures->Unload(rightBarrels);
	App->textures->Unload(leftBarrels);

	return true;
}

// Update: draw background
update_status ModuleDecoration::Update()
{
	App->renderer->Blit(leftBarrels, 148, 342);
	App->renderer->Blit(leaves, 102, 374);
	App->renderer->Blit(cactus, 467, 363);
	App->renderer->Blit(gate, 242, 367);
	App->renderer->Blit(plant, 55, 325);
	App->renderer->Blit(tree, 492, 245);
	App->renderer->Blit(carruage, 155, 215);
	App->renderer->Blit(mineWall, 647, 39);

	//All cowoys
	//App->renderer->Blit(cowboy, 242, 100);


	return UPDATE_CONTINUE;
}

void ModuleDecoration::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	//App->audio->PlayFx(bonus_fx);
}