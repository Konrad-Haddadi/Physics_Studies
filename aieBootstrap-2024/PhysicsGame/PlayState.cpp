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
#include <time.h>
#include <stdlib.h>
#include <stdio.h>   


Bird* current;

void PlayState::StateEnter()
{
	current = nullptr;
	win = new aie::Texture("./textures/YouWin.png");
	srand(time(NULL));

	pigs = std::vector<Pig*>();

	SpawnRandomLevel();
	BuildWorld();
}

void PlayState::StateUpdate(float _dt)
{
	AngryBirdsControls(m_input, _dt);
	m_physicsScene->Update(_dt);

	if (current != nullptr)
	{
		if (current->remove)
		{
			delete current;
			current = nullptr;
		}
	}

	for (int i = 0; i < pigs.size(); i++)
	{
		if (pigs[i]->dead)
		{
			delete pigs[i];
			pigs.erase(pigs.begin() + i);
			break;
		}
	}
}

void PlayState::StateDraw()
{
	aie::Gizmos::add2DCircle(glm::vec2(0), 5, 12, glm::vec4(1, 0, 0, 1));
	m_physicsScene->Draw();

	if (pigs.size() <= 0)
	{
		m_renderer->drawSprite(win, 500, 500);

		if (m_input->isKeyDown(aie::INPUT_KEY_SPACE) || m_input->isKeyDown(aie::INPUT_MOUSE_BUTTON_LEFT))
		{
			SpawnRandomLevel();
			BuildWorld();

		}
	}
}

void PlayState::StateExit()
{
	
}

void PlayState::AngryBirdsControls(aie::Input* _input, float _dt)
{
	if (current != nullptr)
		return;

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

			Bird* ball = new Bird(pos, glm::vec2(5, 5), force, 10, new aie::Texture("./textures/Red_Bird.png"), 5.f, 2);
			current = ball;
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
	slingShot = new SlingShot(glm::vec2(200, 175), glm::vec2(50,50), new aie::Texture("./textures/SlingShot.png"));
	slingShot->SetKinematic(true);
	m_physicsScene->AddActor(slingShot);
	m_physicsScene->SetGravity(glm::vec2(0, -50));
	m_physicsScene->SetTimeStep(0.005f);


	Box* leftWall = new Box(glm::vec2(0, 400), glm::vec2(0), 0, 1, glm::vec2(25, 1300), glm::vec4(1, 1, 1, 1));
	leftWall->SetKinematic(true);

	Box* rightWall = new Box(glm::vec2(1275, 400), glm::vec2(0), 0, 1, glm::vec2(25, 1300), glm::vec4(1, 1, 1, 1));
	rightWall->SetKinematic(true);

	Box* bottomWall = new Box(glm::vec2(400, 125), glm::vec2(0), 0, 1, glm::vec2(1300, 25), glm::vec4(1, 1, 1, 1));
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
	int numRows = _strings[0].length();
	int numColumns = _strings.size();

	RigidBody** rigidBodies = new RigidBody * [numRows * numColumns];

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColumns; j++)
		{
			if (_strings[j][i] == '0')
			{
				Pig* pig = new Pig(_pos + glm::vec2(i, j) * _spacing, glm::vec2(15, 15), glm::vec2(0), 50.0f, new aie::Texture("./textures/Pig_01.png"), 4);
				pig->physicsScene = m_physicsScene;

				pigs.push_back(pig);

				rigidBodies[i * numColumns + j] = pig;
				_scene->AddActor(rigidBodies[i * numColumns + j]);
			}
			else if (_strings[j][i] == '1')
			{
				WoodenBox* box = new WoodenBox(_pos + glm::vec2(i, j) * _spacing, glm::vec2(0), 0, 50.0f, glm::vec2(15, 15), new aie::Texture("./textures/WoodenBox.png"), 2);
				box->physicsScene = m_physicsScene;

				rigidBodies[i * numColumns + j] = box;
				_scene->AddActor(rigidBodies[i * numColumns + j]);
			}
			else if (_strings[j][i] == '2')
			{
				Pig* pig = new Pig(_pos + glm::vec2(i, j) * _spacing, glm::vec2(15, 15), glm::vec2(0), 50.0f, new aie::Texture("./textures/Pig_01.png"), 4);
				pig->physicsScene = m_physicsScene;

				rigidBodies[i * numColumns + j] = pig;
				rigidBodies[i * numColumns + j]->SetKinematic(true);
				_scene->AddActor(rigidBodies[i * numColumns + j]);
			}
			else if (_strings[j][i] == '3')
			{
				WoodenBox* box = new WoodenBox(_pos + glm::vec2(i, j) * _spacing, glm::vec2(0), 0, 50.0f, glm::vec2(15, 15), new aie::Texture("./textures/Stone.png"), 5);
				box->physicsScene = m_physicsScene;

				rigidBodies[i * numColumns + j] = box;
				rigidBodies[i * numColumns + j]->SetKinematic(true);
				_scene->AddActor(rigidBodies[i * numColumns + j]);
			}
			else if (_strings[j][i] == '4')
			{
				WoodenBox* box = new WoodenBox(_pos + glm::vec2(i, j) * _spacing, glm::vec2(0), 0, 25.0f, glm::vec2(15 * numColumns, 15), new aie::Texture("./textures/WoodenBox.png"), 5);
				box->physicsScene = m_physicsScene;

				rigidBodies[i * numColumns + j] = box;
				_scene->AddActor(rigidBodies[i * numColumns + j]);
			}			
			else
				rigidBodies[i * numColumns + j] = nullptr;

			
		}
	}
}

void PlayState::LevelSelect(int _level, glm::vec2 _pos)
{
	std::vector<std::string> sb;
	float spacing = 0;
	spacing = 30;

	switch (_level)
	{
	case 0:

		sb.push_back("33333");
		sb.push_back("10101");
		sb.push_back("1.1.1");
		sb.push_back("1.1.1");
		sb.push_back("..4...");
		

		break;

	case 1:

		sb.push_back("333333");
		sb.push_back("..00..");
		sb.push_back("......");
		sb.push_back("..00..");		

		break;

	case 2:

		sb.push_back("3.33.3");
		sb.push_back("1.00.1");
		sb.push_back("1....1");
		sb.push_back("1....1");
		sb.push_back("......");
		sb.push_back("......");

		break;

	case 3:

		sb.push_back("33333");
		sb.push_back("11.1.");
		sb.push_back("10.0.");
		sb.push_back("1....");
		sb.push_back("1....");


		break;

	default:
		break;
	}

	if(sb.size() > 0)
		LevelBuilder(m_physicsScene, glm::vec2(500, 175) + _pos, spacing, sb);
}

void PlayState::SpawnRandomLevel()
{
	m_physicsScene->ClearActors();

	int val = 1 + (rand() % 4);
	for (int i = 0; i < val; i++)
	{
		LevelSelect(rand() % 4, glm::vec2(215 * i, rand() % 500));
	}
}
