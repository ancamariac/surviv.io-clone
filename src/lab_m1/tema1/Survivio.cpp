#include "lab_m1/tema1/Survivio.h"

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"
#include "lab_m1/tema1/Character.h"
#include "lab_m1/tema1/Projectile.h"
#include "lab_m1/tema1/Obstacle.h"

#include "core/engine.h"
#include "utils/gl_utils.h"
#include <vector>
#include <string>
#include <iostream>
#include <lab_m1\tema1\Enemy.h>


using namespace std;
using namespace m1;

Survivio::Survivio()
{	
}


Survivio::~Survivio()
{
	Survivio::Destroy();
}

Character * myCharacter;

glm::vec2 debugMarker;

glm::vec2 lastMousePos;

vector<Projectile*> projectiles;

vector<Enemy*> enemies;

vector<Obstacle*> obstacles;

GLvoid Survivio::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	width = resolution.x;
	height = resolution.y;

	logicSpace.x = 0;       // logic x
	logicSpace.y = 0;       // logic y
	logicSpace.width = 800;  // logic width
	logicSpace.height = 600;  // logic height

	// Initialize the translation steps
	translateX = 0;
	translateY = 0;

	// Initialize the scale factors
	scaleX = 1;
	scaleY = 1;

	// Position of the mouse pointer
	mouseWorldX = 0;
	mouseWorldY = 0;

	// Debugging stuff
	debugMarker = glm::vec2(0.0f);
	lastMousePos = glm::vec2(0.0f);

	fireRate = 0;
	mapSize = squareSide * scaleMap;

	InitResources();

	// Create the player
	myCharacter = new Character(meshes["circle_player"], meshes["fist_player"], shaders["VertexColor"], this);

	// Create the obstacles
	obstacles.push_back(new Obstacle(glm::vec2(300, -850), 5 * squareSide, 2 * squareSide));
	obstacles.push_back(new Obstacle(glm::vec2(400, -200), 2 * squareSide, 5 * squareSide));
	obstacles.push_back(new Obstacle(glm::vec2(-200, 700), 8 * squareSide, squareSide));
	obstacles.push_back(new Obstacle(glm::vec2(-100, -500), 2 * squareSide, 2 * squareSide));
	obstacles.push_back(new Obstacle(glm::vec2(-800, -750), squareSide, 6 * squareSide));
	obstacles.push_back(new Obstacle(glm::vec2(-800, -850), 6 * squareSide, 2 * squareSide));

}

void Survivio::InitResources() {
	glm::vec3 corner = glm::vec3(0, 0, 0);

	Mesh* squareMap = object2D::CreateSquareDecor("squareMap", glm::vec3(0, 0.2f, 0));
	AddMeshToList(squareMap);

	Mesh* squareFrame = object2D::CreateSquareObj("squareFrame", glm::vec3(0, 0, 4), squareSide, glm::vec3(0.6f, 0, 0), false);
	AddMeshToList(squareFrame);


	Mesh* squareObj = object2D::CreateSquareDecor("squareObj", glm::vec3(0.1f, 0.4f, 0.3f));
	AddMeshToList(squareObj);

	Mesh* squareHealth = object2D::CreateSquareObj("squareHealth", glm::vec3(0, 0, 4), squareSide, glm::vec3(0.6f, 0, 0), true);
	AddMeshToList(squareHealth);

	Mesh* projectile = object2D::CreateProjectile("projectile", glm::vec3(0.8f, 0, 0.6f));
	AddMeshToList(projectile);

	Mesh* circle_player = object2D::CreateCircle("circle_player", glm::vec3(0.55f, 0.13f, 0.41f), 30, 50);
	AddMeshToList(circle_player);

	Mesh* fist_player = object2D::CreateCircle("fist_player", glm::vec3(0.6f, 0.19f, 0.8f), 30, 20);
	AddMeshToList(fist_player);

	Mesh* circle_enemy = object2D::CreateCircle("circle_enemy", glm::vec3(0.137f, 0.137f, 0.556f), 30, 50);
	AddMeshToList(circle_enemy);

	Mesh* fist_enemy = object2D::CreateCircle("fist_enemy", glm::vec3(0, 0, 1), 30, 20);
	AddMeshToList(fist_enemy);

	Mesh* death_enemy = object2D::CreateStar("death_enemy", glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));
	AddMeshToList(death_enemy);

	Mesh* target = object2D::CreateTarget("target", glm::vec3(1, 0, 0));
	AddMeshToList(target);
}

