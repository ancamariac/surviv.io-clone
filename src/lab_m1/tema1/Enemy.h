#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

#include "Entity.h"

#include "Survivio.h"

using namespace m1;

class Enemy : public Entity
{
    public:
        Enemy(Mesh* mesh, Mesh * fist, Mesh * death, Shader* shader, Survivio* instance);
        ~Enemy();

        void Draw();
        void PointTowards(glm::vec2 worldSpacePoint);
        void AdvanceTowards(glm::vec2 worldSpacePoint, float deltaTime);
        bool DestroyAnimation(float deltaTimeSeconds);
        bool BulletCollision(glm::vec2 worldSpacePoint);
        bool hitPlayer;
        bool dead;
        float speed;
    private:
        Enemy();
        Mesh* mesh;
        Mesh* fist;
        Mesh* death;
        Shader* shader;
        Survivio* survInstance;
        float destroyTime;
};