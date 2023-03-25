#include "Obstacle.h"
#include <iostream>

Obstacle::Obstacle() {

	upObstTexture.loadFromFile(OBSTACLE_UP_FILEPATH);
	downObstTexture.loadFromFile(OBSTACLE_DOWN_FILEPATH);

	movementSpeed = 200;

	spawnFakeGround();
}

void Obstacle::setGap(unsigned short distanceBetweenObstacles, unsigned short verticalGap) {

	//setting horizontal and vertical gap between obstacles

	this->distanceBetweenObstacles = distanceBetweenObstacles;
	this->verticalGap = verticalGap;
}

void Obstacle::spawnFakeGround() {

	//initializing fakeGround to collide with
	fakeObstacle.setTexture(upObstTexture);
	sf::FloatRect temp;
	temp = fakeObstacle.getLocalBounds();
	fakeObstacle.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);

	fakeObstacle.setRotation(90);
	fakeObstacle.setPosition(sf::Vector2f(0, OBSTACLE_AREA * 1.2 + 10));
	fakeObstacle.setScale(1, 2.5);
}

sf::Sprite Obstacle::spawnGround() {
	return fakeObstacle;
}

static bool addScore = true;

void Obstacle::spawnObstacle()
{
	if (ObstacleSprites.size() != 0) { // checks when to insert next obstacle if the vector isn't empty
		if (ObstacleSprites.back().getPosition().x > SCREEN_WIDTH - distanceBetweenObstacles) return;
	}

	sf::Sprite upObstacle;
	upObstacle.setTexture(upObstTexture);

	sf::Sprite downObstacle;
	downObstacle.setTexture(downObstTexture);

	int x = SCREEN_WIDTH + upObstacle.getLocalBounds().width / 2;

	int upperlimit = OBSTACLE_AREA * 0.45;
	int downObstY = rand() % int(OBSTACLE_AREA - upperlimit) + upperlimit;

	int upObstY = downObstY - verticalGap - upObstacle.getLocalBounds().height * 0.9;

	upObstacle.setPosition(sf::Vector2f(x, upObstY));
	downObstacle.setPosition(sf::Vector2f(x, downObstY));

	//pushes spawned obstacles into the vector
	ObstacleSprites.push_back(upObstacle);
	ObstacleSprites.push_back(downObstacle);

	addScore = true;

}

void Obstacle::drawObstacles(sf::RenderWindow* myWindow)
{
	for (int i = 0; i < ObstacleSprites.size(); i++) {
		myWindow->draw(ObstacleSprites[i]);
	}
}

bool Obstacle::moveObstacles(QuadTree& quadTree, float dt, Player player, unsigned short& score)
{
	if (ObstacleSprites.empty()) return false; // no obstacles to move

	//removing obstacles that totally passed the screen
	if (ObstacleSprites.front().getPosition().x + ObstacleSprites.front().getLocalBounds().width < 0) {
		ObstacleSprites.pop_front();
	}

	//adds score 
	if (addScore) {
		if (ObstacleSprites.front().getPosition().x + ObstacleSprites.front().getLocalBounds().width < player.startXpos && addScore) {
			score++;
			addScore = false;
		}
	}

	//moving all obstacles to the left
	for (int i = 0; i < ObstacleSprites.size(); i++) {
		ObstacleSprites[i].move(-movementSpeed * dt, 0);
	}

	return true;
}


