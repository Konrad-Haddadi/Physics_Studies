#include "PhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

PhysicsApp::PhysicsApp() {

}

PhysicsApp::~PhysicsApp() {

}

bool PhysicsApp::startup() 
{
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	m_texture = new aie::Texture("../bin/textures/ship.png");

	return true;
}

void PhysicsApp::shutdown() 
{

	delete m_font;
	delete m_2dRenderer;
	delete m_texture;
}

void PhysicsApp::update(float deltaTime) 
{

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	Draw();
	DrawText();


	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

void PhysicsApp::Draw()
{
	m_2dRenderer->setUVRect(0, 0, 1, 1);
	m_2dRenderer->drawSprite(m_texture, 200, 200, 100,100);	

	aie::Gizmos::add2DCircle(glm::vec2(0), 3, 15, glm::vec4(1));

	static float aspectRatio = 16.f / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1, 1));

}

void PhysicsApp::DrawText()
{	
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());	
	int windowHeight = Application::getWindowHeight();


	m_2dRenderer->drawText(m_font, fps, 0, windowHeight - 32);
}

