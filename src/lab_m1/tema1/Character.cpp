#include "Character.h"

#include "components/simple_scene.h"
#include "core/engine.h"
#include "utils/gl_utils.h"
#include "utils/glm_utils.h"

#include "transform2D.h"

using namespace std;

Character::Character(Mesh* mesh, Mesh* fist, Shader* shader, Survivio* instance)
{
	this->mesh = mesh;
	this->fist = fist;
	this->shader = shader;
	survInstance = instance;
}

Character::~Character()
{

}

void Character::PointTowards(glm::vec2 worldSpacePoint) {
	glm::vec2 position = GetPosition();
	SetRotation(atan2((worldSpacePoint.y - position.y), (worldSpacePoint.x - position.x)));
}

void Character::Draw() {
	this->UpdateTransformMatrix();
	survInstance->DrawMesh2D(mesh, shader, this->GetTransformMatrix());


	glm::mat3 tr = transform2D::Translate(50, -30);

	// Draw left fist
	survInstance->DrawMesh2D(fist, shader, this->GetTransformMatrix() * tr);

	tr = transform2D::Translate(50, 30);

	// Draw right fist
	survInstance->DrawMesh2D(fist, shader, this->GetTransformMatrix() * tr);
}