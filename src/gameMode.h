#pragma once
#include "ofColor.h"
#include "ofSoundPlayer.h"

// Contains many aspects of the overarching game logic. 
class GameMode
{
public:
	enum class gameState { mainMenu, rulesMenu, play, endMenu };

	gameState mode{gameState::mainMenu}; // Set to mainMenu at default from the start.

	// Will either display "Game Over" or "You Win!":
	std::string endMenuText;

	int totalScore{0};
	int totalBricksDestroyed{0};
	int playerLives{3};
	bool orangeBrickHit = false;
	bool redBrickHit = false;

	// Brick Colors:
	ofColor yellowBrickColor = ofColor(220, 220, 0);
	ofColor greenBrickColor = ofColor(0, 200, 0);
	ofColor orangeBrickColor = ofColor(220, 135, 0);
	ofColor redBrickColor = ofColor(220, 0, 0);

	// Music:
	ofSoundPlayer soundtrack;

	/*
	Soundtrack Music from Upbeat : Danijel Zambo
	Chip Mode -
	https://uppbeat.io/t/danijel-zambo/chip-mode
	License code : VT8L9HIDO5YF8HXX
	*/

	void calculateScore(ofColor color);
	void checkPlayerWon();
	void checkPlayerLost();
};
