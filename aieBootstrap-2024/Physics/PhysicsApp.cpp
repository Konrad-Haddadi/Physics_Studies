#include "PhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
#include "glm/glm.hpp"

#include "glm/ext.hpp"
#include "PhysicsScene.h"
#include "Circle.h"

float timer;

PhysicsApp::PhysicsApp() {

}

PhysicsApp::~PhysicsApp() {

}

bool PhysicsApp::startup() 
{
	timer = 0;
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"

	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	m_physicsScene = new PhysicsScene();

	m_physicsScene->SetGravity(glm::vec2(0, -15));
	m_physicsScene->SetTimeStep(0.01f);
	
	rocket = new Circle(glm::vec2(0, -50), glm::vec2(0), 10, 5, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(rocket);
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

	m_physicsScene->Update(deltaTime);
	

	Controls(input, deltaTime);


	// exit the application

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();
	aie::Gizmos::clear();

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
	m_physicsScene->Draw();

	static float aspectRatio = 16.f / 9.f;

	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1, 1));
}

void PhysicsApp::DrawText()
{	
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());	
	int windowHeight = Application::getWindowHeight();

	m_2dRenderer->drawText(m_font, fps, 0, windowHeight - 32);
	m_2dRenderer->setUVRect(0, 0, 1, 1);
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

void PhysicsApp::Controls(aie::Input* _input, float _dt)
{
	if (_input->isKeyDown(aie::INPUT_KEY_W))
	{
		timer += _dt;

		if (timer >= .1f)
		{
			timer = 0;

			Circle* fuel = new Circle(rocket->GetPosition() - glm::vec2(0, rocket->GetRadius()), glm::vec2(0, -20), 0, 1, glm::vec4(0, 1, 0, 1));
			m_physicsScene->AddActor(fuel);
			rocket->ApplyForce(-fuel->GetVelocity());

			rocket->SetMass(rocket->GetMass() - _dt);
		}
	}

	if (_input->isKeyDown(aie::INPUT_KEY_S))
	{
		timer += _dt;

		if (timer >= .1f)
		{
			timer = 0;

			Circle* fuel = new Circle(rocket->GetPosition() + glm::vec2(0, rocket->GetRadius()), glm::vec2(0, 20), 0, 1, glm::vec4(0, 1, 0, 1));
			m_physicsScene->AddActor(fuel);

			rocket->ApplyForce(-fuel->GetVelocity());
			rocket->SetMass(rocket->GetMass() - _dt);
		}
	}

	if (_input->isKeyDown(aie::INPUT_KEY_D))
	{
		timer += _dt;

		if (timer >= .1f)
		{
			timer = 0;

			Circle* fuel = new Circle(rocket->GetPosition() + glm::vec2(-rocket->GetRadius(), 0), glm::vec2(-20, 0), 0, 1, glm::vec4(0, 1, 0, 1));
			m_physicsScene->AddActor(fuel);

			rocket->ApplyForce(-fuel->GetVelocity());

			rocket->SetMass(rocket->GetMass() - _dt);
		}
	}

	if (_input->isKeyDown(aie::INPUT_KEY_A))
	{
		timer += _dt;

		if (timer >= .1f)
		{
			timer = 0;

			Circle* fuel = new Circle(rocket->GetPosition() + glm::vec2(rocket->GetRadius(), 0), glm::vec2(20, 0), 0, 1, glm::vec4(0, 1, 0, 1));
			m_physicsScene->AddActor(fuel);

			rocket->ApplyForce(-fuel->GetVelocity());

			rocket->SetMass(rocket->GetMass() - _dt);
		}
	}
}


