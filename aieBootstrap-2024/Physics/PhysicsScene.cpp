#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "RigidBody.h"

#include "Circle.h"
#include "Plane.h"
#include "Box.h"
#include <glm/glm.hpp>
#include <vector>

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] =
{
	PhysicsScene::Plane2Plane,  PhysicsScene::Plane2Circle,  PhysicsScene::Plane2Box,
	PhysicsScene::Circle2Plane, PhysicsScene::Circle2Circle, PhysicsScene::Circle2Box,
	PhysicsScene::Box2Plane,    PhysicsScene::Box2Circle,    PhysicsScene::Box2Box,
};

PhysicsScene::PhysicsScene(aie::Renderer2D* _renderer)
	:m_renderer(_renderer)
{
	SetTimeStep(0.01f);
	SetGravity(glm::vec2(0,0));
	m_actors = std::vector<PhysicsObject*>();
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


void PhysicsScene::ClearActors()
{
	for (int i = 0; i < m_actors.size(); i++)
	{
		delete m_actors[i];		
	}

	m_actors.clear();
}

void PhysicsScene::Update(float _dt)
{
	static float accumulatedTime = 0.0f;
	accumulatedTime += _dt;
		
	while (accumulatedTime >= m_timeStep) {
		for (auto pActor : m_actors) {
			pActor->FixedUpdate(m_gravity, m_timeStep);			
		}
		accumulatedTime -= m_timeStep;

		CheckForCollision();		
	}

	for(auto pActor : m_actors)
		pActor->Update(_dt);
}

void PhysicsScene::Draw()
{
	for (auto obj : m_actors)
	{
		obj->Draw(m_renderer);
		//obj->DrawGizmos(1);
	}
	
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

void PhysicsScene::CheckForCollision()
{
	int actorCount = m_actors.size();


	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];

			int shapeId1 = object1->GetShapeID();
			int shapeId2 = object2->GetShapeID();

			int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;

			if (shapeId1 < 0 || shapeId2 < 0)
				continue;

			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];

			if (collisionFunctionPtr != nullptr)
			{
				collisionFunctionPtr(object1, object2);
			}
		}
	}
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
		int numContacts = 0;
		glm::vec2 contact(0, 0);
		float contactV = 0;

		// Get a representative point on the plane
		glm::vec2 planeOrigin = plane->GetNormal() * plane->GetDistance();

		// check all four corners to see if we've hit the plane
		for (float x = -box->GetExtents().x; x < box->GetWidth(); x += box->GetWidth())
		{
			for (float y = -box->GetExtents().y; y < box->GetHeight(); y += box->GetHeight())
			{
				// Get the position of the corner in world space
				glm::vec2 p = box->GetPosition() + x * box->GetLocalX() + y * box->GetLocalY();
				float distFromPlane = glm::dot(p - planeOrigin, plane->GetNormal());

				// this is the total velocity of the point in world space
				glm::vec2 displacement = x * box->GetLocalX() + y * box->GetLocalY();
				glm::vec2 pointVelocity = box->GetVelocity() + box->GetAngularVelocity() * glm::vec2(-displacement.y, displacement.x);
				// and this is the component of the point velocity into the plane
				float velocityIntoPlane = glm::dot(pointVelocity, plane->GetNormal());

				// and moving further in, we need to resolve the collision
				if (distFromPlane < 0 && velocityIntoPlane <= 0)
				{
					numContacts++;
					contact += p;
					contactV += velocityIntoPlane;
				}
			}
		}

		// we've had a hit - typically only two corners can contact
		if (numContacts > 0)
		{
			plane->ResolveCollision(box, contact / (float)numContacts);
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

		float penetration = circle1->GetRadius() + circle2->GetRadius() - glm::length(dist);

		if (penetration > 0)
		{
			circle1->ResolveCollision(circle2, (circle1->GetPosition() + circle2->GetPosition()) * 0.5f, nullptr, penetration);
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
		// transform the circle into the box's coordinate space
		glm::vec2 circlePosWorld = circle->GetPosition() - box->GetPosition();
		glm::vec2 circlePosBox = glm::vec2(glm::dot(circlePosWorld, box->GetLocalX()), glm::dot(circlePosWorld, box->GetLocalY()));

		// find the closest point to the circle centre on the box by clamping the coordinates in box-space to the box's extents
		glm::vec2 closestPointOnBoxBox = circlePosBox;
		glm::vec2 extents = box->GetExtents();

		if (closestPointOnBoxBox.x < -extents.x) 
			closestPointOnBoxBox.x = -extents.x;

		if (closestPointOnBoxBox.x > extents.x) 
			closestPointOnBoxBox.x = extents.x;

		if (closestPointOnBoxBox.y < -extents.y)
			closestPointOnBoxBox.y = -extents.y;

		if (closestPointOnBoxBox.y > extents.y) 
			closestPointOnBoxBox.y = extents.y;
		// and convert back into world coordinates
		glm::vec2 closestPointOnBoxWorld = box->GetPosition() + closestPointOnBoxBox.x * box->GetLocalX() + closestPointOnBoxBox.y * box->GetLocalY();
		glm::vec2 circleToBox = circle->GetPosition() - closestPointOnBoxWorld;

		float penetration = circle->GetRadius() - glm::length(circleToBox);

		if (penetration > 0)
		{
			glm::vec2 direction = glm::normalize(circleToBox);
			glm::vec2 contact = closestPointOnBoxWorld;
			box->ResolveCollision(circle, contact, &direction, penetration);
		}

		if (glm::length(circleToBox) < circle->GetRadius())
		{
			glm::vec2 direction = glm::normalize(circleToBox);
			glm::vec2 contact = closestPointOnBoxWorld;
			box->ResolveCollision(circle, contact, &direction);
		}

		return true;

	}

	return false;
}

bool PhysicsScene::Box2Box(PhysicsObject* _lhs, PhysicsObject* _rhs)
{
	Box* box1 = dynamic_cast<Box*>(_lhs);
	Box* box2 = dynamic_cast<Box*>(_rhs);

	if (box1 != nullptr && box2 != nullptr) 
	{
		glm::vec2 boxPos = box2->GetPosition() - box1->GetPosition();
		glm::vec2 norm(0, 0);
		glm::vec2 contact(0, 0);

		float pen = 0;
		int numContacts = 0;

		box1->CheckBoxCorners(*box2, contact, numContacts, pen, norm);

		if (box2->CheckBoxCorners(*box1, contact, numContacts, pen, norm)) 
		{
			norm = -norm;
		}		

		if (pen > 0)
		{
			box1->ResolveCollision(box2, contact / float(numContacts), &norm, pen);
			return true; 
		}
	}
	return false;


}