void Survivio::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

glm::mat3 visMatrix;

void Survivio::DrawMesh2D(Mesh* mesh, Shader* shader, glm::mat3& mat) {
	RenderMesh2D(mesh, shader, visMatrix * mat);
}

void Survivio::DrawGui2D(Mesh* mesh, Shader* shader, glm::mat3& mat) {
	RenderMesh2D(mesh, shader, mat);
}

void Survivio::DrawScene() {

	float mapSize = scaleMap * squareSide;

	modelMatrix7 = transform2D::Translate(window->GetResolution().x - 3 * squareSide, window->GetResolution().y - squareSide);
	modelMatrix7 *= transform2D::Scale(2.5f, 0.5f);
	DrawGui2D(meshes["squareFrame"], shaders["VertexColor"], modelMatrix7);

	modelMatrix7 = transform2D::Translate(window->GetResolution().x - 3 * squareSide, window->GetResolution().y - squareSide);
	modelMatrix7 *= transform2D::Scale(2.5f * playerHP / 100, 0.5f);
	DrawGui2D(meshes["squareHealth"], shaders["VertexColor"], modelMatrix7);

	// Debug marker for the mouse pointer
	modelMatrix = transform2D::Translate(debugMarker.x, debugMarker.y);
	modelMatrix *= transform2D::Scale(2.5f, 2.5f);
	DrawMesh2D(meshes["target"], shaders["VertexColor"], modelMatrix);

	// Draw the center of the map (debugging purpose)
	//modelMatrix = transform2D::Translate(-5.0f, -5.0f);
	//modelMatrix *= transform2D::Scale(0.1f, 0.1f);
	//DrawMesh2D(meshes["squareObj"], shaders["VertexColor"], modelMatrix);
	
	// Obstacles
	modelMatrix8 = transform2D::Translate(300, -850);
	modelMatrix8 *= transform2D::Scale(5, 2);
	DrawMesh2D(meshes["squareObj"], shaders["VertexColor"], modelMatrix8);

	modelMatrix7 = transform2D::Translate(400, -200);
	modelMatrix7 *= transform2D::Scale(2, 5);
	DrawMesh2D(meshes["squareObj"], shaders["VertexColor"], modelMatrix7);

	modelMatrix6 = transform2D::Translate(-200, 700);
	modelMatrix6 *= transform2D::Scale(8, 1);
	DrawMesh2D(meshes["squareObj"], shaders["VertexColor"], modelMatrix6);

	modelMatrix3 = transform2D::Translate(-100, -500);
	modelMatrix3 *= transform2D::Scale(2, 2);
	DrawMesh2D(meshes["squareObj"], shaders["VertexColor"], modelMatrix3);

	modelMatrix2 = transform2D::Translate(-800, -750);
	modelMatrix2 *= transform2D::Scale(1, 6);
	DrawMesh2D(meshes["squareObj"], shaders["VertexColor"], modelMatrix2);

    modelMatrix1 = transform2D::Translate(-800, -850);
	modelMatrix1 *= transform2D::Scale(6, 2);
	DrawMesh2D(meshes["squareObj"], shaders["VertexColor"], modelMatrix1);

	// Map square
	mapModelMatrix = transform2D::Translate(-mapSize/2, -mapSize/2);
	mapModelMatrix *= transform2D::Scale(scaleMap, scaleMap);
	DrawMesh2D(meshes["squareMap"], shaders["VertexColor"], mapModelMatrix);
}

