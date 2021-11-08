#pragma once

#include "ofMain.h"
#include "paddle.h"
#include "ball.h"
#include "brick.h"
#include "vector"

class ofApp : public ofBaseApp
{
public:
	void setup() override;
	void update() override;
	void draw() override;

	void keyPressed(int key) override;
	void keyReleased(int key) override;
	void mouseMoved(int x, int y) override;
	void mouseDragged(int x, int y, int button) override;
	void mousePressed(int x, int y, int button) override;
	void mouseReleased(int x, int y, int button) override;
	void mouseEntered(int x, int y) override;
	void mouseExited(int x, int y) override;
	void windowResized(int w, int h) override;
	void dragEvent(ofDragInfo dragInfo) override;
	void gotMessage(ofMessage msg) override;


	const int bricksPerRow{14};
	const int numberOfRows{8};
	const int windowWidth{1024};
	const int windowHeight{768};

	Paddle paddle;
	Ball ball;
	std::vector<Brick> bricks;

	// Music:
	ofSoundPlayer soundtrack;
	ofSoundPlayer paddleBounce;
	ofSoundPlayer brickBounce;
	ofSoundPlayer loseLife;

	/*
	Soundtrack Music from Uppbeat : Danijel Zambo
	Chip Mode -
	https://uppbeat.io/t/danijel-zambo/chip-mode
	License code : VT8L9HIDO5YF8HXX

	paddleBounce, brickBounce, and loseLife sound effects from Atari.
	Converted to mp3 from this video:
	https://www.youtube.com/watch?v=qhaS2uMNTjI&ab_channel=AnthonyCassimiro
	*/
};
