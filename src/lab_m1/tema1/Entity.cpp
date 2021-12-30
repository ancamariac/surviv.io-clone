#include "Entity.h"
#include "transform2D.h"

#include <iostream>
using namespace std;

Entity::Entity() {
    // Setting default values
    position = glm::vec2(0.0f);
    angularStep = 0.0f;
    scale = glm::vec2(1.0f);
    rotationPivot = glm::vec2(0.0f);

    dirtyTransform = true;
}

Entity::~Entity() {

}

void Entity::Translate(glm::vec2 delta) {
    SetPosition(position + delta);
}

// TODO: do not mark as dirty if the thing hasn't moved!
void Entity::SetPosition(glm::vec2 newPosition) {
    position = newPosition;
    dirtyTransform = true;
}

glm::vec2 Entity::GetPosition() {
    return position;
}

// TODO: do not mark as dirty if the thing hasn't moved!
void Entity::SetRotation(float rotation) {
    this->angularStep = rotation;
    dirtyTransform = true;
}

// TODO: do not mark as dirty if the thing hasn't moved!
void Entity::SetScale(glm::vec2 scale) {
    this->scale = scale;
    dirtyTransform = true;
}

void Entity::UpdateTransformMatrix() {
    if (dirtyTransform)
    {
        glm::vec2 centre = position - rotationPivot;
        glm::mat3 translation = transform2D::Translate(centre.x, centre.y);
        glm::mat3 rotation = transform2D::RotateAround(angularStep, rotationPivot.x, rotationPivot.y);
        glm::mat3 scale = transform2D::Scale(this->scale.x, this->scale.y);
        transformMatrix = translation * rotation * scale;

        dirtyTransform = false;
    }
}

glm::mat3 Entity::GetTransformMatrix() {
    return transformMatrix;
}

void Entity::SetRotationPivot(glm::vec2 pivot) {
    rotationPivot = pivot;
    dirtyTransform = true;
}