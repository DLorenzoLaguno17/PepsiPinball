#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	lf_Section = { 2, 3, 72, 21 };
	rf_Section = { 2, 28, 72, 21 };
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	// Textures are loaded
	ballTexture = App->textures->Load("Assets/Textures/ball.png");
	flippersTexture = App->textures->Load("Assets/Textures/flippers.png");

	// Audios are loaded
	flipperSound =  App->audio->LoadFx("Assets/SoundFX/flipper.wav");
	
	startingPosition = {500, 100};

	addBall(startingPosition.x, startingPosition.y);
	putLeftFlipper();
	putRightFlippers();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->textures->Unload(flippersTexture);
	App->textures->Unload(ballTexture);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	// Move right flippers
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		rightFlipperJoint1->EnableMotor(true);
		rightFlipperJoint2->EnableMotor(true);
		if (!playedRight) {
			App->audio->PlayFx(flipperSound);
			playedRight = true;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP) {
		rightFlipperJoint1->EnableMotor(false); 
		rightFlipperJoint2->EnableMotor(false);
		playedRight = false;
	}

	// Move left flipper
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		leftFlipperJoint->EnableMotor(true); 
		if (!playedLeft) {
			App->audio->PlayFx(flipperSound);
			playedLeft = true;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP) {
		leftFlipperJoint->EnableMotor(false);
		playedLeft = false;
	}
	
	//Drawing everything
	rightFlipper1->GetPosition(position.x, position.y);
	App->renderer->Blit(flippersTexture, position.x, position.y, &rf_Section, 1.0f, rightFlipper1->GetRotation());
	
	rightFlipper2->GetPosition(position.x, position.y);
	App->renderer->Blit(flippersTexture, position.x, position.y, &rf_Section, 1.0f, rightFlipper2->GetRotation());

	leftFlipper->GetPosition(position.x, position.y);
	App->renderer->Blit(flippersTexture, position.x, position.y, &lf_Section, 1.0f, leftFlipper->GetRotation());
	
	ball->GetPosition(position.x, position.y); 
	App->renderer->Blit(App->player->ballTexture, position.x, position.y);

	return UPDATE_CONTINUE;
}

void ModulePlayer::putRightFlippers() {
	// Lower flipper
	rightFlipper1 = App->physics->CreateRectangle(375, 500, 32, 10, b2_dynamicBody);
	rightFlipper1_pivot = App->physics->CreateCircle(393, 489, 3, b2_staticBody);

	b2RevoluteJointDef revoluteJointDef1;

	revoluteJointDef1.bodyA = rightFlipper1->body;
	revoluteJointDef1.bodyB = rightFlipper1_pivot->body;

	rightFlipper1->body->SetGravityScale(9.81f);

	revoluteJointDef1.localAnchorA.Set(PIXEL_TO_METERS(25), 0);
	revoluteJointDef1.localAnchorB.Set(0, 0);
	revoluteJointDef1.collideConnected = false;

	revoluteJointDef1.enableLimit = true;
	revoluteJointDef1.upperAngle = 25 * DEGTORAD;
	revoluteJointDef1.lowerAngle = -25 * DEGTORAD;

	revoluteJointDef1.motorSpeed = -2000.0f * DEGTORAD;
	revoluteJointDef1.maxMotorTorque = 1500.0f;
	revoluteJointDef1.enableMotor = false;

	rightFlipperJoint1 = (b2RevoluteJoint*)App->physics->world->CreateJoint(&revoluteJointDef1);
	
	// Upper flipper
	rightFlipper2 = App->physics->CreateRectangle(375, 500, 32, 10, b2_dynamicBody);
	rightFlipper2_pivot = App->physics->CreateCircle(500, 300, 3, b2_staticBody);

	b2RevoluteJointDef revoluteJointDef2;

	revoluteJointDef2.bodyA = rightFlipper2->body;
	revoluteJointDef2.bodyB = rightFlipper2_pivot->body;

	rightFlipper2->body->SetGravityScale(9.81f);

	revoluteJointDef2.localAnchorA.Set(PIXEL_TO_METERS(25), 0);
	revoluteJointDef2.localAnchorB.Set(0, 0);
	revoluteJointDef2.collideConnected = false;

	revoluteJointDef2.enableLimit = true;
	revoluteJointDef2.upperAngle = 25 * DEGTORAD;
	revoluteJointDef2.lowerAngle = -25 * DEGTORAD;

	revoluteJointDef2.motorSpeed = -2000.0f * DEGTORAD;
	revoluteJointDef2.maxMotorTorque = 1500.0f;
	revoluteJointDef2.enableMotor = false;

	rightFlipperJoint2 = (b2RevoluteJoint*)App->physics->world->CreateJoint(&revoluteJointDef2);

}

void ModulePlayer::putLeftFlipper() {
	leftFlipper = App->physics->CreateRectangle(242, 500, 32, 10, b2_dynamicBody);
	leftFlipper_pivot = App->physics->CreateCircle(255, 489, 3, b2_staticBody);

	b2RevoluteJointDef revoluteJointDef;

	revoluteJointDef.bodyA = leftFlipper->body;
	revoluteJointDef.bodyB = leftFlipper_pivot->body;
	leftFlipper->body->SetGravityScale(9.81f);

	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(-25), 0);
	revoluteJointDef.localAnchorB.Set(0, 0);
	revoluteJointDef.collideConnected = false;

	revoluteJointDef.enableLimit = true;
	revoluteJointDef.upperAngle = 25 * DEGTORAD;
	revoluteJointDef.lowerAngle = -25 * DEGTORAD;

	revoluteJointDef.motorSpeed = 2000.0f * DEGTORAD;
	revoluteJointDef.maxMotorTorque = 1500.0f;
	revoluteJointDef.enableMotor = false;

	leftFlipperJoint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&revoluteJointDef);
}

void ModulePlayer::addBall(uint x, uint y) {
	ball = App->physics->CreateCircle(x, y, 14, b2_dynamicBody);
	ball->listener = this;
}