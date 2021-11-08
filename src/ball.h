#pragma once
#include "ofRectangle.h"
#include <vector>

// Forward declaration to include the Paddle:
class Paddle;
class Brick;

class Ball
{
public:
	// Default values for the ball (currently all Magic Numbers):
	float xPosition{512.0}; // Default canvas Width/2.
	float yPosition{384.0}; // Default canvas Height - Height/16. 
	float xSpeed{2.0};
	float ySpeed{2.0};
	float size{10.0};
	ofRectangle hitBox;

	// Constructor:
	Ball() = default;
	Ball(float xPos, float yPos, float xSpd, float ySpd, float sz);

	void update();
	void edgeBounce(float canvasWidth, float canvasHeight);
	void draw() const;


	void hitPaddle(const Paddle& paddle);
	void hitBrick(std::vector<Brick>& bricks);
};
