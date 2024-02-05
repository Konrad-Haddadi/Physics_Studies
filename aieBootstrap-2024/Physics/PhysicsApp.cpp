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
#include "Renderer2D.h"
#include "Box.h"
#include "Spring.h"
#include "SoftBody.h"

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
	//m_physicsScene->SetGravity(glm::vec2(0, -10));

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
#ifndef ProjectilePhysics

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
	

	//m_2dRenderer->drawSprite(image, 50, 50,50,50, timer);

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
	
	char totalEnergy[32];
	sprintf_s(totalEnergy, 32, "Total energy %i", (int)m_physicsScene->GetTotalEnergy());

	int windowHeight = Application::getWindowHeight();

	
	m_2dRenderer->drawText(m_font, totalEnergy, 0, windowHeight - 64);

	m_2dRenderer->drawText(m_font, fps, 0, windowHeight - 32);
	m_2dRenderer->setUVRect(0, 0, 1, 1);
}

void PhysicsApp::SetupContinuousDemo(glm::vec2 _startPos, float _inclination, float _speed, float _gravity)
{	
	float t = 0;
	float tStep = 0.5f;
	float radius = 1.0f;
	int segments = 12;
	glm::vec4 color = glm::vec4(1, 1, 0, 1);

	float xRot = glm::cos(glm::radians(_inclination));
	float yRot = glm::sin(glm::radians(_inclination));

	
	while (t <= 5)
	{
		float x = xRot * _speed * t + _startPos.x;
		float y = yRot * _speed * t + (-_gravity * (t * t)) * 0.5f + _startPos.y;

		aie::Gizmos::add2DCircle(glm::vec2(x, y), radius, segments, color);
		t += tStep;
	}


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

#ifdef ProjectilePhysics

	SetupContinuousDemo(glm::vec2(-40, 0), 45, 40, 10);


	m_physicsScene->SetGravity(glm::vec2(0, -10));
	m_physicsScene->SetTimeStep(0.5f);

	float radius = 1.0f;
	float speed = 40;
	glm::vec2 startPos(-40, 0);
	float inclination = glm::pi<float>() / 4.0f;

	float xRot = glm::cos(inclination);
	float yRot = glm::sin(inclination);

	float x = xRot * speed;
	float y = yRot * speed;

	m_physicsScene->AddActor(new Circle(startPos, glm::vec2(x, y), 1, radius, glm::vec4(1, 0, 0, 1)));


#endif // ProjectilePhysicsPart

#ifdef CollisionReslution

	Circle* ball1 = new Circle(glm::vec2(-50, 5), glm::vec2(50, 0), 3, 5, glm::vec4(1, 0, 0, 1));
	Circle* ball2 = new Circle(glm::vec2(0, 0), glm::vec2(0, 0), 1, 5, glm::vec4(1, 1, 0, 1));

	Plane* topWall = new Plane(glm::vec2(0,-1), -50);
	Plane* bottomWall = new Plane(glm::vec2(0, 1), -50);
	Plane* leftWall = new Plane(glm::vec2(1, 0), -95);
	Plane* rightWall = new Plane(glm::vec2(-1, 0), -95);

	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);
	m_physicsScene->AddActor(topWall);
	m_physicsScene->AddActor(bottomWall);
	m_physicsScene->AddActor(leftWall);
	m_physicsScene->AddActor(rightWall);

#endif // CollisionReslution

#ifdef Cradle

	Circle* ball1 = new Circle(glm::vec2(-50, 0), glm::vec2(50, 0), 1, 5, glm::vec4(1, 0, 0, 1));
	Circle* ball2 = new Circle(glm::vec2(-30, 0), glm::vec2(0, 0), 1, 5, glm::vec4(1, 0, 0, 1));
	Circle* ball3 = new Circle(glm::vec2(-10, 0), glm::vec2(0, 0), 1, 5, glm::vec4(1, 0, 0, 1));
	Circle* ball4 = new Circle(glm::vec2(10, 0), glm::vec2(0, 0), 1, 5, glm::vec4(1, 0, 0, 1));
	Circle* ball5 = new Circle(glm::vec2(30, 0), glm::vec2(0, 0), 1, 5, glm::vec4(1, 1, 0, 1));

	Plane* topWall = new Plane(glm::vec2(0, -1), -50);
	Plane* bottomWall = new Plane(glm::vec2(0, 1), -50);
	Plane* leftWall = new Plane(glm::vec2(1, 0), -95);
	Plane* rightWall = new Plane(glm::vec2(-1, 0), -95);

	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);
	m_physicsScene->AddActor(ball3);
	m_physicsScene->AddActor(ball4);
	m_physicsScene->AddActor(ball5);

	m_physicsScene->AddActor(topWall);
	m_physicsScene->AddActor(bottomWall);
	m_physicsScene->AddActor(leftWall);
	m_physicsScene->AddActor(rightWall);

