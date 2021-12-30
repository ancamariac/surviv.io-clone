#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

#include "Entity.h"


#include "Survivio.h"

using namespace m1;

class Character : public Entity
{
    public :
        Character(Mesh * mesh, Mesh * fist, Shader * shader, Survivio* instance);
        ~Character();

        void Draw();
        void PointTowards(glm::vec2 worldSpacePoint);
    private:
        Character();
        Mesh* mesh;
        Mesh* fist;
        Shader* shader;
        Survivio* survInstance;
};