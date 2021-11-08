#include "ofApp.h"
#include <iostream>

//--------------------------------------------------------------
void ofApp::setup()
{
	// Soundtrack:
	soundtrack.load("sounds/chipmode.mp3");
	soundtrack.setVolume(0.4f);
	//soundtrack.play();
	// Eventual nice-to-have: Music Speeds up when ball/game speeds up!

	paddleBounce.load("sounds/paddleBounce.mp3");
	brickBounce.load("sounds/brickBounce.mp3");
	loseLife.load("sounds/loseLife.mp3");

	paddleBounce.setVolume(0.75f);
	brickBounce.setSpeed(0.5f);
	loseLife.setVolume(0.75f);


	// Temporary, could move to .h later:
	int brickWidth{windowWidth / 14};
	int brickHeight{brickWidth / 3};
	float menuGap = 100.0;

	for (short x = 0; x < numberOfRows; x++)
	{
		for (short y = 0; y < bricksPerRow; ++y)
		{
			const float xPosition = brickWidth * static_cast<float>(y);
			const float yPosition = (menuGap) + (brickHeight * static_cast<float>(x));
			const float width = brickWidth;
			const float height = brickHeight;
			ofColor color;
			if (x < 2)
			{
				color = ofColor(255, 0, 0);
			}
			else if (x < 4)
			{
				color = ofColor(255, 165, 0);
			}
			else if (x < 6)
			{
				color = ofColor(0, 255, 0);
			}
			else
			{
				color = ofColor(255, 255, 0);
			}
			bricks.emplace_back(xPosition, yPosition, width, height, color, true);
		}
	}

	// Test Code for displaying 1 brick:
	//Brick brick
	//{
	//	static_cast<float>(ofGetWidth()) / 2,
	//	static_cast<float>(ofGetHeight()) / 2,
	//	static_cast<float>(brickWidth),
	//	static_cast<float>(brickHeight),
	//	ofColor(255, 0, 0),
	//	true
	//};
	//bricks.emplace_back(brick);
}

//--------------------------------------------------------------
void ofApp::update()
{
	// Prevents the window from being resized:
	if (ofGetWidth() != windowWidth || ofGetHeight() != windowHeight)
	{
		ofSetWindowShape(windowWidth, windowHeight);
	}


	ball.update();
	ball.hitPaddle(paddle);
	ball.hitBrick(bricks);
	ball.edgeBounce(windowWidth, windowHeight);

	// Updates the sound playing system:
	ofSoundUpdate();
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ball.draw();
	paddle.draw();
	for (Brick brick : bricks)
	{
		if (brick.isActive)
		{
			//std::cout << "isActive = " << brick.isActive << "\n";
			brick.draw();
		}
	}

	// Ensuring that the soundtrack is playing on-loop:
	/*if (!soundtrack.isPlaying())
	{
		soundtrack.play();
	}*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	// ToDo: DELETE LATER - Simply used for testing purposes for now:
	if (key == 'z')
	{
		paddleBounce.play();
	}

	if (key == 'x')
	{
		brickBounce.play();
	}

	if (key == 'c')
	{
		loseLife.play();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	// Takes in the current mouse X-position and sets the paddle's X-position to that value:
	paddle.hitBox.setFromCenter(x, paddle.yPosition, paddle.width, paddle.height);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
