#include "paddle.h"
#include "ofGraphics.h"

Paddle::Paddle(float xPos, float yPos, float w, float h)
	: xPosition{xPos}, yPosition{yPos}, width{w}, height{h}
{
	hitBox.setFromCenter(xPos, yPos, w, h);
}

void Paddle::draw()
{
	ofSetColor(230, 50);
	//ofSetRectMode(OF_RECTMODE_CENTER); // Need to be careful as this is where the rectmode is set!!
	/*hitBox.setFromCenter(xPosition, yPosition, width, height);*/
	ofFill();
	ofDrawRectangle(hitBox);
}
