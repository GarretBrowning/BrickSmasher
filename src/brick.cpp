#include "brick.h"
#include "ofGraphics.h"

Brick::Brick(float xPos, float yPos, float w, float h, ofColor c, bool active)
	: xPosition{xPos}, yPosition{yPos}, width{w}, height{h}, color{c}, isActive{active}
{
	hitBox.set(xPos, yPos, w, h);
}

void Brick::draw()
{
	if (isActive)
	{
		// Drawing the brick to the canvas using the given color:
		ofSetColor(color);
		ofFill();
		ofDrawRectangle(hitBox);

		// Setting the thick black border around the brick:
		ofSetColor(0);
		ofSetLineWidth(5);
		ofNoFill();
		ofDrawRectangle(hitBox);
	}
}
