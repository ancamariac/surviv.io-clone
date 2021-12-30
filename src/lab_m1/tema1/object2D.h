#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{
    // Create square with given bottom left corner, length and color
    Mesh* CreateSquareObj(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateSquareDecor(const std::string& name, glm::vec3 color);
    Mesh* CreateProjectile(const std::string& name, glm::vec3 color);
    Mesh* CreateCircle(const std::string& name, glm::vec3 color, int sectors, float radius);
    Mesh* CreateStar(const std::string& name, glm::vec3 color1, glm::vec3 color2);
    Mesh* CreateTarget(const std::string& name, glm::vec3 color);
};