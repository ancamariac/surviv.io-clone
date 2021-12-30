#pragma once

#include <vector>

#include "components/simple_scene.h"

#define PI 3.14159265
#define scaleMap 20
#define squareSide 100
#define projectileSpeed 550.0f
#define MIN_ENEMY_SPEED 100
#define MAX_ENEMY_SPEED 450
#define MIN_SPAWN_LOCATION -800
#define MAX_SPAWN_LOCATION 800

namespace m1
{
    class Survivio : public gfxc::SimpleScene
    {
        public:
            struct ViewportSpace
            {
                ViewportSpace() : x(0), y(0), width(1), height(1) {}
                ViewportSpace(int x, int y, int width, int height)
                    : x(x), y(y), width(width), height(height) {}
                int x;
                int y;
                int width;
                int height;
            };

            struct LogicSpace
            {
                LogicSpace() : x(0), y(0), width(1), height(1) {}
                LogicSpace(float x, float y, float width, float height)
                    : x(x), y(y), width(width), height(height) {}
                float x;
                float y;
                float width;
                float height;
            };

            int width, height;

            GLfloat mouseWorldX, mouseWorldY;

            Survivio();
            ~Survivio();

            GLvoid Init() override;

            void DrawMesh2D(Mesh* mesh, Shader* shader, glm::mat3& mat);
            void DrawGui2D(Mesh* mesh, Shader* shader, glm::mat3& mat);
            glm::mat3 CenterCamera(float x, float y);

        private:
            void Destroy();
            void DrawScene();
            glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
            void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

            void CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
            void FrameStart() override;
            void Update(float deltaTimeSeconds) override;

            void OnInputUpdate(float deltaTime, int mods) override;
            void OnKeyPress(int key, int mods) override;
            glm::vec2 ScreenToWorldPoint(int screenX, int screenY);
            void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
            void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;

            void InitResources();

            void SpawnEnemy(glm::vec2 position, float speed);

        protected:
            glm::mat3 mapModelMatrix;
            glm::mat3 playerModelMatrix;

            glm::mat3 modelMatrix;
            glm::mat3 modelMatrix1;
            glm::mat3 modelMatrix2;
            glm::mat3 modelMatrix3;
            glm::mat3 modelMatrix4;
            glm::mat3 modelMatrix5;
            glm::mat3 modelMatrix6;
            glm::mat3 modelMatrix7;
            glm::mat3 modelMatrix8;

            float translateX, translateY;
            float scaleX, scaleY;
            const float speedUp = 400;
            float fireRate = 0;
            float enemyRate = 0;
            float mapSize;
            int playerHP = 100;
            int score = 0;

            float length;
            ViewportSpace viewSpace;
            LogicSpace logicSpace;
            glm::mat3 visMatrix;
    };
}