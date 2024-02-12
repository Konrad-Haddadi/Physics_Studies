#pragma once

#include "PhysicsObject.h"
#include <glm/glm.hpp>

class RigidBody;

class Spring : public PhysicsObject
{
public:
	Spring(RigidBody* _body1, RigidBody* _body2,
		float _springCoefficient, float _damping, float _restLength = 0, glm::vec4 _color = glm::vec4(1,1,1,1),
		glm::vec2 _contact1 = glm::vec2(0), glm::vec2 _contact2 = glm::vec2(0));
	~Spring();


	glm::vec2 GetContact1(float _alpha = 1.f);
	glm::vec2 GetContact2(float _alpha = 1.f);

protected:
	RigidBody* m_body1;
	RigidBody* m_body2;

	glm::vec2 m_contact1;
	glm::vec2 m_contact2;
	glm::vec4 m_color;

	float m_damping;
	float m_restLength;
	float m_springCoefficent;

	void FixedUpdate(glm::vec2 _gravity, float _timeStep) override;
	float GetPotentialEnergy(glm::vec2 _gravity) override;
	void DrawGizmos(float _alpha) override;

};

