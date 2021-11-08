#include "ball.h"
#include "ofGraphics.h"
#include "paddle.h"
#include "brick.h"
#include <iostream>

Ball::Ball(const float xPos, const float yPos, const float xSpd, const float ySpd, const float sz)
	: xPosition{xPos}, yPosition{yPos}, xSpeed{xSpd}, ySpeed{ySpd}, size{sz}
{
	hitBox.setFromCenter(xPos, yPos, sz, sz);
}

void Ball::update()
{
	xPosition += xSpeed;
	yPosition += ySpeed;


	// ToDo: Seems hacky, but let's try manually updating the hitBox values within here:
	hitBox.setFromCenter(xPosition, yPosition, size, size);
}

void Ball::edgeBounce(const float canvasWidth, const float canvasHeight)
{
	if (xPosition + (size) > canvasWidth || xPosition - (size) < 0)
	{
		xSpeed *= -1;
	}
	if (yPosition + (size) > canvasHeight || yPosition - (size) < 0)
	{
		ySpeed *= -1;
	}
}


void Ball::draw() const
{
	ofSetColor(255);
	ofFill();
	ofDrawCircle(xPosition, yPosition, size);

	// Visual debugging to see where the ball's hitBox is:
	ofSetColor(0, 155, 255);
	ofFill();
	ofDrawRectangle(hitBox);
}

void Ball::hitPaddle(const Paddle& paddle)
{
	if (hitBox.intersects(paddle.hitBox))
	{
		xSpeed *= -1;
		ySpeed *= -1;
	}
}

void Ball::hitBrick(std::vector<Brick>& bricks)
{
	for (Brick& brick : bricks) // I need this reference. Because it won't work otherwise.
	{
		if (hitBox.intersects(brick.hitBox))
		{
			if (brick.isActive)
			{
				brick.isActive = false;
				xSpeed *= -1;
				ySpeed *= -1;
			}
		}
	}

	// Evil Sorcery at hand:
	//for (short i = 0; i < bricks.size(); ++i)
	//{
	//	if (hitBox.intersects(bricks[i].hitBox))
	//	{
	//		if (bricks[i].isActive)
	//		{
	//			bricks[i].isActive = false;
	//			xSpeed *= -1;
	//			ySpeed *= -1;
	//		}
	//	}
	//}
}
