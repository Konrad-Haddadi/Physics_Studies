#pragma once

#include <glm/glm.hpp>
#include "PhysicsObject.h"

class RigidBody;

class Plane : public PhysicsObject
{
public:
	Plane(glm::vec2 _normal, float _dist);
	~Plane();

	virtual void FixedUpdate(glm::vec2 _gravity, float _timeStep);
	virtual void Draw(float _alpha);
	virtual void ResetPosition();

	glm::vec2 GetNormal() { return m_normal; }
	float GetDistance() { return m_distanceToOrigin; }
	glm::vec4 GetColor() { return m_color; }
	void ResolveCollision(RigidBody* _actor2);
	void ResolveCollision(RigidBody* _actor2, glm::vec2 _contact);

protected:
	glm::vec2 m_normal;
	float m_distanceToOrigin;
	glm::vec4 m_color;

	// Inherited via PhysicsObject
	float GetPotentialEnergy(glm::vec2 _gravity) override;
};

