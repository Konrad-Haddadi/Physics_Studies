#include "PlayState.h"
#include "Gizmos.h"
#include <glm/glm.hpp>
#include "GameStateManager.h"
#include "MenuState.h"
#include "Box.h"
#include "Plane.h"
#include "PhysicsScene.h"
#include "PhysicsGameApp.h"
#include "Circle.h"
#include "Bird.h"
#include "Button.h"
#include "ButtonManager.h"
#include "Texture.h"
#include "Bird.h"
#include "Application.h"

void PlayState::StateEnter()
{
	slingShot = new Box(glm::vec2(200,50), glm::vec2(0), 0, 1, glm::vec2(10, 50), glm::vec4(0, 1, 0, 1));
	slingShot->SetKinematic(true);
	m_physicsScene->AddActor(slingShot);
	m_physicsScene->SetGravity(glm::vec2(0, -100));
	m_physicsScene->SetTimeStep(0.005f);


	Box* leftWall = new Box(glm::vec2(0, 400), glm::vec2(0), 0, 1, glm::vec2(25, 1300), glm::vec4(1, 1, 1, 1));
	leftWall->SetKinematic(true);

	Box* rightWall = new Box(glm::vec2(1275, 400), glm::vec2(0), 0, 1, glm::vec2(25, 1300), glm::vec4(1, 1, 1, 1));
	rightWall->SetKinematic(true);

	Box* bottomWall = new Box(glm::vec2(400, 0), glm::vec2(0), 0, 1, glm::vec2(1300, 25), glm::vec4(1, 1, 1, 1));
	bottomWall->SetKinematic(true);

	Box* topWall = new Box(glm::vec2(400, 800), glm::vec2(0), 0, 1, glm::vec2(1300, 25), glm::vec4(1, 1, 1, 1));
	topWall->SetKinematic(true);

	m_physicsScene->AddActor(leftWall);
	m_physicsScene->AddActor(rightWall);
	m_physicsScene->AddActor(topWall);
	m_physicsScene->AddActor(bottomWall);

	pull = false;
}

void PlayState::StateUpdate(float _dt)
{
	AngryBirdsControls(m_input, _dt);
	m_physicsScene->Update(_dt);
}

void PlayState::StateDraw()
{
	aie::Gizmos::add2DCircle(glm::vec2(0), 5, 12, glm::vec4(1, 0, 0, 1));
	m_physicsScene->Draw();
}

void PlayState::StateExit()
{

}

void PlayState::AngryBirdsControls(aie::Input* _input, float _dt)
{
	glm::vec2 mousePos = glm::vec2(_input->getMouseX(), _input->getMouseY());

	if (_input->isMouseButtonDown(0))
		pull = true;

	if(_input->isMouseButtonUp(0))
	{
		if (pull)
		{
			pull = false;

			glm::vec2 pos = slingShot->GetPosition() + slingShot->GetExtents();
			aie::Gizmos::add2DLine(pos, mousePos, glm::vec4(1, 1, 1, 1));

			float radius = 1.0f;
			float speed = 40;
			glm::vec2 startPos(-40, 0);

			glm::vec2 force = glm::normalize(pos - mousePos) * (float)(glm::distance(mousePos, pos));

			Bird* ball = new Bird(pos, glm::vec2(10, 10), force ,10, new aie::Texture("../bin/textures/ship.png"), 5.f);
			ball->SetLinearDrag(0);

			ball->physicsScene = m_physicsScene;
			m_physicsScene->AddActor(ball);
		}
	}

	if (pull)
	{
		glm::vec2 pos = slingShot->GetPosition() + slingShot->GetExtents();
		aie::Gizmos::add2DLine(pos, mousePos, glm::vec4(1, 1, 1, 1));

		float radius = 1.0f;
		float speed = 40;
		glm::vec2 startPos(-40, 0);

		float inclination = glm::atan((mousePos.x - pos.x) / (mousePos.y - pos.y));

		inclination = -glm::degrees(inclination);

		m_gameStateManager->physicsApp->AngryBirdShootLine(pos, inclination + 90, glm::distance(mousePos, pos), -m_physicsScene->GetGravity().y);
	}
}
