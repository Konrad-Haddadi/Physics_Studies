#include "PhysicsGameApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
#include "GameStateManager.h"
#include "PlayState.h"
#include "glm/ext.hpp"
#include "PhysicsScene.h"

aie::Texture* background;

PhysicsGameStates::PhysicsGameStates() 
{
	
}

PhysicsGameStates::~PhysicsGameStates() 
{

}

bool PhysicsGameStates::startup() 
{	
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);
	m_2dRenderer = new aie::Renderer2D();
	m_physicsScene = new PhysicsScene(m_2dRenderer);

	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_gameStateManager = new GameStateManager(this, nullptr, m_physicsScene, m_2dRenderer);
	m_gameStateManager->SetNextState(new PlayState(m_gameStateManager, m_2dRenderer, m_physicsScene));

	m_gameStateManager->StartUp();
	background = new aie::Texture("./textures/Background.png");


	return true;
}

void PhysicsGameStates::shutdown() {

	m_gameStateManager->ShutDown();

	delete m_font;
	delete m_2dRenderer;
	delete m_gameStateManager;
}

void PhysicsGameStates::update(float deltaTime) 
{

	//aie::Gizmos::clear();

	m_gameStateManager->Update(deltaTime);

	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsGameStates::draw() {

	clearScreen();

	static float aspectRatio = 16.f / 9.f;

	aie::Gizmos::draw2D(glm::ortho<float>(0, Application::getWindowWidth(), 0, Application::getWindowHeight(), -1, 1));
	m_2dRenderer->begin();

	m_2dRenderer->drawSprite(background, Application::getWindowWidth() *0.5f, Application::getWindowHeight() * 0.5f, Application::getWindowWidth(), Application::getWindowHeight());
	m_gameStateManager->Draw();
	
	DrawFPS();

	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	m_2dRenderer->end();

}

void PhysicsGameStates::DrawFPS()
{
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	int windowHeight = Application::getWindowHeight();

	m_2dRenderer->drawText(m_font, fps, 0, windowHeight - 32);
}

glm::vec2 PhysicsGameStates::ScreenToWorld(glm::vec2 screenPos)
{
	glm::vec2 worldPos = screenPos;

	// move the centre of the screen to (0,0)
	worldPos.x -= getWindowWidth() / 2;
	worldPos.y -= getWindowHeight() / 2;

	// scale according to our extents
	worldPos.x *= 2.0f * m_extents / getWindowWidth();
	worldPos.y *= 2.0f * m_extents / (m_aspectRatio * getWindowHeight());

	return worldPos;
}

void PhysicsGameStates::AngryBirdShootLine(glm::vec2 _startPos, float _inclination, float _speed, float _gravity)
{
	float t = 0;
	float tStep = 0.5f;
	float radius = 1.0f;
	int segments = 12;
	glm::vec4 color = glm::vec4(1, 0, 0, 1);

	float xRot = glm::cos(glm::radians(_inclination));
	float yRot = glm::sin(glm::radians(_inclination));

	glm::vec2 lastPos = glm::vec2(0);

	while (t <= 8)
	{
		float x = xRot * _speed * t + _startPos.x;
		float y = yRot * _speed * t + (-_gravity * (t * t)) * 0.5f + _startPos.y;

		if (lastPos != glm::vec2(0))
			aie::Gizmos::add2DLine(lastPos, glm::vec2(x, y), color);

		lastPos = glm::vec2(x, y);
		t += tStep;
	}
}
