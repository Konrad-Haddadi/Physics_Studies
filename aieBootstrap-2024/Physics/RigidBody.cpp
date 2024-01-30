#include "RigidBody.h"
#include "PhysicsObject.h"
#include <iostream>

RigidBody::RigidBody(ShapeType _shapeID, glm::vec2 _pos, glm::vec2 _velocity, float _orientation, float _mass)
	: PhysicsObject(_shapeID), m_position(_pos), m_velocity(_velocity), m_orientation(_orientation), m_mass(_mass)
{

}

RigidBody::~RigidBody()
{

}

void RigidBody::FixedUpdate(glm::vec2 _gravity, float _timeStep)
{
	m_position += m_velocity * _timeStep;
	ApplyForce(_gravity * m_mass * _timeStep);
}

void RigidBody::ApplyForce(glm::vec2 _force)
{
	if(m_mass != 0)
		m_velocity += _force / m_mass;
}

void RigidBody::ApplyForceToActor(RigidBody* _inputActor, glm::vec2 _force)
{
	_inputActor->ApplyForce(_force);
	ApplyForce(-_force);
}

float RigidBody::GetKineticEnergy()
{
	float kineticEnergy = m_mass * (m_velocity.length() * m_velocity.length()) * 0.5f;

	return kineticEnergy;
}

void RigidBody::ResolveCollision(RigidBody* _actor2)
{
	glm::vec2 normal = glm::normalize(_actor2->GetPosition() - m_position);
	glm::vec2 relativeVelocity = _actor2->GetVelocity() - m_velocity;

	if (glm::dot(normal, relativeVelocity) >= 0)
		return;

	float elasticity = 1;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) / ((1 / m_mass) + (1 / _actor2->GetMass()));

	glm::vec2 force = normal * j;

	float kePre = GetKineticEnergy() + _actor2->GetKineticEnergy();

	ApplyForceToActor(_actor2, force);

	float kePost = GetKineticEnergy() + _actor2->GetKineticEnergy();

	float deltaKE = kePost - kePre;

	if (deltaKE > kePost * 0.01f)
		std::cout << "Kinetic Energy discrepancy greater than 1% detected!!";
}
