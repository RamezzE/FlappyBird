#include "Obstacle.h"
#include <iostream>

Obstacle::Obstacle() {

	upObstTexture.loadFromFile(OBSTACLE_UP_FILEPATH);
	downObstTexture.loadFromFile(OBSTACLE_DOWN_FILEPATH);

	movementSpeed = (float)myHeight/4.0f;

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
	fakeObstacle.setPosition(sf::Vector2f(0, myHeight * 0.6875 * 1.2 + 10));
	fakeObstacle.setScale(1, 2.5);
}

sf::Sprite Obstacle::spawnGround() {
	return fakeObstacle;
}

static bool addScore = true;

void Obstacle::spawnObstacle()
{
	if (ObstacleSprites.size() != 0) { // checks when to insert next obstacle if the vector isn't empty
		if (ObstacleSprites.back().getPosition().x > myWidth - distanceBetweenObstacles) return;
	}

	sf::Sprite upObstacle;
	upObstacle.setTexture(upObstTexture);
	float num = (float)myHeight / (float)upObstacle.getLocalBounds().height;
	num /= 1.75;
	upObstacle.setScale(num, num);

	sf::Sprite downObstacle;
	downObstacle.setTexture(downObstTexture);
	num = (float)myHeight / (float)downObstacle.getLocalBounds().height;
	num /= 1.75;
	downObstacle.setScale(num, num);
	
	float x = myWidth + upObstacle.getGlobalBounds().width * 0.5f;

	//sf::FloatRect bounds = upObstacle.getLocalBounds();

	float upLimit = myHeight*0.1f;
	float downLimit = myHeight*0.5f;
	//rand between upLimit and downLimit

	int upObstY = rand() % int(downLimit-upLimit) + upLimit;
	//int downObstY = upObstY;

	upObstacle.setPosition(sf::Vector2f(x, upObstY-upObstacle.getGlobalBounds().height));
	downObstacle.setPosition(sf::Vector2f(x, upObstY+verticalGap));

	//pushes spawned obstacles into the vector
	ObstacleSprites.push_back(downObstacle);
	ObstacleSprites.push_back(upObstacle);

	addScore = true;
}

void Obstacle::drawObstacles(sf::RenderWindow* myWindow)
{
	//sf::RectangleShape rect;

	myWindow->draw(fakeObstacle);
	for (int i = 0; i < ObstacleSprites.size(); i++) {
		myWindow->draw(ObstacleSprites[i]);

		/*rect.setOrigin(ObstacleSprites[i].getOrigin());
		rect.setPosition(ObstacleSprites[i].getPosition().x, ObstacleSprites[i].getPosition().y);
		rect.setSize(sf::Vector2f(ObstacleSprites[i].getGlobalBounds().width, ObstacleSprites[i].getGlobalBounds().height));

		rect.setFillColor(sf::Color(34, 133, 23, 150));*/
		//myWindow->draw(rect);
	}
}

bool Obstacle::moveObstacles(QuadTree& quadTree, float dt, Player player, unsigned short& score)
{
	if (ObstacleSprites.empty()) return false; // no obstacles to move

	//removing obstacles that totally passed the screen
	if (ObstacleSprites.front().getPosition().x + ObstacleSprites.front().getGlobalBounds().width < 0) {
		ObstacleSprites.pop_front();
	}

	//adds score 
	if (addScore) {
		if (ObstacleSprites.front().getPosition().x + ObstacleSprites.front().getGlobalBounds().width < player.startXpos && addScore) {
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


