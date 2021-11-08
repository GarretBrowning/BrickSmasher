#pragma once
#include "ofRectangle.h"

class Paddle
{
public:
	// Default values for the player paddle (currently all Magic Numbers):
	float xPosition{512.0}; // Default canvas Width/2.
	float yPosition{720.0}; // Default canvas Height - Height/16. 
	float width{100.0};
	float height{20.0};
	ofRectangle hitBox{xPosition, yPosition, width, height};
	//ofRectangle hitBox;

	// Constructor:
	Paddle() = default;
	Paddle(float xPos, float yPos, float w, float h);

	// Member functions:
	void draw();
};
