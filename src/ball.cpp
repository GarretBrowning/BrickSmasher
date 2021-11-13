#include "ball.h"
#include "gameMode.h"
#include "brick.h"
#include "paddle.h"
#include "ofGraphics.h"

Ball::Ball(float sz, ofVec3f vel, ofVec3f pos)
	: size{sz}, position{pos}, velocity{vel}
{
	hitBox.setFromCenter(position.x, position.y, size * 1.3f, size * 1.3f);
}

void Ball::update()
{
	position += velocity;

	// Useful debugging lines to set the ball's position to where the mouse is located:
	//position.x = ofGetMouseX();
	//position.y = ofGetMouseY();

	// Update the hitbox's position and set from center:
	hitBox.setFromCenter(position.x, position.y, size * 1.3f, size * 1.3f);
}

void Ball::edgeBounce(const float canvasWidth, const float canvasHeight, Paddle& paddle, GameMode& gameMode)
{
	// If the ball hits the side wall, bounce it in the other direction:
	if (position.x + size > canvasWidth || position.x - size < 0)
	{
		velocity.x *= -1;
	}

	// When the ball hits the top of the canvas, shrink the paddle to half its size:
	if (position.y - size < 0)
	{
		velocity.y *= -1;

		if (paddle.isFullSize)
		{
			paddle.width *= 0.5f;
			paddle.isFullSize = false;
		}
	}

	// Whenever the ball hits the bottom of the canvas, subtract a life and check to see if player loses:
	if (position.y + size > canvasHeight)
	{
		velocity.y *= -1;
		gameMode.playerLives--;
		loseLifeSFX.play();
		gameMode.checkPlayerLost();
	}
}

void Ball::hitPaddle(const Paddle& paddle)
{
	if (hitBox.intersects(paddle.hitBox))
	{
		// Find the center of the hitBox for both the paddle and the ball:
		const float paddleHitBoxCenter = paddle.hitBox.getPosition().x + (paddle.width / 2);
		const float ballHitBoxCenter = hitBox.position.x + (size / 2);

		// Find the delta between the paddle's hitbox center and the ball's hitbox center:
		const float deltaPosition = paddleHitBoxCenter - ballHitBoxCenter;

		// Set the new bounce angle for the ball based upon the delta position relative to the center of the paddle within the range of maxBounceAngle:
		const float newBounceAngle = (deltaPosition / (paddle.width / 2)) * maxBounceAngle;

		// Set the ball's x and y velocity based upon the delta position (cos for x, -sin for y) relative to the center of the paddle:
		velocity.x += cos(newBounceAngle) * deltaPosition / (paddle.width / 2);
		velocity.y += -sin(newBounceAngle) * deltaPosition / (paddle.width / 2);

		// Change the ball's direction depending on it's current direction and where it hits the paddle's hitbox:
		if (deltaPosition < 0 && velocity.x < 0 || deltaPosition >= 0 && velocity.x >= 0)
		{
			velocity.x *= -1;
		}

		// Set the y velocity to bounce back upwards:
		velocity.y *= -1;

		// Set a limit on the new calculated velocity:
		velocity.limit(limit);

		// Play SFX on hit:
		paddleHitSFX.play();
	}
}

void Ball::hitBrick(std::vector<Brick>& bricks, GameMode& gameMode)
{
	// Loop through all of the bricks to check if any have been intersected by the ball's hitbox:
	for (Brick& brick : bricks)
	{
		if (hitBox.intersects(brick.hitBox))
		{
			if (brick.isActive)
			{
				// Play SFX:
				brickHitSFX.play();

				// Hide brick from play (destroyed):
				brick.isActive = false;

				// Bounce the ball off of the brick:
				velocity.y *= -1; // ToDo: Change to a more specific ball velocity calculation upon brick impact.

				// Add to the player's score and check to see if they have won the game:
				gameMode.calculateScore(brick.color);
				gameMode.checkPlayerWon();
			}
		}
	}

	// Speeding up the ball & game soundtrack based upon the following conditions:
	if (gameMode.totalBricksDestroyed == 4)
	{
		velocity *= 1.2;
		limit = 5;
		velocity.limit(limit);
		gameMode.soundtrack.setSpeed(1.02f);
	}
	if (gameMode.totalBricksDestroyed == 12)
	{
		velocity *= 1.2;
		limit = 7;
		velocity.limit(limit);
		gameMode.soundtrack.setSpeed(1.04f);
	}
	if (gameMode.orangeBrickHit)
	{
		velocity *= 1.2;
		limit = 9;
		velocity.limit(limit);
		gameMode.soundtrack.setSpeed(1.06f);
	}
	if (gameMode.redBrickHit)
	{
		velocity *= 1.2;
		limit = 11;
		velocity.limit(limit);
		gameMode.soundtrack.setSpeed(1.08f);
	}
}

void Ball::draw() const
{
	ofSetColor(255);
	ofFill();
	ofDrawCircle(position.x, position.y, size);

	// Useful visual debugging lines to see where the ball's hitBox is:
	//ofSetColor(0, 155, 255);
	//ofFill();
	//ofDrawRectangle(hitBox);
}

void Ball::reset()
{
	limit = 4;
	position = ofVec3f(512.0f, 384.0f, 0);
	velocity = ofVec3f(ofRandom(-3.0f, -1.8f), ofRandom(1.8f, 3.0f), 0);
}
