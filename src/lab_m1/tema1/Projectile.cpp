#include "Projectile.h"

using namespace std;

Projectile::Projectile(Mesh* mesh, Shader* shader, glm::vec2 position, glm::vec2 target, Survivio* instance )
{
	dead = false;
	aliveTime = 0;
	//fireRate = 0;

	this->mesh = mesh;
	this->shader = shader;
	survInstance = instance;
	
	SetRotationPivot(glm::vec2(5, 15));

	SetPosition(position);

	// Se normalizeaza pentru ca vrem doar directia, nu ne intereseaza magnitudinea.
	// ( pentru a asigura viteza constanta, indiferent de distanta dintre personaj si mouse )
	direction = glm::normalize(target - position);

	PointTowards(target);
}

Projectile::~Projectile()
{
}


void Projectile::Draw() {
	this->UpdateTransformMatrix();
	survInstance->DrawMesh2D(mesh, shader, this->GetTransformMatrix());
}

void Projectile::PointTowards(glm::vec2 worldSpacePoint) {
	glm::vec2 position = GetPosition();
	SetRotation(atan2((worldSpacePoint.y - position.y), (worldSpacePoint.x - position.x)) + PI/2);
}

void Projectile::Update(float deltaSeconds) {

	Translate(direction * deltaSeconds * projectileSpeed);

	glm::vec2 position = GetPosition();

	if (position.x < -1000 || position.x > 1000 || position.y < -1000 || position.y > 1000) {
		this->dead = true;
	}

}
