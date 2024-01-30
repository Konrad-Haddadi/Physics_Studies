#include "PhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"
#include "glm/glm.hpp"
#include "Demos.h"
#include "glm/ext.hpp"
#include "PhysicsScene.h"
#include "Circle.h"
#include "Plane.h"

float timer;

PhysicsApp::PhysicsApp() 
{

}

PhysicsApp::~PhysicsApp() 
{

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

	m_physicsScene->SetTimeStep(0.01f);
	SetupContinuousDemo(glm::vec2(0,0), 10, 10, 10);	

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
#ifndef ProjectilePhysicsPart1

	aie::Gizmos::clear();

#endif 
	// input example
	aie::Input* input = aie::Input::getInstance();

	m_physicsScene->Update(deltaTime);
	m_physicsScene->Draw();

	DemoUpdate(input, deltaTime);

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

void PhysicsApp::SetupContinuousDemo(glm::vec2 _startPos, float _inclination, float _speed, float _gravity)
{
#ifdef ProjectilePhysicsPart1
	float t = 0;
	float tStep = 0.5f;
	float radius = 1.0f;
	int segments = 12;
	glm::vec4 color = glm::vec4(1, 1, 0, 1);

	while (t <= 5)
	{
		float x = 0;
		float y = 0;

		aie::Gizmos::add2DCircle(glm::vec2(x, y), radius, segments, color);
		t += tStep;
	}
#endif
}

void PhysicsApp::DemoStartUp(int _num)
{
#ifdef NewtonsSecondLaw

	rocket = new Circle(glm::vec2(-20, 0), glm::vec2(0), 10, 5, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(rocket);

	m_physicsScene->SetGravity(glm::vec2(0, -10));

#endif //NewtonsSecondLaw


#ifdef CollisionDetection

	Circle* ball1 = new Circle(glm::vec2(-20, 0), glm::vec2(0), 10, 5, glm::vec4(1, 0, 0, 1));
	Circle* ball2 = new Circle(glm::vec2(10, 0), glm::vec2(0), 10, 5, glm::vec4(0, 1, 0, 1));
	Plane* plane = new Plane(glm::vec2(1, 1), -30);

	m_physicsScene->SetGravity(glm::vec2(0, -10));


	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);
	m_physicsScene->AddActor(plane);

#endif // CollisionDetection

#ifdef ProjectilePhysicsPart1


	
#endif // CollisionDetection
}

void PhysicsApp::DemoUpdate(aie::Input* _input, float _dt)
{
#ifdef NewtonsSecondLaw

	Controls(_input, _dt);

#endif //NewtonsSecondLaw

#ifdef ProjectilePhysicsPart1



#endif // CollisionDetection
}

void PhysicsApp::Controls(aie::Input* _input, float _dt)
{
	
	if (_input->isKeyDown(aie::INPUT_KEY_W))
	{
		timer += _dt;

		if (timer >= .1f)
		{
			timer = 0;

			Circle* fuel = new Circle(rocket->GetPosition() - glm::vec2(0, rocket->GetRadius()), glm::vec2(0, -20), 1, 1, glm::vec4(0, 1, 0, 1));
			m_physicsScene->AddActor(fuel);
			rocket->ApplyForce(-fuel->GetVelocity());
		}
	}

	if (_input->isKeyDown(aie::INPUT_KEY_S))
	{
		timer += _dt;

		if (timer >= .1f)
		{
			timer = 0;

			Circle* fuel = new Circle(rocket->GetPosition() + glm::vec2(0, rocket->GetRadius()), glm::vec2(0, 20), 1, 1, glm::vec4(0, 1, 0, 1));
			m_physicsScene->AddActor(fuel);

			rocket->ApplyForce(-fuel->GetVelocity());
		}
	}

	if (_input->isKeyDown(aie::INPUT_KEY_D))
	{
		timer += _dt;

		if (timer >= .1f)
		{
			timer = 0;

			Circle* fuel = new Circle(rocket->GetPosition() + glm::vec2(-rocket->GetRadius(), 0), glm::vec2(-20, 0), 1, 1, glm::vec4(0, 1, 0, 1));
			m_physicsScene->AddActor(fuel);

			rocket->ApplyForce(-fuel->GetVelocity());
		}
	}

	if (_input->isKeyDown(aie::INPUT_KEY_A))
	{
		timer += _dt;

		if (timer >= .1f)
		{
			timer = 0;

			Circle* fuel = new Circle(rocket->GetPosition() + glm::vec2(rocket->GetRadius(), 0), glm::vec2(20, 0), 1, 1, glm::vec4(0, 1, 0, 1));
			m_physicsScene->AddActor(fuel);

			rocket->ApplyForce(-fuel->GetVelocity());
		}
	}
}


