#include "PhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "PhysicsScene.h"



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
	m_physicsScene = new PhysicsScene();
	m_physicsScene->SetTimeStep(0.01f);

	Circle* rocket1 = new Circle(glm::vec2(50, 50), glm::vec2(0), 10, 10, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(rocket1);	
	DemoStartUp(1);	

	return true;
}

void PhysicsApp::shutdown() 
{
	delete m_physicsScene;
	delete m_font;
	delete m_2dRenderer;
}

void PhysicsApp::update(float deltaTime) 
{
	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->Update(deltaTime);

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
	aie::Gizmos::add2DCircle(glm::vec2(0), 10, 12, glm::vec4(1, 1, 1, 1));

	// done drawing sprites
	m_2dRenderer->end();
}

void PhysicsApp::Draw()
{
	static float aspectRatio = 16.f / 9.f;

	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1, 1));

	m_physicsScene->Draw();
}

void PhysicsApp::DrawText()
{	
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());	
	int windowHeight = Application::getWindowHeight();

	m_2dRenderer->drawText(m_font, fps, 0, windowHeight - 32);
}

void PhysicsApp::DemoStartUp(int _num)
{
#ifdef NewtonsFirstLaw
	int test = 0;

#endif // NewtonsFirstLaw
}

void PhysicsApp::DemoUpdate(aie::Input* _input, float _dt)
{

}

