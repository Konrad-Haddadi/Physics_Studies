#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Circle.h"
#include "Plane.h"
#include "Box.h"
#include <glm/glm.hpp>

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] =
{
	PhysicsScene::Plane2Plane,  PhysicsScene::Plane2Circle,  PhysicsScene::Plane2Box,
	PhysicsScene::Circle2Plane, PhysicsScene::Circle2Circle, PhysicsScene::Circle2Box,
	PhysicsScene::Box2Plane,    PhysicsScene::Box2Circle,    PhysicsScene::Box2Box,
};

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
	int actorCount = m_actors.size();

	static float accumulatedTime = 0.0f;
	accumulatedTime += _dt;

	
	while (accumulatedTime >= m_timeStep) {
		for (auto pActor : m_actors) {
			pActor->FixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;

		for (int outer = 0; outer < actorCount - 1; outer++)
		{
			for (int inner = outer + 1; inner < actorCount; inner++)
			{
				PhysicsObject* object1 = m_actors[outer];
				PhysicsObject* object2 = m_actors[inner];

				int shapeId1 = object1->GetShapeID();
				int shapeId2 = object2->GetShapeID();

				int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;

				fn collisionFunctionPtr = collisionFunctionArray[functionIdx];

				if (collisionFunctionPtr != nullptr)
				{
					collisionFunctionPtr(object1, object2);
				}
			}
		}
	}
}

void PhysicsScene::Draw()
{
	for (auto obj : m_actors)
		obj->Draw(1);
	
}

float PhysicsScene::GetTotalEnergy()
{
	float total = 0;
	for (auto iter = m_actors.begin(); iter != m_actors.end(); iter++)
	{
		PhysicsObject* obj = *iter;
		total += glm::abs(obj->GetPotentialEnergy(m_gravity));
	}

	return total;
}

bool PhysicsScene::Plane2Plane(PhysicsObject* _lhs, PhysicsObject* _rhs)
{
	return false;
}


bool PhysicsScene::Plane2Circle(PhysicsObject* _lhs, PhysicsObject* _rhs)
{
	Plane* plane = dynamic_cast<Plane*>(_lhs);
	Circle* circle = dynamic_cast<Circle*>(_rhs);

	return Circle2Plane(circle, plane);

}

bool PhysicsScene::Plane2Box(PhysicsObject* _lhs, PhysicsObject* _rhs)
{
	Plane* plane = dynamic_cast<Plane*>(_lhs);
	Box* box = dynamic_cast<Box*>(_rhs);

	if (box != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->GetNormal();
		float sphereToPlane = glm::dot(box->GetPosition(), plane->GetNormal()) - plane->GetDistance();

		float intersectionX = box->GetExtent().x - sphereToPlane;
		float intersectionY = box->GetExtent().y - sphereToPlane;

		float velocityOutOfPlane = glm::dot(box->GetVelocity(), plane->GetNormal());

		if (intersectionX > 0 && velocityOutOfPlane < 0)
		{
			glm::vec2 contact = box->GetPosition() + (collisionNormal * -box->GetExtent().x);
			plane->ResolveCollision(box, contact);

			float r = (float)(rand() % 100) / 100;
			float g = (float)(rand() % 100) / 100;
			float b = (float)(rand() % 100) / 100;

			box->SetColor(glm::vec4(r, g, b, 1));

			return true;
		}

		if (intersectionY > 0 && velocityOutOfPlane < 0)
		{
			glm::vec2 contact = box->GetPosition() + (collisionNormal * -box->GetExtent().y);
			plane->ResolveCollision(box, contact);


			float r = (float)(rand() % 100) / 100;
			float g = (float)(rand() % 100) / 100;
			float b = (float)(rand() % 100) / 100;

			box->SetColor(glm::vec4(r, g, b, 1));

			return true;
		}
	}

	return false;
}

bool PhysicsScene::Circle2Circle(PhysicsObject* _lhs, PhysicsObject* _rhs)
{
	Circle* circle1 = dynamic_cast<Circle*>(_lhs);
	Circle* circle2 = dynamic_cast<Circle*>(_rhs);

	if (circle1 != nullptr && circle2 != nullptr)
	{
		glm::vec2 dist = circle1->GetPosition() - circle2->GetPosition();
		if (glm::length(dist) < circle1->GetRadius() + circle2->GetRadius())
		{
			circle1->ResolveCollision(circle2, 0.5f * (circle1->GetPosition() + circle2->GetPosition()));
			return true;
		}
	}

	return false;
}


bool PhysicsScene::Circle2Plane(PhysicsObject* _lhs, PhysicsObject* _rhs)
{
	Circle* circle = dynamic_cast<Circle*>(_lhs);
	Plane* plane = dynamic_cast<Plane*>(_rhs);

	if (circle != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->GetNormal();
		float sphereToPlane = glm::dot(circle->GetPosition(), plane->GetNormal()) - plane->GetDistance();

		float intersection = circle->GetRadius() - sphereToPlane;
		float velocityOutOfPlane = glm::dot(circle->GetVelocity(), plane->GetNormal());

		if (intersection > 0 && velocityOutOfPlane < 0)
		{
			glm::vec2 contact = circle->GetPosition() + (collisionNormal * -circle->GetRadius());
			plane->ResolveCollision(circle, contact);
			return true;
		}
	}

	return false;

}

bool PhysicsScene::Circle2Box(PhysicsObject* _lhs, PhysicsObject* _rhs)
{
	Circle* circle = dynamic_cast<Circle*>(_lhs);
	Box* box = dynamic_cast<Box*>(_rhs);

	return Box2Circle(_rhs, _lhs);
}


bool PhysicsScene::Box2Plane(PhysicsObject* _lhs, PhysicsObject* _rhs)
{
	Plane* plane = dynamic_cast<Plane*>(_rhs);
	Box* box = dynamic_cast<Box*>(_lhs);

	return Plane2Box(plane, box);

}

bool PhysicsScene::Box2Circle(PhysicsObject* _lhs, PhysicsObject* _rhs)
{
	Box* box = dynamic_cast<Box*>(_lhs);
	Circle* circle = dynamic_cast<Circle*>(_rhs);

	if (box != nullptr && circle != nullptr)
	{
		glm::vec2 pos1 = box->GetPosition();
		glm::vec2 pos2 = circle->GetPosition();
		glm::vec2 extent1 = box->GetExtent();
		float radius = circle->GetRadius();

		if (pos1.x + extent1.x >= pos2.x - radius &&
			pos1.x - extent1.x <= pos2.x + radius &&
			pos1.y + extent1.y >= pos2.y - radius &&
			pos1.y - extent1.y <= pos2.y + radius)
		{
			box->ResolveCollision(circle);

			return true;
		}
	}

	return false;
}

bool PhysicsScene::Box2Box(PhysicsObject* _lhs, PhysicsObject* _rhs)
{
	Box* box1 = dynamic_cast<Box*>(_lhs);
	Box* box2 = dynamic_cast<Box*>(_rhs);

	if (box1 != nullptr && box2 != nullptr)
	{
		glm::vec2 pos1 = box1->GetPosition();
		glm::vec2 pos2 = box2->GetPosition();
		glm::vec2 extent1 = box1->GetExtent();
		glm::vec2 extent2 = box2->GetExtent();

		if (pos1.x + extent1.x >= pos2.x - extent2.x &&
			pos1.x - extent1.x <= pos2.x + extent2.x &&
			pos1.y + extent1.y >= pos2.y - extent2.y &&
			pos1.y - extent1.y <= pos2.y + extent2.y)
		{
			box1->ResolveCollision(box2);
			return true;
		}
	}

	return false;

}