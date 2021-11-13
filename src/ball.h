#pragma once
#include "ofMath.h"
#include "ofVec3f.h"
#include "ofRectangle.h"
#include "ofSoundPlayer.h"
#include <vector>

// Forward declaration to include the GameMode, Brick, and Paddle:
class GameMode;
class Brick;
class Paddle;

class Ball
{
public:
	// Inspired by the mover template/personal adaptation in Math 3009 - (A Proper Bounce), ---
	// Found that ofPoint is a typedef alias of ofVec3f, so I will opt to use ofVec3f to represent a vector:
	// https://openframeworks.cc/documentation/types/ofPoint/
	//
	// Default values for the ball (currently all Magic Numbers):
	float size{10.0};
	ofVec3f position = ofVec3f(512.0f, 384.0f, 0);
	ofVec3f velocity = ofVec3f(ofRandom(-3.0f, -1.8f), ofRandom(1.8f, 3.0f), 0); // Ball will start moving downward and to the left.

	ofRectangle hitBox;

	float limit{4};
	const float maxBounceAngle{60};

	// Constructors:
	Ball() = default;
	Ball(float sz, ofVec3f vel, ofVec3f pos);

	// Methods:
	void update();
	void edgeBounce(float canvasWidth, float canvasHeight, Paddle& paddle, GameMode& gameMode);
	void hitPaddle(const Paddle& paddle);
	void hitBrick(std::vector<Brick>& bricks, GameMode& gameMode);
	void draw() const;
	void reset();

	// Ball Hit SFX:
	ofSoundPlayer paddleHitSFX;
	ofSoundPlayer brickHitSFX;
	ofSoundPlayer loseLifeSFX;

	/*
	SFX from Atari -
	Converted to mp3 from this video:
	https://www.youtube.com/watch?v=qhaS2uMNTjI&ab_channel=AnthonyCassimiro
	*/
};
