#pragma once

#include "utils/glm_utils.h"


namespace transform2D
{
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        // Implement the translation matrix
        return glm::transpose(
            glm::mat3(1, 0, translateX,
                0, 1, translateY,
                0, 0, 1)
        );

    }

    // Scale matrix
    inline glm::mat3 Scale(float scaleX, float scaleY)
    {
        // Implement the scaling matrix
        return glm::transpose(
            glm::mat3(scaleX, 0, 0,
                0, scaleY, 0,
                0, 0, 1)
        );

    }

    // Rotate matrix
    inline glm::mat3 Rotate(float radians)
    {
        // Implement the rotation matrix
        return glm::transpose(
            glm::mat3(cos(radians), -sin(radians), 0,
                sin(radians), cos(radians), 0,
                0, 0, 1)
        );

    }

    inline glm::mat3 RotateAround(float radians, float x, float y) {
        glm::mat3 result = glm::mat3(1);

        result *= transform2D::Translate(x, y);
        result *= transform2D::Rotate(radians);
        result *= transform2D::Translate(-x, -y);

        return result;
    }
}   // namespace transform2D