void Survivio::Destroy() {
	delete myCharacter;
}

glm::mat3 Survivio::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
	float sx, sy, tx, ty, smin;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	if (sx < sy)
		smin = sx;
	else
		smin = sy;

	tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
	ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

	return glm::transpose(glm::mat3(
		smin, 0.0f, tx,
		0.0f, smin, ty,
		0.0f, 0.0f, 1.0f));
}

void Survivio::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
	glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	glEnable(GL_SCISSOR_TEST);
	glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
	GetSceneCamera()->Update();
}

glm::mat3 Survivio::CenterCamera(float x, float y) {

	glm::ivec2 resolution = window->GetResolution();

	// Physical viewport
	viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
	SetViewportArea(viewSpace, glm::vec3(0, 0, 0), true);

	return transform2D::Translate(-x + resolution.x/2, -y + resolution.y / 2);
}


void Survivio::Update(float deltaTimeSeconds)
{
	// The death of the player
	if (playerHP <= 0) {
		std::cout << "\n\n\n\nGAME OVER!\n\n\n\n";
		std::cout << "FINAL SCORE: " << score << "\n\n\n\n";
		exit(0);
	}


	visMatrix = CenterCamera(translateX, translateY);

	debugMarker = ScreenToWorldPoint(lastMousePos.x, window->GetResolution().y - lastMousePos.y);

	enemyRate += deltaTimeSeconds;
	fireRate += deltaTimeSeconds;

	// Player
	glm::ivec2 resolution = window->GetResolution();
	myCharacter->PointTowards(debugMarker);
	//std::cout << debugMarker.x << "  " << debugMarker.y << endl;
	myCharacter->SetPosition(glm::vec2(translateX, translateY));
	myCharacter->Draw();

	// Enemies
	if (enemyRate > 3) {
		enemyRate = 0;
		SpawnEnemy(glm::vec2(rand() % (MAX_SPAWN_LOCATION - MIN_SPAWN_LOCATION + 1) + MIN_SPAWN_LOCATION,
							 rand() % (MAX_SPAWN_LOCATION - MIN_SPAWN_LOCATION + 1) + MIN_SPAWN_LOCATION), 
							 rand() % (MAX_ENEMY_SPEED - MIN_ENEMY_SPEED + 1) + MIN_ENEMY_SPEED);
	}

	for (vector<Enemy*>::iterator i = enemies.begin(); i != enemies.end(); ) {

		Enemy* myEnemy = *i;

		if (!myEnemy->dead) {
			myEnemy->PointTowards(myCharacter->GetPosition());
			myEnemy->AdvanceTowards(myCharacter->GetPosition(), deltaTimeSeconds);
			myEnemy->Draw();
			i++;
		}
		else {
			//if (myEnemy->DestroyAnimation(deltaTimeSeconds)) {
				if (myEnemy->hitPlayer) {
					playerHP -= 5;
				}
				else {
					score++;
					if (score % 5 == 0) {
						std::cout << "SCORE: " << score << endl;
					}
				}
				delete myEnemy;
				i = enemies.erase(i);
			//}
		}
	}
	
	// Projectiles
	for (vector<Projectile*>::iterator i = projectiles.begin(); i != projectiles.end(); ) {
		
		Projectile* proj = *i;
		int cnt = 0;
		for (vector<Enemy*>::iterator j = enemies.begin(); j != enemies.end(); j++) {

			Enemy* myEnemy = *j;
			if (myEnemy->BulletCollision(proj->GetPosition())) {
				proj->dead = true;
				break;
			}
		}

		for (vector<Obstacle*>::iterator k = obstacles.begin(); k != obstacles.end(); k++) {
			Obstacle* obs = *k;
			if (obs->ObstacleCollision(proj->GetPosition(), 6)) {
				proj->dead = true;
				break;
			}
		}

		if (!proj->dead) {
			proj->Update(deltaTimeSeconds);
			proj->Draw();
			proj->aliveTime += deltaTimeSeconds;
			i++;
			// Destroy bullet after a period of time
			if (proj->aliveTime * projectileSpeed > scaleMap * (squareSide - 20)) {
				proj->dead = true;
			}
		}
		else {	
			delete proj;
			i = projectiles.erase(i);
		}
	}

	// Map
	DrawScene();

}

