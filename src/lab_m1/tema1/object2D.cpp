#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

#include "Survivio.h"


Mesh* object2D::CreateCircle(const std::string& name, glm::vec3 color, int sectors, float radius)
{
    float alpha;

    std::vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(0, 0, 0), color)
    };

    std::vector<unsigned int> indices;


    for (int i = 0; i < sectors; i++)
    {
        alpha = (2 * PI * i) / sectors;

        vertices.emplace_back(glm::vec3(cos(alpha), sin(alpha), 0) * radius, color),
            indices.push_back(i);
    }

    indices.push_back(sectors);
    indices.push_back(1);

    Mesh* circle = new Mesh(name);
    circle->SetDrawMode(GL_TRIANGLE_FAN);
    circle->InitFromData(vertices, indices);
    return circle;
}


Mesh* object2D::CreateSquareDecor(const std::string& name, glm::vec3 color)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0, 0, 0), color),
        VertexFormat(glm::vec3(100, 0, 0), color),
        VertexFormat(glm::vec3(100, 100, 0), color),
        VertexFormat(glm::vec3(0, 100, 0), color),
    };

    Mesh* squareMap = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 0, 2 };

    squareMap->InitFromData(vertices, indices);
    return squareMap;
}

Mesh* object2D::CreateProjectile(const std::string& name, glm::vec3 color) {

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0, 0, 0), color),
        VertexFormat(glm::vec3(10, 0, 0), color),
        VertexFormat(glm::vec3(10, 30, 0), color),
        VertexFormat(glm::vec3(0, 30, 0), color),
    };

    Mesh* projectile = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 0, 2 };

    projectile->InitFromData(vertices, indices);
    return projectile;
}

Mesh* object2D::CreateSquareObj(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 color1,
    glm::vec3 color2)
{
    

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-30, 0, 1), color1),
        VertexFormat(glm::vec3(30, 0, 1), color1),
        VertexFormat(glm::vec3(0, -30, 1), color1),
        VertexFormat(glm::vec3(0, 30, 1), color1),
        VertexFormat(glm::vec3(-8, -8, 1), color2),
        VertexFormat(glm::vec3(8, 8, 1), color2),
        VertexFormat(glm::vec3(8, -8, 1), color2),
        VertexFormat(glm::vec3(-8, 8, 1), color2)  
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 4, 7, 1, 5, 6, 5, 3, 7, 6, 4, 2, 5, 7, 4, 4, 5, 6 };
    

    star->InitFromData(vertices, indices);
    return star;
}

Mesh* object2D::CreateTarget(const std::string& name, glm::vec3 color) {
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-0.5f, 1, 5), color),
        VertexFormat(glm::vec3(0.5f, 1, 5), color),
        VertexFormat(glm::vec3(-0.5f, 4, 5), color),
        VertexFormat(glm::vec3(0.5f, 4, 5), color),

        VertexFormat(glm::vec3(-0.5f, -1, 5), color),
        VertexFormat(glm::vec3(0.5f, -1, 5), color),
        VertexFormat(glm::vec3(-0.5f, -4, 5), color),
        VertexFormat(glm::vec3(0.5f, -4, 5), color),
        
        VertexFormat(glm::vec3(-4, -0.5f, 5), color),
        VertexFormat(glm::vec3(-1, -0.5f, 5), color),
        VertexFormat(glm::vec3(-4, 0.5f, 5), color),
        VertexFormat(glm::vec3(-1, 0.5f, 5), color),
        
        VertexFormat(glm::vec3(4, -0.5f, 5), color),
        VertexFormat(glm::vec3(1, -0.5f, 5), color),
        VertexFormat(glm::vec3(4, 0.5f, 5), color),
        VertexFormat(glm::vec3(1, 0.5f, 5), color)
    };

    Mesh* target = new Mesh(name);
    std::vector<unsigned int> indices = { 
        0, 1, 2, 1, 2, 3,
        4, 5, 6, 5, 6, 7,
        8, 9, 10, 9, 10, 11,
        12, 13, 14, 13, 14, 15
    };

    target->InitFromData(vertices, indices);
    return target;
}
