#ifndef PLAYERSONIC_H
#define PLAYERSONIC_H

class TexturedModel;
class Triangle3D;
class ParticleTexture;
class Source;
class PlayerModel;
class Source;

#include <list>
#include <vector>
#include "entity.h"
#include "controllableplayer.h"
#include "../toolbox/vector.h"

class PlayerSonic : public ControllablePlayer
{
private:
	PlayerModel* playerModel = nullptr;

	//bool onGround = false;
	//Vector3f vel; //Direction we are currently going
	//Vector3f relativeUp; //What direction is "up", aka grounds normal
	Vector3f relativeUpSmooth; //What direction is "up", aka grounds normal
	Vector3f relativeUpAnim; //relative up to use for animations. smooth less than relativeUpSmooth
	//Vector3f camDir; //Direction the camera wants to be facing
	//Vector3f camDirSmooth; //Direction the camera is facing curerntly

	const float FLOOR_OFFSET = 0.1f; //How much you stay away from the floor
	Triangle3D* currentTriangle = nullptr; //the triangle object that you are touching
	const float smoothTransitionThreshold = 0.6f; //Dot product threshold for running between triangles
	const float surfaceTension = 10.0f;     //To not fly off the ground
	const float hitWallTimePunish = 0.0f;   //How long you can't move after hitting a wall 0.125

	const float wallStickThreshold = 0.45f;  //How steep a slope must be to be considered a wall 0.3
    const float wallStickTimerMax = 0.5f; //How much time you can stick to a wall while running slow
    const float wallStickSpeedRequirement = 100.0f; //how much speed you need to stick to a wall
    float wallStickTimer = 0.0f;

	const float gravityForce = 280.0f;
	const float gravityTerminal = -650.0f;
	const float gravityApproach = 0.45f;

	bool isJumping = false;
	const float jumpPower = 120.0f; //Initial speed you get form jump
	const float hoverPower = 170.0f; //How much hover adds to your vel
	const float hoverTimerThreshold = 1.0f; //How long you can hover for
	float hoverTimer = 0.0f;

	const float groundRunPush = 100.0f;
	const float groundRunFriction = 0.5f;
	const float groundNeutralFriction = 1.5f; //5.5
	const float skidPower = -5.0f;
	const float airRunPush = 25.0f; //30.0
	const float airRunFrictionUp = 0.75f; //0.25    //maybe make another variable for this to use when vel.y < 0?
	const float airRunFrictionDown = 0.25f; //For when sonic is falling down
    const float airFrictionThreshold = 40.0f; //When youre going slower than this horizontally, doing apply friction
	const float airNeutralFriction = 1.25f;
	const float slopeRunAccel = 9000.0f;

	bool isBall = false;
	//version 1
	//const float groundBallFriction = 0.1f;
	//const float slopeBallAccel = 42000.0f;
	//version 2
	const float groundBallFriction = 0.1f; //0.02f;
	const float slopeBallAccel = 140.0f; //50.0f;
	const float autoUnrollThreshold = 120.0f; //60
	const float maxBallSpeed = 800.0f; //you wont go faster than this when rolling down a hill in ball form

	bool isSpindashing = false;
	Vector3f spindashDirection;
	bool canStartSpindash = false;
	bool bufferedSpindashInput = false;
	const float spindashPowerMax = 500.0f; //475.0f
	const float spindashChargeRate = 0.4f*60*60;
	const float spindashFriction = 2.0f;
	const float spindashPowerfulFriction = 8.0f;
	const float spindashPowerfulFrictionThreshold = 100.0f;
	const float spindashDelay = 0; //how long the timer waits before it starts applying spindash friction
	float spindashTimer = 0;
	const float spindashTimerMax = 35.0f/60.0f;
	float spindashReleaseTimer = 0;
	const float spindashReleaseTimerMax = 30.0f/60.0f;
	float spindashRestartDelay = 0;
	const float spindashRestartDelayMax = 25.0f/60.0f; // 3.0f/60.0f
	float storedSpindashSpeed = 0;

    bool isRunningOnWater = false;
    const float runningOnWaterSpeedThreshold = 480.0f;
    const float runOnWaterTransitionThreshold = 0.75f; //Dot product threshold for running between floor and water

    bool isStomping = false;
    const float stompSpeed = -350.0f;
    Source* sourceStomp = nullptr;

	bool isSkidding = false;
    const float skidAudioThreshold = 150.0f;

	bool isGrinding = false;
    bool onRocket = false;

    bool isLightdashing = false;
    std::vector<Vector3f> lightdashTrail;
    float lightdashTrailProgress = -1.0f;
    const float lightdashStartRingMinDist = 45.0f; //how close does the ring need to be to start lightdashing?
    const float lightdashContinueRingMinDist = 80.0f; //how close does the next ring have to be to coninue the trail?
    const float lightdashSpeed = 600.0f;
    const float lightdashExitSpeed = 300.0f;

	const float bounceVel = -300.0f;
	const float bounceFactor = 0.7f;
	bool isBouncing = false;
	bool justBounced = false; //Are we in the air after doing a bounce?

	bool justHomingAttacked = false; //Are we in the air after doing a homing attack?
	float homingAttackTimer = -1.0f; // less than 0 = can start a homing attack
	const float homingAttackTimerMax = 0.2f;
    bool isHomingOnPoint = false;
    const float homingAttackRangeMax =  115.0f*115.0f; //max squared
    const float homingAttackDotThreshold = 0.65f;

	//const float camAngleLookdown = 0.0f; //0.2f; //How much the camera looks down
	const float camRadius        = 75.0;  //Camera radius at zero speed
	const float camHeightOffset  = 5.0f; //Point above the vehicle that the camera focuses on

	//float canMoveTimer = 0.0f;
    float hitSpringTimer = 0.0f;

	//animation variables
	float runAnimationCycle = 0.0f;

	//const float displayHeightOffset = 0.6f;
	//const float displayBallOffset = 3.0f;

    Vector3f centerPosPrev;

    //input variables
	bool  inputJump;
	bool  inputJumpPrevious;
	bool  inputAction;
	bool  inputActionPrevious;
	bool  inputAction2;
	bool  inputAction2Previous;
    bool  inputAction3;
    bool  inputAction3Previous;
	float inputX;
	float inputY;
	float inputX2;
	float inputY2;

	void moveMeGround();

	void moveMeAir();

	void spindash();

    void homingAttack();

	void calcSpindashDirection();

	void setInputs();

	void updateAnimationValues();

public:
	PlayerSonic();
	PlayerSonic(float x, float y, float z);
	~PlayerSonic();

	void step();

	//Call this to "redraw" sonic
	void animate();

    //updates the global camera's values based on 
    // this player's values
    void refreshCamera();

	void setVelocity(float xVel, float yVel, float zVel);

	Vector3f* getVelocity();

    void popOffWall();

    void hitSpring(Vector3f* direction, float power, float lockInputTime);

    void hitDashpad();

    bool isVulnerable();

    void rebound(Vector3f* source);

	void setCanMoveTimer(float newTimer);

	void startGrinding();

	void stopGrinding();

	void setIsBall(bool newIsBall);

    void grabRocket();

    void releaseRocket();

	void setOnGround(bool newOnGround);

	//called by Rail when sonic jumps off
	void jump();

	void setRelativeUp(Vector3f* newUp);

	std::list<TexturedModel*>* getModels();

	void loadVehicleInfo();

	static void deleteStaticModels();

	const bool isVehicle();

    Vector3f* getCameraDirection();

    void setCameraDirection(Vector3f* newDirection);

    Vector3f getCenterPosition();
};
#endif