void Survivio::SpawnEnemy(glm::vec2 position, float speed) {

	Enemy* myEnemy = new Enemy(meshes["circle_enemy"], meshes["fist_enemy"], meshes["death_enemy"], shaders["VertexColor"], this);

	myEnemy->SetPosition(position);
	myEnemy->speed = speed;

	enemies.push_back(myEnemy);
}

void Survivio::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W))
	{
		float dist = deltaTime * speedUp;
		translateY += dist;

		// Collision with the wall of the map
		if (translateY > 950) {
			translateY = 950;
		}

		for (vector<Obstacle*>::iterator i = obstacles.begin(); i != obstacles.end(); i++) {
			Obstacle* obj = *i;
			if (obj->ObstacleCollision(glm::vec2(translateX, translateY), squareSide/2)) {
				translateY -= dist;
				break;
			}
		}
	}

	if (window->KeyHold(GLFW_KEY_A))
	{
		float dist = deltaTime * speedUp;
		translateX -= dist;

		// Collision with the wall of the map
		if (translateX < -950) {
			translateX = -950;
		}

		for (vector<Obstacle*>::iterator i = obstacles.begin(); i != obstacles.end(); i++) {
			Obstacle* obj = *i;
			if (obj->ObstacleCollision(glm::vec2(translateX, translateY), squareSide / 2)) {
				translateX += dist;
				break;
			}
		}
	}

	if (window->KeyHold(GLFW_KEY_S))
	{
		float dist = deltaTime * speedUp;
		translateY -= dist;
		// Collision with the wall of the map
		if (translateY < -950) {
			translateY = -950;
		}

		for (vector<Obstacle*>::iterator i = obstacles.begin(); i != obstacles.end(); i++) {
			Obstacle* obj = *i;
			if (obj->ObstacleCollision(glm::vec2(translateX, translateY), squareSide / 2)) {
				translateY += dist;
				break;
			}
		}
	}

	if (window->KeyHold(GLFW_KEY_D))
	{
		float dist = deltaTime * speedUp;
		translateX += dist;
		// Collision with the wall of the map
		if (translateX > 950) {
			translateX = 950;
		}

		for (vector<Obstacle*>::iterator i = obstacles.begin(); i != obstacles.end(); i++) {
			Obstacle* obj = *i;
			if (obj->ObstacleCollision(glm::vec2(translateX, translateY), squareSide / 2)) {
				translateX -= dist;
				break;
			}
		}
	}
}

glm::vec2 Survivio::ScreenToWorldPoint(int screenX, int screenY) {
	glm::vec2 result;

	result.x = screenX + translateX - window->GetResolution().x / 2;
	result.y = screenY + translateY - window->GetResolution().y / 2;

	return result;
}

void Survivio::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	glm::vec2 mousePos = ScreenToWorldPoint(mouseX, mouseY);
	glm::vec2 characterPos = myCharacter->GetPosition();

	lastMousePos = glm::vec2(mouseX, mouseY);
}

void Survivio::OnKeyPress(int key, int mods)
{
}

void Survivio::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	glm::vec2 targetPos = ScreenToWorldPoint(mouseX, window->GetResolution().y - mouseY);
	
	if (fireRate > 0.5f) {
		fireRate = 0;
		Projectile* projectile = new Projectile(meshes["projectile"], shaders["VertexColor"], myCharacter->GetPosition(), targetPos, this);
		projectiles.push_back(projectile);
	}
	
}