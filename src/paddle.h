#pragma once
#include "ofRectangle.h"

class Paddle
{
public:
	// Default values for the player paddle (currently all Magic Numbers):
	float xPosition{512.0}; // Default canvas Width/2.
	const float yPosition{720.0}; // Default canvas Height - Height/16. 
	float width{100.0};
	float height{20.0};
	bool isFullSize{true};
	ofRectangle hitBox{xPosition, yPosition, width, height};

	// Constructors:
	Paddle() = default;
	Paddle(float xPos, float yPos, float w, float h, bool isFS);

	void draw() const;
};
