#include "paddle.h"
#include "ofGraphics.h"

Paddle::Paddle(const float xPos, const float yPos, const float w, const float h, const bool isFS)
	: xPosition{xPos}, yPosition{yPos}, width{w}, height{h}, isFullSize{isFS}
{
	hitBox.setFromCenter(xPosition, yPosition, width, height);
}

void Paddle::draw() const
{
	ofSetColor(180);
	ofFill();
	ofDrawRectRounded(hitBox, 5);
}
