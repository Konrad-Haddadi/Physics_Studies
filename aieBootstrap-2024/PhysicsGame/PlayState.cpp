#include "PlayState.h"
#include "Gizmos.h"
#include "GameStateManager.h"
#include "PhysicsGameApp.h"
#include "PhysicsScene.h"
#include "Circle.h"
#include "Pig.h"
#include "Bird.h"
#include "Texture.h"
#include "WoodenBox.h"
#include "Box.h"
#include "SlingShot.h"

#include <glm/glm.hpp>
#include <vector>
#include <string>

void PlayState::StateEnter()
{
	BuildWorld();
	LevelSelect(2);
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
	glm::vec2 pos = slingShot->GetPosition() + glm::vec2(slingShot->GetExtents().x * 0.5, slingShot->GetExtents().y * 0.75);

	if (_input->isMouseButtonDown(0))
		pull = true;

	if(_input->isMouseButtonUp(0))
	{
		if (pull)
		{
			pull = false;
			aie::Gizmos::add2DLine(pos, mousePos, glm::vec4(1, 1, 1, 1));

			float radius = 1.0f;
			float speed = 40;
			glm::vec2 startPos(-40, 0);

			glm::vec2 force = glm::normalize(pos - mousePos) * (float)(glm::distance(mousePos, pos));

			Bird* ball = new Bird(pos, glm::vec2(10, 10), force ,10, new aie::Texture("../bin/textures/rock_large.png"), 5.f);
			ball->SetLinearDrag(0);

			ball->physicsScene = m_physicsScene;
			m_physicsScene->AddActor(ball);
		}
	}

	if (pull)
	{
		aie::Gizmos::add2DLine(pos, mousePos, glm::vec4(1, 1, 1, 1));

		float radius = 1.0f;
		float speed = 40;
		glm::vec2 startPos(-40, 0);

		float inclination = glm::atan((mousePos.x - pos.x) / (mousePos.y - pos.y));

		inclination = -glm::degrees(inclination);

		m_gameStateManager->physicsApp->AngryBirdShootLine(pos, inclination + 90, glm::distance(mousePos, pos), -m_physicsScene->GetGravity().y);
	}
}

void PlayState::BuildWorld()
{
	slingShot = new SlingShot(glm::vec2(200, 100), glm::vec2(50,50), new aie::Texture("../bin/textures/SlingShot.png"));
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

void PlayState::LevelBuilder(PhysicsScene* _scene, glm::vec2 _pos, float _spacing, std::vector<std::string>& _strings)
{
	int numColumns = _strings.size();
	int numRows = _strings[0].length();

	RigidBody** rigidBodies = new RigidBody * [numRows * numColumns];

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColumns; j++)
		{
			if (_strings[j][i] == '0')
			{
				rigidBodies[i * numColumns + j] = new Pig(_pos + glm::vec2(i, j) * _spacing, glm::vec2(15,15), glm::vec2(0), 10.0f, new aie::Texture("../bin/textures/Pig_01.png"), 10);
				_scene->AddActor(rigidBodies[i * numColumns + j]);
			}
			else if (_strings[j][i] == '1')
			{
				rigidBodies[i * numColumns + j] = new WoodenBox(_pos + glm::vec2(i, j) * _spacing, glm::vec2(0), 0, 10.0f, glm::vec2(15, 15), new aie::Texture("../bin/textures/WoodenBox.png"), 2);
				_scene->AddActor(rigidBodies[i * numColumns + j]);
			}
			else if (_strings[j][i] == '2')
			{
				rigidBodies[i * numColumns + j] = new Pig(_pos + glm::vec2(i, j) * _spacing, glm::vec2(15, 15), glm::vec2(0), 10.0f, new aie::Texture("../bin/textures/Pig_01.png"), 10);
				rigidBodies[i * numColumns + j]->SetKinematic(true);
				_scene->AddActor(rigidBodies[i * numColumns + j]);
			}
			else if (_strings[j][i] == '3')
			{
				rigidBodies[i * numColumns + j] = new WoodenBox(_pos + glm::vec2(i, j) * _spacing, glm::vec2(0), 0, 10.0f, glm::vec2(15, 15), new aie::Texture("../bin/textures/WoodenBox.png"), 2);
				rigidBodies[i * numColumns + j]->SetKinematic(true);
				_scene->AddActor(rigidBodies[i * numColumns + j]);
			}
			else
				rigidBodies[i * numColumns + j] = nullptr;
		}
	}
}

void PlayState::LevelSelect(int _level)
{
	std::vector<std::string> sb;
	float spacing = 0;

	switch (_level)
	{
	case 0:

		sb.push_back("000000");
		sb.push_back("000000");
		sb.push_back("......");
		sb.push_back("......");
		sb.push_back("001100");
		sb.push_back("000000");
		
		spacing = 25;

		break;

	case 1:

		sb.push_back("111111");
		sb.push_back("1.00.1");
		sb.push_back("1....1");
		sb.push_back("1.00.1");
		sb.push_back("......");
		sb.push_back("......");
		spacing = 30;

		break;

	case 2:

		sb.push_back("333333");
		sb.push_back("1.00.1");
		sb.push_back("1....1");
		sb.push_back("1.00.1");
		sb.push_back("......");
		sb.push_back("......");
		spacing = 30;

		break;

	default:
		break;
	}

	if(sb.size() > 0)
		LevelBuilder(m_physicsScene, glm::vec2(500, 100), spacing, sb);
}
