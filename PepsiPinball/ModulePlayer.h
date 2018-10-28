#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "Animation.h"
#include "Box2D/Box2D/Box2D.h"

struct SDL_Texture;
class PhysBody;

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	void addBall(uint x, uint y);
	void putRightFlippers();
	void putLeftFlipper();
	void putHorse();
	void createSensors();

public:
	SDL_Texture* ballTexture = nullptr;
	SDL_Texture* flippersTexture = nullptr;
	
	// The propeller of the ball is a horse
	SDL_Texture* horseTexture = nullptr;

	// Flipers section of the texture
	SDL_Rect rf_Section;
	SDL_Rect lf_Section;

	Animation horse;

	// Audios
	uint henSound;
	uint barrelSound;
	uint thrillingSound;
	uint horseSound;
	uint loseSound;
	uint touchingHat;
	uint wolfSound;
	uint newBallSound;

	uint flipperSound;
	bool playedRight = false;
	bool playedLeft = false;

	// Total score
	uint highScore;
	uint playerScore;

	int fontScore = -1;
	char scoreText[10];
	char ballsText[10];

	// Score modifyers
	uint collisionScore;
	uint flagScore;
	uint cowboyScore;
	uint pathScore;
	uint wagonScore;

	iPoint startingPosition;
	iPoint position;
	uint balls;

private:
	// Sensors
	PhysBody* wagonSensor = nullptr;
	PhysBody* pathSensor = nullptr;
	PhysBody* barrelSensorRight = nullptr;
	PhysBody* barrelSensorLeft = nullptr;
	PhysBody* hatSensor1 = nullptr;
	PhysBody* hatSensor2 = nullptr;
	PhysBody* hatSensor3 = nullptr;
	PhysBody* flagSensor1 = nullptr;
	PhysBody* flagSensor2 = nullptr;
	PhysBody* flagSensor3 = nullptr;

	// Joints
	PhysBody* propeller = nullptr;
	PhysBody* propeller_pivot = nullptr;
	PhysBody* ball = nullptr;
	PhysBody* leftFlipper = nullptr;
	PhysBody* leftFlipper_pivot = nullptr;
	PhysBody* rightFlipper1 = nullptr;
	PhysBody* rightFlipper1_pivot = nullptr;
	PhysBody* rightFlipper2 = nullptr;
	PhysBody* rightFlipper2_pivot = nullptr;

	b2PrismaticJoint* propellerJoint = nullptr;
	b2RevoluteJoint* leftFlipperJoint = nullptr;
	b2RevoluteJoint* rightFlipperJoint1 = nullptr;
	b2RevoluteJoint* rightFlipperJoint2 = nullptr;
};