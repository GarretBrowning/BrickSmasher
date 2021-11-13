#pragma once
#include "ofMain.h"
#include "gameMode.h"
#include "paddle.h"
#include "ball.h"
#include "brick.h"
#include <vector>

class ofApp : public ofBaseApp
{
	// Canvas Dimensions:
	const float windowWidth{1024};
	const float windowHeight{768};
	const float hudGap = 100.0f; // Gap for the HUD to fit at the top of the canvas.

	// Brick Wall Constants:
	const short numberOfRows{8};
	const short bricksPerRow{14};
	const float brickWidth{windowWidth / 14};
	const float brickHeight{brickWidth / 3};

	std::vector<Brick> bricks;

	// Initializing the GameMode, Ball, and Paddle:
	GameMode gameMode;
	Paddle paddle;
	Ball ball;

	// Fonts:
	ofTrueTypeFont hudFont;
	ofTrueTypeFont titleFont;
	ofTrueTypeFont buttonFont;
	ofTrueTypeFont rulesFont;

	// Menu Buttons:
	ofRectangle playButton;
	ofRectangle rulesButton;
	ofRectangle quitButton;

	// HUD Text:
	std::string scoreText;
	std::string livesText = "Lives:  III";

	// Button Text:
	const std::string playButtonText = "Play";
	const std::string rulesButtonText = "Rules";
	const std::string quitButtonText = "Quit";

	// Main Menu Text:
	const std::string titleText = "BRICK SMASHER";

	// Rules Menu Text:
	const std::string rulesTitleText = "RULES";
	const std::string rulesText1 = "The goal of Brick Smasher is to destroy all of the bricks.";
	const std::string rulesText2 = "Move the paddle using the mouse. Bounce the ball off the paddle to smash bricks.";
	const std::string rulesText3 = "Each game starts with 3 lives. If the ball touches the bottom you lose a life.";
	const std::string rulesText4 = "You lose if you run out of lives.";

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
};
