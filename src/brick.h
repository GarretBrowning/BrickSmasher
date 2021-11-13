#pragma once
#include "ofColor.h"
#include "ofRectangle.h"

class Brick
{
	const float xPosition;
	const float yPosition;
	const float width;
	const float height;

public:
	const ofColor color;
	bool isActive;
	ofRectangle hitBox;

	// Constructor:
	Brick(float xPos, float yPos, float w, float h, ofColor c, bool active);

	void draw() const;
};