#endif // Cradle

#ifdef BoxDemo

	Box* box1 = new Box(glm::vec2(30, 0), glm::vec2(-10, 0), 0, 1, 10, 10, glm::vec4(1, 1, 0, 1));
	Box* box2 = new Box(glm::vec2(0, 0), glm::vec2(0, 0), 0, 1, 10, 10, glm::vec4(1, 0, 0, 1));
	Box* box3 = new Box(glm::vec2(10, 40), glm::vec2(0, -10), 0, 1, 10, 10, glm::vec4(1, 0, 0, 1));

	m_physicsScene->AddActor(box1);
	m_physicsScene->AddActor(box2);
	m_physicsScene->AddActor(box3);

#endif // BoxDemo

#ifdef BoxCircleDemo

	Box* box1 = new Box(glm::vec2(30, 0), glm::vec2(0, 0), 0, 1, 10, 10, glm::vec4(1, 1, 0, 1));
	Circle* ball1 = new Circle(glm::vec2(0, 20), glm::vec2(10, -5), 1, 5, glm::vec4(1, 0, 0, 1));

	m_physicsScene->AddActor(box1);
	m_physicsScene->AddActor(ball1);

#endif // BoxCircleDemo

#ifdef DVDLogo

	Box* box1 = new Box(glm::vec2(30, 0), glm::vec2(-50, 40), 0, 1, 10, 10, glm::vec4(1, 1, 0, 1));

	float height = Application::getWindowHeight() / 15;
	float width = Application::getWindowWidth() / 15;

	Plane* topWall = new Plane(glm::vec2(0, -1), -height);
	Plane* bottomWall = new Plane(glm::vec2(0, 1), -height);
	Plane* leftWall = new Plane(glm::vec2(1, 0), -width);
	Plane* rightWall = new Plane(glm::vec2(-1, 0), -width);

	m_physicsScene->AddActor(box1);


	m_physicsScene->AddActor(topWall);
	m_physicsScene->AddActor(bottomWall);
	m_physicsScene->AddActor(leftWall);
	m_physicsScene->AddActor(rightWall);

#endif // BoxPlaneDemo

#ifdef RotatedBoxCheck

	Box* box1 = new Box(glm::vec2(30, 0), glm::vec2(-50, 40), 45, 1, 10, 10, glm::vec4(1, 1, 0, 1));
	Box* box2 = new Box(glm::vec2(00, 0), glm::vec2(-10, -30), 20, 1, 10, 10, glm::vec4(1, 1, 0, 1));

	float height = Application::getWindowHeight() / 15;
	float width = Application::getWindowWidth() / 15;

	Plane* topWall = new Plane(glm::vec2(0, -1), -height);
	Plane* bottomWall = new Plane(glm::vec2(0, 1), -height);
	Plane* leftWall = new Plane(glm::vec2(1, 0), -width);
	Plane* rightWall = new Plane(glm::vec2(-1, 0), -width);

	m_physicsScene->AddActor(box1);
	m_physicsScene->AddActor(box2);

	m_physicsScene->AddActor(topWall);
	m_physicsScene->AddActor(bottomWall);
	m_physicsScene->AddActor(leftWall);
	m_physicsScene->AddActor(rightWall);

#endif // RotatedBoxCheck

#ifdef RandomObjectCheck

	m_physicsScene->SetGravity(glm::vec2(0, -20));

	Box* box1 = new Box(glm::vec2(30, 0), glm::vec2(-10,0), 45, 1, glm::vec2(10,5), glm::vec4(1, 1, 0, 1));
	Circle* ball1 = new Circle(glm::vec2(0, 20), glm::vec2(10, -5), 1, 5, glm::vec4(1, 0, 0, 1));

	m_physicsScene->AddActor(box1);
	m_physicsScene->AddActor(ball1);

	float height = Application::getWindowHeight() / 15;
	float width = Application::getWindowWidth() / 15;

	Plane* topWall = new Plane(glm::vec2(0, -1), -height);
	Plane* bottomWall = new Plane(glm::vec2(.25, 1), -height /2);
	Plane* leftWall = new Plane(glm::vec2(1, 0), -width);
	Plane* rightWall = new Plane(glm::vec2(-1, 0), -width);

	m_physicsScene->AddActor(topWall);
	m_physicsScene->AddActor(bottomWall);
	m_physicsScene->AddActor(leftWall);
	m_physicsScene->AddActor(rightWall);

#endif // RandomObjectCheck

