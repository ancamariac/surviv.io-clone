#pragma once
#include <iostream>
#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

#include "Entity.h"


#include "Survivio.h"

using namespace m1;

class Projectile : public Entity
{
    public:
        bool dead;
        float aliveTime;
        //float fireRate;
        Projectile(Mesh* mesh, Shader* shader, glm::vec2 position, glm::vec2 target, Survivio* instance);
        ~Projectile();

        void Draw();
        void PointTowards(glm::vec2 worldSpacePoint);
        void Update(float deltaSeconds);
    private:
        Projectile();
        Mesh* mesh;
        Shader* shader;
        Survivio* survInstance;

        glm::vec2 direction;
};