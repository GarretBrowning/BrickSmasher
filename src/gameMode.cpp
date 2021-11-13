#include "gameMode.h"

void GameMode::calculateScore(ofColor color)
{
	if (color == yellowBrickColor)
	{
		totalScore += 1;
	}
	else if (color == greenBrickColor)
	{
		totalScore += 3;
	}
	else if (color == orangeBrickColor)
	{
		totalScore += 5;
		orangeBrickHit = true;
	}
	else if (color == redBrickColor)
	{
		totalScore += 7;
		redBrickHit = true;
	}
	totalBricksDestroyed += 1;
}

void GameMode::checkPlayerWon()
{
	if (totalBricksDestroyed == 112 && totalScore == 448)
	{
		endMenuText = "You Win!";
		mode = gameState::endMenu;
	}
}

void GameMode::checkPlayerLost()
{
	if (playerLives < 1)
	{
		endMenuText = "Game Over";
		mode = gameState::endMenu;
	}
}
