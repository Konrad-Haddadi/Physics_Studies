#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "PhysicsObject.h"

class Plane;
class Circle;

class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void AddActor(PhysicsObject* _actor);
	void RemoveActor(PhysicsObject* _actor);
	void Update(float _dt);
	void Draw();

	void SetGravity(const glm::vec2 _gravity) { m_gravity = _gravity; }
	glm::vec2 GetGravity() const { return m_gravity; }

	void SetTimeStep(const float _timeStep) { m_timeStep = _timeStep; }
	float GetTimeStep() const { return m_timeStep; }

	static bool Plane2Plane(PhysicsObject* _lhs, PhysicsObject* _rhs);
	static bool Plane2Circle(PhysicsObject* _lhs, PhysicsObject* _rhs);
	static bool Plane2Box(PhysicsObject* _lhs, PhysicsObject* _rhs);

	static bool Circle2Circle(PhysicsObject* _lhs, PhysicsObject* _rhs);
	static bool Circle2Plane(PhysicsObject* _lhs, PhysicsObject* _rhs);
	static bool Circle2Box(PhysicsObject* _lhs, PhysicsObject* _rhs);
	
	static bool Box2Plane(PhysicsObject* _lhs, PhysicsObject* _rhs);
	static bool Box2Circle(PhysicsObject* _lhs, PhysicsObject* _rhs);
	static bool Box2Box(PhysicsObject* _lhs, PhysicsObject* _rhs);

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
};