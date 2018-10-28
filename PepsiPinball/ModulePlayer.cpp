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

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	lf_Section = { 2, 3, 72, 21 };
	rf_Section = { 2, 28, 72, 21 };

	horse.PushBack({48, 58, 72, 104});
	horse.PushBack({ 150, 58, 72, 104 });
	horse.PushBack({ 242, 58, 72, 104 });
	horse.PushBack({ 331, 59, 72, 104 });
	horse.PushBack({ 242, 58, 72, 104 });
	horse.PushBack({ 48, 58, 72, 104 });

	horse.speed = 0.15f;
	horse.loop = false;
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
	horseTexture = App->textures->Load("Assets/Textures/horse.png");

	// Audios are loaded
	flipperSound =  App->audio->LoadFx("Assets/SoundFX/flipper.wav");
	horseSound = App->audio->LoadFx("Assets/SoundFX/lose.wav");
	thrillingSound = App->audio->LoadFx("Assets/SoundFX/thrill.wav");
	henSound = App->audio->LoadFx("Assets/SoundFX/hen.wav");
	loseSound = App->audio->LoadFx("Assets/SoundFX/lose.wav"); 
	touchingHat = App->audio->LoadFx("Assets/SoundFX/touchingHat.wav");

	// Fonts are loaded
	fontScore = App->fonts->Load("Assets/Textures/Fonts/fontScore.png", "0123845679", 2);

	// Each score increaser is given a value
	collisionScore = 500;
	flagScore = 1000;
	cowboyScore = 1000;
	pathScore = 250000;
	carruageScore = 500000;

	playerScore = 0;

	startingPosition = {650, 360};

	addBall(startingPosition.x, startingPosition.y);
	putLeftFlipper();
	putRightFlippers();
	putHorse();
	createSensors();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->fonts->UnLoad(fontScore);

	App->textures->Unload(horseTexture);
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

	// Activate horse propeller
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN) {
		propellerJoint->EnableMotor(true);
		App->audio->PlayFx(horseSound);
		horse.Reset();
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP) {
		propellerJoint->EnableMotor(false);
	}

	// Death condition
	ball->GetPosition(position.x, position.y);
	if (position.y > SCREEN_HEIGHT) {
		delete ball;
		ball->body = nullptr;
		addBall(startingPosition.x, startingPosition.y);
		App->audio->PlayFx(loseSound);
	}	

	//Drawing everything
	SDL_Rect r = horse.GetCurrentFrame();
	App->renderer->Blit(horseTexture, 600, 390, &r);

	rightFlipper1->GetPosition(position.x, position.y);
	App->renderer->Blit(flippersTexture, position.x, position.y, &rf_Section, 1.0f, rightFlipper1->GetRotation());
	
	rightFlipper2->GetPosition(position.x, position.y);
	App->renderer->Blit(flippersTexture, position.x, position.y, &rf_Section, 1.0f, rightFlipper2->GetRotation());

	leftFlipper->GetPosition(position.x, position.y);
	App->renderer->Blit(flippersTexture, position.x, position.y, &lf_Section, 1.0f, leftFlipper->GetRotation());
	
	ball->GetPosition(position.x, position.y); 
	App->renderer->Blit(App->player->ballTexture, position.x, position.y);
	
	// Drawing the score
	sprintf_s(scoreText, 10, "%7d", playerScore);
	App->fonts->BlitText(97, 473, fontScore, scoreText);

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
	rightFlipper2 = App->physics->CreateRectangle(475, 280, 32, 10, b2_dynamicBody);
	rightFlipper2_pivot = App->physics->CreateCircle(499, 295, 3, b2_staticBody);

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

void ModulePlayer::putHorse() {
	propeller = App->physics->CreateRectangle(640, 428, 10, 30, b2_dynamicBody);
	propeller_pivot = App->physics->CreateCircle(640, 428, 5, b2_staticBody);

	b2PrismaticJointDef prismaticJointDef;

	prismaticJointDef.bodyA = propeller->body;
	prismaticJointDef.bodyB = propeller_pivot->body;

	prismaticJointDef.localAnchorA.Set(0, 0);
	prismaticJointDef.localAnchorB.Set(0, 0);
	prismaticJointDef.collideConnected = false;

	prismaticJointDef.localAxisA.Set(0, 1);

	prismaticJointDef.enableLimit = true;
	prismaticJointDef.lowerTranslation = 0;
	prismaticJointDef.upperTranslation = PIXEL_TO_METERS(50);
	prismaticJointDef.enableMotor = false;
	prismaticJointDef.maxMotorForce = 700;
	prismaticJointDef.motorSpeed = 5000;

	propellerJoint = (b2PrismaticJoint*)App->physics->world->CreateJoint(&prismaticJointDef);
}

void ModulePlayer::addBall(uint x, uint y) {
	ball = App->physics->CreateCircle(x, y, 12, b2_dynamicBody);
	ball->listener = this;
}

void ModulePlayer::createSensors() {
	// Sensor for the carruage
	carruageSensor = App->physics->CreateRectangleSensor( 165, 245, 15, 15);
	
	// Sensors for the path
	pathSensor = App->physics->CreateRectangleSensor(550, 275, 15, 15);

	// Sensors for the hats
	hatSensor1 = App->physics->CreateRectangleSensor(418, 165, 40, 30);
	hatSensor2 = App->physics->CreateRectangleSensor(422, 205, 40, 30);
	hatSensor3 = App->physics->CreateRectangleSensor(473, 183, 40, 30);

	// Sensors for the flags
	flagSensor1 = App->physics->CreateRectangleSensor(440, 114, 10, 10);
	flagSensor2 = App->physics->CreateRectangleSensor(475, 125, 10, 10);
	flagSensor3 = App->physics->CreateRectangleSensor(515, 135, 10, 10);
}

void ModulePlayer::OnCollision(PhysBody* bodyA, PhysBody* bodyB) {
	
	if (bodyB == carruageSensor) {
		playerScore += carruageScore;
		App->audio->PlayFx(thrillingSound);
		App->audio->PlayFx(henSound);
	}
	else if (bodyB == pathSensor) {
		playerScore += pathScore;
		App->audio->PlayFx(thrillingSound);
	}
	else if (bodyB == hatSensor1 || bodyB == hatSensor2 || bodyB == hatSensor3) {
		App->audio->PlayFx(touchingHat);
		playerScore += collisionScore;
	}
	else {
		playerScore += collisionScore;
	}

	if (!App->scene_intro->hold) {
		if (bodyB == flagSensor1) {
			App->scene_intro->activatedFlag1 = true;
		}
		if (bodyB == flagSensor2) {
			App->scene_intro->activatedFlag2 = true;
		}
		if (bodyB == flagSensor3) {
			App->scene_intro->activatedFlag3 = true;
		}
	}
}