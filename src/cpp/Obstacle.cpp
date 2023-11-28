#include "../hpp/Obstacle.hpp"
#include <iostream>

Obstacle::Obstacle(Player *myPlayer, QuadTree<sf::Sprite> *quadTree)
{
	Collision::CreateTextureAndBitmask(upObstTexture, OBSTACLE_UP_FILEPATH);
	Collision::CreateTextureAndBitmask(downObstTexture, OBSTACLE_DOWN_FILEPATH);

	this->myPlayer = myPlayer;
	myTree = quadTree;
	obstacleSpeed = OBSTACLE_SPEED;
	spawnGroundObstacle();

	scoreBuffer.loadFromFile(SCORE_SOUND);
	scoreSound.setBuffer(scoreBuffer);
	scoreSound.setPitch(1.5);
}

void Obstacle::setGap(ushort verticalGap)
{
	// setting vertical gap between obstacles
	this->verticalGap = verticalGap;
}

void Obstacle::newGame()
{
	ObstacleSprites.clear();
}

void Obstacle::spawnGroundObstacle()
{
	// initializing fakeGround to collide with
	groundObstacle.setTexture(upObstTexture);
	sf::FloatRect temp;
	temp = groundObstacle.getLocalBounds();
	groundObstacle.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);

	groundObstacle.setRotation(90);
	groundObstacle.setPosition(sf::Vector2f(0, myHeight * 0.6875 * 1.22));
	groundObstacle.setScale(1, 2.5);
}

static bool addScore = true;

void Obstacle::spawnObstacle()
{
	sf::Sprite upObstacle;
	upObstacle.setTexture(upObstTexture);
	float num = (float)myHeight / (float)upObstacle.getLocalBounds().height;
	num /= 1.75;
	upObstacle.setScale(num, num);

	sf::Sprite downObstacle;
	downObstacle.setTexture(downObstTexture);
	downObstacle.setScale(num, num);

	float x = myWidth + upObstacle.getGlobalBounds().width * 0.5f;

	float upLimit = myHeight * 0.1f;
	float downLimit = myHeight * 0.5f;
	// rand between upLimit and downLimit

	int upObstY = rand() % int(downLimit - upLimit) + upLimit;

	upObstacle.setPosition(sf::Vector2f(x, upObstY - upObstacle.getGlobalBounds().height));
	downObstacle.setPosition(sf::Vector2f(x, upObstY + verticalGap));

	ObstacleSprites.push_back(downObstacle);
	ObstacleSprites.push_back(upObstacle);

	addScore = true;
}

void Obstacle::moveObstacles(const float dt)
{
	// removing obstacles that totally passed the screen
	if (ObstacleSprites.front().getPosition().x + ObstacleSprites.front().getGlobalBounds().width < 0)
		ObstacleSprites.pop_front();

	// adds score
	if (addScore && !myPlayer->isCollided())
		if (ObstacleSprites.front().getPosition().x + ObstacleSprites.front().getGlobalBounds().width < myPlayer->startXpos && addScore)
		{
			myPlayer->score++;
			addScore = false;
			scoreSound.play();
		}

	// moving all obstacles to the left
	for (int i = 0; i < ObstacleSprites.size(); i++)
		ObstacleSprites[i].move(-obstacleSpeed * dt, 0);
}

void Obstacle::update(const float dt, Game *game)
{

	if (game->isPaused())
		return;

	if (ObstacleSprites.empty())
		spawnObstacle();

	else if (!myPlayer->isCollided())
	{
		float distanceBetweenObstacles;

		switch (game->getDifficulty())
		{
		case Difficulty::Normal:
			distanceBetweenObstacles = DISTANCE_BETWEEN_OBSTACLES * 1.35;
			obstacleSpeed = OBSTACLE_SPEED;
			break;
		case Difficulty::Hard:
			distanceBetweenObstacles = DISTANCE_BETWEEN_OBSTACLES * 0.875;
			obstacleSpeed = OBSTACLE_SPEED;
			break;
		case Difficulty::Extreme:
			distanceBetweenObstacles = DISTANCE_BETWEEN_OBSTACLES;
			obstacleSpeed = OBSTACLE_SPEED * 1.5;
			break;
		default:
			distanceBetweenObstacles = DISTANCE_BETWEEN_OBSTACLES;
			obstacleSpeed = OBSTACLE_SPEED;
			break;
		}

		moveObstacles(dt);

		if (ObstacleSprites.back().getPosition().x <= myWidth - distanceBetweenObstacles)
			spawnObstacle();
	}

	if (!myPlayer->isCollided())
	{
		for (ushort i = 0; i < ObstacleSprites.size(); i++)
			myTree->insert(&ObstacleSprites[i]);
	}

	spawnGroundObstacle();
	myTree->insert(&groundObstacle);
	scoreSound.setVolume(20);
}

void Obstacle::draw(sf::RenderWindow *myWindow)
{
	for (int i = 0; i < ObstacleSprites.size(); i++)
		myWindow->draw(ObstacleSprites[i]);
}
