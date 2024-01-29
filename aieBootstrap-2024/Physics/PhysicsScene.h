#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "PhysicsObject.h"

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

	static bool Circle2Circle(PhysicsObject* _lhs, PhysicsObject* _rhs);

protected:
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
};

