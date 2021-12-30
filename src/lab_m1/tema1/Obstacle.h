#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

#include "Entity.h"

#include "utils/glm_utils.h"

#include "Survivio.h"

using namespace m1;

class Obstacle
{
public:
    Obstacle(glm::vec2 position, float width, float height);
    ~Obstacle();
    
    bool ObstacleCollision(glm::vec2 playerPos, float radius);
    

private:
    Obstacle();
    glm::vec2 position;
    float width;
    float height;
    float top, bottom, left, right;
};