#include "Enemy.h"

#include "transform2D.h"
#include <iostream>

using namespace std;

Enemy::Enemy(Mesh* mesh, Mesh* fist, Mesh* death,  Shader* shader, Survivio* instance)
{
	this->mesh = mesh;
	this->shader = shader;
	this->fist = fist;
	this->death = death;
	this->destroyTime = 0;
	this->hitPlayer = false;

	survInstance = instance;

	dead = false;
}

Enemy::~Enemy()
{

}

void Enemy::Draw() {
	this->UpdateTransformMatrix();
	survInstance->DrawMesh2D(mesh, shader, this->GetTransformMatrix());

	glm::mat3 tr = transform2D::Translate(50, -30);

	// Draw left fist
	survInstance->DrawMesh2D(fist, shader, this->GetTransformMatrix() * tr);

	tr = transform2D::Translate(50, 30);

	// Draw right fist
	survInstance->DrawMesh2D(fist, shader, this->GetTransformMatrix() * tr);
}

void Enemy::PointTowards(glm::vec2 worldSpacePoint) {
	glm::vec2 position = GetPosition();
	SetRotation(atan2((worldSpacePoint.y - position.y), (worldSpacePoint.x - position.x)));

}

void Enemy::AdvanceTowards(glm::vec2 worldSpacePoint, float deltaTime) {
	glm::vec2 direction = worldSpacePoint - GetPosition();
	
	if (glm::length(direction) < 100.0f) {
		//DestroyAnimation(0);
		this->hitPlayer = true;
		this->dead = true;
	}
	
	Translate(glm::normalize(direction) * this->speed * deltaTime);
}

bool Enemy::DestroyAnimation(float deltaTimeSeconds) {
	this->destroyTime += deltaTimeSeconds;
	if (this->destroyTime >= 250) {
		return true;
	}
	survInstance->DrawMesh2D(death, shader, this->GetTransformMatrix());
	return false;
}

bool Enemy::BulletCollision(glm::vec2 worldSpacePoint) {
	glm::vec2 direction = worldSpacePoint - GetPosition();
	if (glm::length(direction) < 45.0f) {
		//DestroyAnimation(0);
		this->dead = true;
		return true;
	}
	return false;
}