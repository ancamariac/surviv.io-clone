#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


class Entity
{
    public :
        Entity();
        ~Entity();

        void Translate(glm::vec2 delta);
        void SetPosition(glm::vec2 newPosition);
        glm::vec2 GetPosition();
        void SetRotation(float rotation);
        void SetScale(glm::vec2 scale);
        void UpdateTransformMatrix();
        glm::mat3 GetTransformMatrix();

        void SetRotationPivot(glm::vec2 pivot);
    private:
        glm::vec2 position;
        float angularStep;
        glm::vec2 scale;
        glm::vec2 rotationPivot;

        bool dirtyTransform;
        glm::mat3 transformMatrix;
};