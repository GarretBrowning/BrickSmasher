#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetWindowTitle("Brick Smasher");
	ofSetBackgroundColor(21);

	//Loading Fonts:
	hudFont.load("fonts/Library3am.otf", 21);
	titleFont.load("fonts/PixelGosub.ttf", 90);
	buttonFont.load("fonts/ThirteenPixelFontsRegular.ttf", 45);
	rulesFont.load("fonts/PixelGosub.ttf", 16);

	// Loading, Setting the Volume, and Playing the Game Soundtrack:
	gameMode.soundtrack.load("sounds/chipmode.mp3");
	gameMode.soundtrack.setVolume(0.4f);
	gameMode.soundtrack.play();

	// Loading the on-hit SFX:
	ball.paddleHitSFX.load("sounds/paddleBounce.mp3");
	ball.brickHitSFX.load("sounds/brickBounce.mp3");
	ball.loseLifeSFX.load("sounds/loseLife.mp3");

	// Fine tuning of the SFX:
	ball.paddleHitSFX.setVolume(0.75f);
	ball.brickHitSFX.setSpeed(0.5f);
	ball.loseLifeSFX.setVolume(0.75f);

	// Populating the Brick Wall (vector):
	for (short x = 0; x < numberOfRows; x++)
	{
		for (short y = 0; y < bricksPerRow; ++y)
		{
			const float xPosition = brickWidth * static_cast<float>(y);
			const float yPosition = (hudGap) + (brickHeight * static_cast<float>(x));
			ofColor color;

			// Every two rows change the color of the brick:
			if (x < 2)
			{
				color = gameMode.redBrickColor;
			}
			else if (x < 4)
			{
				color = gameMode.orangeBrickColor;
			}
			else if (x < 6)
			{
				color = gameMode.greenBrickColor;
			}
			else
			{
				color = gameMode.yellowBrickColor;
			}
			bricks.emplace_back(xPosition, yPosition, brickWidth, brickHeight, color, true);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	// Updates the sound playing system:
	ofSoundUpdate();

	// Ensuring that the soundtrack is playing on-loop:
	if (!gameMode.soundtrack.isPlaying())
	{
		gameMode.soundtrack.play();
	}

	// Prevents the window from being resized:
	if (ofGetWidth() != windowWidth || ofGetHeight() != windowHeight)
	{
		ofSetWindowShape(windowWidth, windowHeight);
	}

	switch (gameMode.mode)
	{
	case GameMode::gameState::mainMenu:
		break;

	case GameMode::gameState::rulesMenu:
		break;

	case GameMode::gameState::play:
		// Hide the mouse cursor during play:
		ofHideCursor();

		// Update the ball's position and check to see if it's hit anything:
		ball.update();
		ball.hitPaddle(paddle);
		ball.hitBrick(bricks, gameMode);
		ball.edgeBounce(windowWidth, windowHeight, paddle, gameMode);

		// Update Score:
		scoreText = "Score:  " + std::to_string(gameMode.totalScore);

		// Update Lives:
		if (gameMode.playerLives == 2)
		{
			livesText = "Lives:  II";
		}
		else if (gameMode.playerLives == 1)
		{
			livesText = "Lives:  I";
		}
		else if (gameMode.playerLives < 1)
		{
			livesText = "Lives:";
		}
		break;

	case GameMode::gameState::endMenu:
		ofShowCursor();

		// Reset the ball's position and acceleration:
		ball.reset();
		gameMode.orangeBrickHit = false;
		gameMode.redBrickHit = false;

		// Reset the paddle size:
		if (!paddle.isFullSize)
		{
			paddle.width *= 2;
			paddle.isFullSize = true;
		}

		// Reset the brick wall (set all bricks to active):
		for (auto& brick : bricks)
		{
			brick.isActive = true;
		}
		gameMode.totalBricksDestroyed = 0;

		// Reset the HUD values:
		gameMode.totalScore = 0;
		gameMode.playerLives = 3;
		livesText = "Lives:  III";

		// Reset the speed of the soundtrack:
		gameMode.soundtrack.setSpeed(1);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	// Setting up initial TextBox sizes in order to calculate offsets for centering purposes:
	ofRectangle titleTextBox = titleFont.getStringBoundingBox(titleText, 0, ofGetHeight() / 2);
	ofRectangle endMenuTextBox = titleFont.getStringBoundingBox(gameMode.endMenuText, 0, ofGetHeight() / 2);
	ofRectangle playButtonTextBox = buttonFont.getStringBoundingBox(playButtonText, 0, ofGetHeight() / 2);
	ofRectangle rulesButtonTextBox = buttonFont.getStringBoundingBox(rulesButtonText, 0, ofGetHeight() / 1.5);
	ofRectangle quitButtonTextBox = buttonFont.getStringBoundingBox(quitButtonText, 0, ofGetHeight() / 1.5);

	// Calculating the x offset in order to center each element:
	float titleOffsetX = (ofGetWidth() - titleTextBox.width) / 2;
	float endMenuOffsetX = (ofGetWidth() - endMenuTextBox.width) / 2;
	float playButtonOffsetX = (ofGetWidth() - playButtonTextBox.width) / 2;
	float rulesButtonOffsetX = (ofGetWidth() - rulesButtonTextBox.width) / 2;
	float quitButtonOffsetX = (ofGetWidth() - quitButtonTextBox.width) / 2;

	// Setting the necessary values for the TextBox with the newly calculated offsets (needed for button logic later):
	playButton = buttonFont.getStringBoundingBox(playButtonText, playButtonOffsetX, ofGetHeight() / 2);
	rulesButton = buttonFont.getStringBoundingBox(rulesButtonText, rulesButtonOffsetX, ofGetHeight() / 1.5);
	quitButton = buttonFont.getStringBoundingBox(quitButtonText, rulesButtonOffsetX, ofGetHeight() / 1.5);

	// Rules:
	ofRectangle rulesTitleTextBox = titleFont.getStringBoundingBox(rulesTitleText, 0, ofGetHeight() / 2);
	float rulesTitleOffsetX = (ofGetWidth() - rulesTitleTextBox.width) / 2;

	// TextBoxes for the rules:
	ofRectangle rules1TextBox = rulesFont.getStringBoundingBox(rulesText1, 0, ofGetHeight() / 1.5);
	ofRectangle rules2TextBox = rulesFont.getStringBoundingBox(rulesText2, 0, ofGetHeight() / 1.5 + 50);
	ofRectangle rules3TextBox = rulesFont.getStringBoundingBox(rulesText3, 0, ofGetHeight() / 1.5 + 100);
	ofRectangle rules4TextBox = rulesFont.getStringBoundingBox(rulesText4, 0, ofGetHeight() / 1.5 + 150);

	// Rules Offsets to make the text centered:
	float rules1TextOffsetX = (ofGetWidth() - rules1TextBox.width) / 2;
	float rules2TextOffsetX = (ofGetWidth() - rules2TextBox.width) / 2;
	float rules3TextOffsetX = (ofGetWidth() - rules3TextBox.width) / 2;
	float rules4TextOffsetX = (ofGetWidth() - rules4TextBox.width) / 2;

	switch (gameMode.mode)
	{
	case GameMode::gameState::mainMenu:
		// Title:
		titleFont.drawString(titleText, titleOffsetX, ofGetHeight() / 5);
		// Button Text:
		buttonFont.drawString(playButtonText, playButtonOffsetX, ofGetHeight() / 2);
		buttonFont.drawString(rulesButtonText, rulesButtonOffsetX, ofGetHeight() / 1.5);
		break;

	case GameMode::gameState::rulesMenu:
		// Title:
		titleFont.drawString(rulesTitleText, rulesTitleOffsetX, ofGetHeight() / 5);
		// Play Button:
		buttonFont.drawString(playButtonText, playButtonOffsetX, ofGetHeight() / 2);
		// Rules:
		rulesFont.drawString(rulesText1, rules1TextOffsetX, ofGetHeight() / 1.5);
		rulesFont.drawString(rulesText2, rules2TextOffsetX, ofGetHeight() / 1.5 + 50);
		rulesFont.drawString(rulesText3, rules3TextOffsetX, ofGetHeight() / 1.5 + 100);
		rulesFont.drawString(rulesText4, rules4TextOffsetX, ofGetHeight() / 1.5 + 150);
		break;

	case GameMode::gameState::play:
		// Draw the ball, paddle, and bricks to the screen:
		ball.draw();
		paddle.draw();
		for (const Brick& brick : bricks)
		{
			brick.draw();
		}
		// Draw the HUD elements:
		ofSetColor(255);
		hudFont.drawString(scoreText, (ofGetWidth() / 15) / 2, ofGetHeight() / 17);
		hudFont.drawString(livesText, ofGetWidth() - (ofGetWidth() / 6), ofGetHeight() / 17);
		break;

	case GameMode::gameState::endMenu:
		// Title:
		titleFont.drawString(gameMode.endMenuText, endMenuOffsetX, ofGetHeight() / 5);
		// Button Text:
		buttonFont.drawString(playButtonText, playButtonOffsetX, ofGetHeight() / 2);
		buttonFont.drawString(quitButtonText, quitButtonOffsetX, ofGetHeight() / 1.5);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
	// Takes in the current mouse x-position and sets the paddle's x-position to that value:
	paddle.hitBox.setFromCenter(x, paddle.yPosition, paddle.width, paddle.height);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	// Selects the game mode within the Main Menu screen:
	if (button == 0 && gameMode.mode == GameMode::gameState::mainMenu)
	{
		// Play button:
		if (
			x >= playButton.x &&
			x < playButton.x + playButton.getWidth() &&
			y >= playButton.y &&
			y < playButton.y + playButton.getHeight()
		)
		{
			gameMode.mode = GameMode::gameState::play;
		}
			// Rules button:
		else if (
			x >= rulesButton.x &&
			x < rulesButton.x + rulesButton.getWidth() &&
			y >= rulesButton.y &&
			y < rulesButton.y + rulesButton.getHeight()
		)
		{
			gameMode.mode = GameMode::gameState::rulesMenu;
		}
	}

	// Selects the game mode within the Rules Menu screen:
	if (button == 0 && gameMode.mode == GameMode::gameState::rulesMenu)
	{
		// Play button:
		if (
			x >= playButton.x &&
			x < playButton.x + playButton.getWidth() &&
			y >= playButton.y &&
			y < playButton.y + playButton.getHeight()
		)
		{
			gameMode.mode = GameMode::gameState::play;
		}
	}

	// Selects the game mode within the End Menu screen:
	if (button == 0 && gameMode.mode == GameMode::gameState::endMenu)
	{
		// Play button:
		if (
			x >= playButton.x &&
			x < playButton.x + playButton.getWidth() &&
			y >= playButton.y &&
			y < playButton.y + playButton.getHeight()
		)
		{
			gameMode.mode = GameMode::gameState::play;
		}
			// Quit button:
		else if (
			x >= quitButton.x &&
			x < quitButton.x + quitButton.getWidth() &&
			y >= quitButton.y &&
			y < quitButton.y + quitButton.getHeight()
		)
		{
			ofExit();
		}
	}
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
