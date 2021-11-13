#include "brick.h"
#include "ofGraphics.h"

Brick::Brick(const float xPos, const float yPos, const float w, const float h, const ofColor c, const bool active)
	: xPosition{xPos}, yPosition{yPos}, width{w}, height{h}, color{c}, isActive{active}
{
	hitBox.set(xPosition, yPosition, width, height);
}

void Brick::draw() const
{
	if (isActive)
	{
		// Drawing the brick to the canvas using the given color:
		ofSetColor(color);
		ofFill();
		ofDrawRectRounded(hitBox, 4);

		// Setting the thick dark grey border around the brick:
		ofSetColor(0);
		ofSetLineWidth(5);
		ofNoFill();
		ofDrawRectRounded(hitBox, 4);
	}
}
