#pragma once
#include "ofColor.h"
#include "ofRectangle.h"

class Brick
{
public:
	float xPosition;
	float yPosition;
	float width;
	float height;
	ofColor color;
	bool isActive;

	ofRectangle hitBox;
	// Constructor:
	Brick(float xPos, float yPos, float w, float h, ofColor c, bool active);

	void draw();
};
