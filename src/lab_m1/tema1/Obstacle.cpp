#include "Obstacle.h"

Obstacle::Obstacle(glm::vec2 position, float width, float height) {
	this->position = position;
	this->width = width;
	this->height = height;

	this->left = position.x;
	this->right = position.x + width;
	this->top = position.y + height;
	this->bottom = position.y;
}

bool Obstacle::ObstacleCollision(glm::vec2 playerPos, float radius) {
		
	if (this->left >= playerPos.x + radius) return false;
	if (this->right <= playerPos.x - radius) return false;
	if (this->top <= playerPos.y - radius) return false;
	if (this->bottom >= playerPos.y + radius) return false;

	return true;

}
