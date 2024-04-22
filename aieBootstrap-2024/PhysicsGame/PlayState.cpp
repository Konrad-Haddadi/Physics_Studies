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
#include <iostream>

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
	{
		if (_input->isMouseButtonDown(0) && (current->timer / current->lifeTimer) > 0.5f)
			current = nullptr;

		return;
	}

	glm::vec2 mousePos = glm::vec2(_input->getMouseX(), _input->getMouseY());
	glm::vec2 pos = slingShot->GetPosition() + glm::vec2(slingShot->GetExtents().x * 0.5, slingShot->GetExtents().y * 0.75);

	if (_input->isMouseButtonDown(0))
		pull = true;


	float dist = glm::distance(mousePos, pos);

	if (dist > 500)
		dist = 500;

	if(_input->isMouseButtonUp(0))
	{
		if (pull)
		{
			pull = false;

			if (mousePos.x > pos.x - slingShot->GetWidth() || mousePos.y > pos.y + slingShot->GetHeight())
				return;

			aie::Gizmos::add2DLine(pos, mousePos, glm::vec4(1, 1, 1, 1));

			float radius = 1.0f;
			float speed = 40;
			glm::vec2 startPos(-40, 0);


			std::cout << dist << std::endl;

			glm::vec2 force = glm::normalize(pos - mousePos) * dist;

			Bird* ball = new Bird(pos, glm::vec2(5, 5), force, 10, new aie::Texture("./textures/Red_Bird.png"), 5.f, 1);
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

		float inclination = 0;

		if (mousePos.x > pos.x - slingShot->GetWidth() || mousePos.y > pos.y + slingShot->GetHeight())
			return;

		if (mousePos.y <= pos.y)
		{
			inclination = glm::atan((mousePos.x - pos.x) / (mousePos.y - pos.y));				
			inclination = -glm::degrees(inclination);
			inclination += 90;
			m_gameStateManager->physicsApp->AngryBirdShootLine(pos, inclination, dist, -m_physicsScene->GetGravity().y);

		}
		else
		{
			inclination = glm::tan((mousePos.y - pos.y)/(pos.x - mousePos.x));
			inclination = -glm::degrees(inclination);
			m_gameStateManager->physicsApp->AngryBirdShootLine(pos, inclination, dist, -m_physicsScene->GetGravity().y);
		}		
			
	}	
}

void PlayState::BuildWorld()
{
	slingShot = new SlingShot(glm::vec2(200, 200), glm::vec2(50,50), new aie::Texture("./textures/SlingShot.png"));
	slingShot->SetKinematic(true);
	m_physicsScene->AddActor(slingShot);
	m_physicsScene->SetGravity(glm::vec2(0, -50));

	m_physicsScene->SetTimeStep(0.01f);


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
				Pig* pig = new Pig(_pos + glm::vec2(i, j) * _spacing, glm::vec2(15, 15), glm::vec2(0), 50.0f, new aie::Texture("./textures/Pig_01.png"), 3);
				rigidBodies[i * numColumns + j] = pig;
				
				pig->physicsScene = m_physicsScene;				
				pigs.push_back(pig);
				_scene->AddActor(pig);

			}
			else if (_strings[j][i] == '1')
			{
				WoodenBox* box = new WoodenBox(_pos + glm::vec2(i, j) * _spacing, glm::vec2(0), 0, 50.0f, glm::vec2(15, 15), new aie::Texture("./textures/WoodenBox.png"), 3);
				rigidBodies[i * numColumns + j] = box;

				box->physicsScene = m_physicsScene;
				_scene->AddActor(box);
			}
			else if (_strings[j][i] == '2')
			{
				Pig* pig = new Pig(_pos + glm::vec2(i, j) * _spacing, glm::vec2(15, 15), glm::vec2(0), 50.0f, new aie::Texture("./textures/Pig_01.png"), 3);
				rigidBodies[i * numColumns + j] = pig;

				pig->physicsScene = m_physicsScene;
				pig->SetKinematic(true);

				pigs.push_back(pig);
				_scene->AddActor(pig);
			}
			else if (_strings[j][i] == '3')
			{
				WoodenBox* box = new WoodenBox(_pos + glm::vec2(i, j) * _spacing, glm::vec2(0), 0, 50.0f, glm::vec2(15, 15), new aie::Texture("./textures/Stone.png"), 3);
				rigidBodies[i * numColumns + j] = box;

				box->physicsScene = m_physicsScene;
				box->SetKinematic(true);
				_scene->AddActor(box);
			}
			else if (_strings[j][i] == '4')
			{
				WoodenBox* box = new WoodenBox(_pos + glm::vec2(i, j) * _spacing, glm::vec2(0), 0, 25.0f, glm::vec2(15 * numColumns, 15), new aie::Texture("./textures/WoodenBox.png"), 5);
				rigidBodies[i * numColumns + j] = box;

				box->physicsScene = m_physicsScene;
				_scene->AddActor(box);
			}
			else if (_strings[j][i] == '5')
			{
				WoodenBox* box = new WoodenBox(_pos + glm::vec2(i, j) * _spacing, glm::vec2(0), 0, 25.0f, glm::vec2(15 * numColumns, 15), new aie::Texture("./textures/Stone.png"), 1, true);
				rigidBodies[i * numColumns + j] = box;

				box->physicsScene = m_physicsScene;
				box->SetKinematic(true);
				_scene->AddActor(box);
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
	spacing = 31.f;

	switch (_level)
	{
	case 0:

		sb.push_back("33333");
		sb.push_back("10.01");
		sb.push_back("1...1");
		sb.push_back("1...1");
		sb.push_back("..4...");
		

		break;	

	case 1:

		sb.push_back("3.33.3");
		sb.push_back("1.00.1");
		sb.push_back("1....1");
		sb.push_back("1....1");
		sb.push_back("......");
		sb.push_back("......");

		break;

	case 2:

		sb.push_back("33333");
		sb.push_back("11.1.");
		sb.push_back("10.0.");
		sb.push_back("1....");
		sb.push_back("1....");


		break;	

	case 3:

		sb.push_back("..5...");
		sb.push_back("..00..");
		sb.push_back("..00..");



		break;

	default:
		break;
	}

	if(sb.size() > 0)
		LevelBuilder(m_physicsScene, glm::vec2(400, 175) + _pos, spacing, sb);
}

void PlayState::SpawnRandomLevel()
{
	current = nullptr;
	m_physicsScene->ClearActors();

	int val = 1 + (rand() % 2);
	for (int i = 0; i < val; i++)
	{
		LevelSelect(rand() % 4, glm::vec2(220 * i, rand() % 250));
	}

	
}
