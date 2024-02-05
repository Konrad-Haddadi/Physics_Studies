#pragma once

#include "PhysicsObject.h"
#include <glm/glm.hpp>

class RigidBody;

class Spring : public PhysicsObject
{
public:
	glm::vec2 GetContact1(float _alpha);
	glm::vec2 GetContact2(float _alpha);

protected:
	RigidBody* m_body1;
	RigidBody* m_body2;

	glm::vec2 m_contact1;
	glm::vec2 m_contact2;

	glm::vec4 m_color;

	float m_damping;
	float m_restLength;
	float m_springCoefficent;



	// Inherited via PhysicsObject
	void FixedUpdate(glm::vec2 _gravity, float _timeStep) override;

	void Draw(float _alpha) override;

	float GetPotentialEnergy(glm::vec2 _gravity) override;

};