#ifdef Pool

	Circle* ball1 = new Circle(glm::vec2(-20, 5), glm::vec2(200,00), 1, 5, glm::vec4(1, 1, 1, 1));
	Circle* ball2 = new Circle(glm::vec2(30, 0), glm::vec2(0), 1, 5, glm::vec4(1, 0, 0, 1));
	/*Circle* ball3 = new Circle(glm::vec2(35, 10), glm::vec2(0), 1, 5, glm::vec4(0, 1, 0, 1));
	Circle* ball4 = new Circle(glm::vec2(35, -10), glm::vec2(0), 1, 5, glm::vec4(1, 1, 0, 1));
	Circle* ball5 = new Circle(glm::vec2(40, -20), glm::vec2(0), 1, 5, glm::vec4(1, 0, 1, 1));
	Circle* ball6 = new Circle(glm::vec2(40, 20), glm::vec2(0), 1, 5, glm::vec4(0, 0, 1, 1));*/


	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);
	/*m_physicsScene->AddActor(ball3);
	m_physicsScene->AddActor(ball4);
	m_physicsScene->AddActor(ball5);
	m_physicsScene->AddActor(ball6);*/

	float height = Application::getWindowHeight() / 15;
	float width = Application::getWindowWidth() / 15;

	Plane* topWall = new Plane(glm::vec2(0, -1), -height * 0.9f);
	Plane* bottomWall = new Plane(glm::vec2(0, 1), -height * 0.9f);
	Plane* leftWall = new Plane(glm::vec2(1, 0), -width * 0.9f);
	Plane* rightWall = new Plane(glm::vec2(-1, 0), -width * 0.9f);

	m_physicsScene->AddActor(topWall);
	m_physicsScene->AddActor(bottomWall);
	m_physicsScene->AddActor(leftWall);
	m_physicsScene->AddActor(rightWall);

#endif // Pool


#ifdef Kinematic


	Box* box1 = new Box(glm::vec2(30, 0), glm::vec2(0), 45, 1, glm::vec2(5,5), glm::vec4(1, 1, 0, 1));
	Box* box2 = new Box(glm::vec2(30, 20), glm::vec2(0, -10), 45, 1, glm::vec2(5, 5), glm::vec4(1, 1, 0, 1));

	box1->SetKinematic(true);

	Circle* ball1 = new Circle(glm::vec2(-30, 0), glm::vec2(30, 0), 1, 5, glm::vec4(1, 0, 0, 1));
	  
	m_physicsScene->SetGravity(glm::vec2(0, -20));

	m_physicsScene->AddActor(box1);
	m_physicsScene->AddActor(box2);
	m_physicsScene->AddActor(ball1);

	float height = Application::getWindowHeight() / 15;
	float width = Application::getWindowWidth() / 15;

	Plane* topWall = new Plane(glm::vec2(0, -1), -height);
	Plane* bottomWall = new Plane(glm::vec2(.25, 1), -height / 2);
	Plane* leftWall = new Plane(glm::vec2(1, 0), -width);
	Plane* rightWall = new Plane(glm::vec2(-1, 0), -width);

	m_physicsScene->AddActor(topWall);
	m_physicsScene->AddActor(bottomWall);
	m_physicsScene->AddActor(leftWall);
	m_physicsScene->AddActor(rightWall);

#endif // Kinematic

#ifdef Springs

	m_physicsScene->SetGravity(glm::vec2(0, -9.82f));

	Circle* ball1 = new Circle(glm::vec2(-20, 20), glm::vec2(50, 00), 50, 5, glm::vec4(1, 1, 1, 1));
	m_physicsScene->AddActor(ball1);

	Circle* prev = nullptr;
	for (int i = 0; i < 16; i++)
	{
		// spawn a circle to the right and below the previous one, so that the whole rope acts under gravity and swings
		Circle* circle = new Circle(glm::vec2(i * 3, 30 - i * 5), glm::vec2(0), 10, 2, glm::vec4(1, 0, 0, 1));
		if (i == 0)
			circle->SetKinematic(true);
		m_physicsScene->AddActor(circle);
		if (prev)
			m_physicsScene->AddActor(new Spring(circle, prev, 500, 10, 7));
		prev = circle;
	}

	// add a kinematic box at an angle for the rope to drape over
	Box* box = new Box(glm::vec2(0, -20), glm::vec2(0), 40, 20, glm::vec2(10, 5), glm::vec4(0, 0, 1, 1));
	box->SetKinematic(true);
	m_physicsScene->AddActor(box);


#endif // Spring

#ifdef SoftBodys

	std::vector<std::string> sb;

	sb.push_back("000000");
	sb.push_back("000000");
	sb.push_back("00....");
	sb.push_back("00....");
	sb.push_back("000000");
	sb.push_back("000000");

	SoftBody::Build(m_physicsScene, glm::vec2(-50, 0), 5.0f, 10.0f, 0.1f, sb);

#endif // SoftBody


}

void PhysicsApp::DemoUpdate(aie::Input* _input, float _dt)
{
#ifdef NewtonsSecondLaw

	Controls(_input, _dt);

#endif //NewtonsSecondLaw

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


