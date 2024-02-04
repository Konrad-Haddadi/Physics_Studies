#include "PhysicsGameApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
#include "GameStateManager.h"
#include "MenuState.h"
#include "glm/ext.hpp"

PhysicsGameStates::PhysicsGameStates() {

}

PhysicsGameStates::~PhysicsGameStates() {

}

bool PhysicsGameStates::startup() 
{	
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);
	m_2dRenderer = new aie::Renderer2D();
	m_physicsScene = new PhysicsScene();

	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_gameStateManager = new GameStateManager(new MenuState(m_gameStateManager), m_physicsScene, m_2dRenderer);
	m_gameStateManager->StartUp();

	return true;
}

void PhysicsGameStates::shutdown() {

	m_gameStateManager->ShutDown();

	delete m_font;
	delete m_2dRenderer;
	delete m_gameStateManager;
}

void PhysicsGameStates::update(float deltaTime) {


	m_gameStateManager->Update(deltaTime);

	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsGameStates::draw() {

	clearScreen();

	static float aspectRatio = 16.f / 9.f;

	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1, 1));

	m_2dRenderer->begin();
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