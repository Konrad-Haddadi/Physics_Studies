#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Circle.h"

PhysicsScene::PhysicsScene()
{
	SetTimeStep(0.01f);
	SetGravity(glm::vec2(0,0));
}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
		delete pActor;
}

void PhysicsScene::AddActor(PhysicsObject* _actor)
{
	m_actors.push_back(_actor);
}

void PhysicsScene::RemoveActor(PhysicsObject* _actor)
{
	for (int i = 0; i < m_actors.size(); i++)
	{
		if (m_actors[i] == _actor)
		{
			m_actors.erase(m_actors.begin() + i);
		}
			
	}
}

void PhysicsScene::Update(float _dt)
{
	static float acumulatedTime = 0.0f;
	acumulatedTime += _dt;

	while (acumulatedTime >= m_timeStep)
	{
		for(auto obj : m_actors)
		{
			obj->FixedUpdate(m_gravity, m_timeStep);
		}

		acumulatedTime -= m_timeStep;

		int actorCount = m_actors.size();

		for (int outer = 0; outer < actorCount - 1; outer++)
		{
			for (int inner = outer + 1; inner < actorCount; inner++)
			{
				PhysicsObject* object1 = m_actors[outer];
				PhysicsObject* object2 = m_actors[inner];

				Circle2Circle(object1, object2);
			}
		}
	}

	
}

void PhysicsScene::Draw()
{
	for (auto obj : m_actors)
		obj->Draw(1);
	
}

bool PhysicsScene::Circle2Circle(PhysicsObject* _lhs, PhysicsObject* _rhs)
{
	Circle* circle1 = dynamic_cast<Circle*>(_lhs);
	Circle* circle2 = dynamic_cast<Circle*>(_rhs);

	if (circle1 != nullptr && circle2 != nullptr)
	{
		if (glm::distance(circle1->m_position, circle2->m_position) < circle1->GetRadius() + circle2->GetRadius())
		{
			circle2->ApplyForceToActor(circle1, (circle2->GetMass() / circle1->GetMass()) * circle2->GetVelocity());
		}
	}

	return false;
}

//glm::vec2 ElasticCollision(RigidBody* _obj1, RigidBody* _obj2)
//{
//	glm::vec2 force = glm::vec2(0);
//
//	float mass1 = _obj1->GetMass();
//	float mass2 = _obj2->GetMass();
//
//	force.x = (mass1 - mass2) / ()
//
//	return force;
//}
