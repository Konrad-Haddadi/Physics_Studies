#include "RigidBody.h"
#include "PhysicsObject.h"
#include <iostream>

RigidBody::RigidBody(ShapeType _shapeID, glm::vec2 _pos, glm::vec2 _velocity, float _orientation, float _mass)
	: PhysicsObject(_shapeID), m_position(_pos), m_velocity(_velocity), m_orientation(_orientation), m_mass(_mass), m_angularVelocity(0)
{

}

RigidBody::~RigidBody()
{

}

void RigidBody::FixedUpdate(glm::vec2 _gravity, float _timeStep)
{
	m_lastPosition = m_position;

	m_position += m_velocity * _timeStep;
	ApplyForce(_gravity * m_mass * _timeStep);

	m_orientation += m_angularVelocity * _timeStep;
}

void RigidBody::ApplyForce(glm::vec2 _force)
{
	if(m_mass != 0)
		m_velocity += _force / m_mass;
}

void RigidBody::ApplyForce(glm::vec2 _force, glm::vec2 _pos)
{
	m_velocity += _force / m_mass;
	m_angularVelocity += (_force.y * _pos.x - _force.x * _pos.y) / GetMoment();
}

void RigidBody::ApplyForceToActor(RigidBody* _inputActor, glm::vec2 _force)
{
	_inputActor->ApplyForce(_force);
	ApplyForce(-_force);
}

void RigidBody::ResolveCollision(RigidBody* _actor2, glm::vec2 _contact, glm::vec2* _collisionNomral)
{
	// find the vector between their centres, or use the provided direction
	// of force, and make sure it's normalised
	glm::vec2 normal = glm::normalize(_collisionNomral ? *_collisionNomral : _actor2->GetPosition() - m_position);

	//get the vector perpendicular to the collision nomral
	glm::vec2 perp(normal.y, -normal.x);

	// determine the total velocity of the contact points for the two objects, for both linear and rotational

	// 'r' is the radius from axis to application of force
	float r1 = glm::dot(_contact - m_position, -perp);
	float r2 = glm::dot(_contact - _actor2->GetPosition(), perp);

	// velocity of the contact point on this object
	float v1 = glm::dot(m_velocity, normal) - r1 * m_angularVelocity;

	// velocity of contact point on actor 2
	float v2 = glm::dot(_actor2->GetVelocity(), normal) + r2 * _actor2->m_angularVelocity;

	if (v1 > v2) // they're moving closer
	{
		// calculate the effective mass at ocntact point for each object ie how the contact point will move due to the force applied.
		float mass1 = 1.0f / (1.0f / m_mass + (r1 * r1) / GetMoment());
		float mass2 = 1.0f / (1.0f / _actor2->GetMass() + (r2 * r2) / _actor2->GetMoment());

		float elasticity = 1;

		glm::vec2 force = (1.0f + elasticity) * mass1 * mass2 / (mass1 + mass2) * (v1 - v2) * normal;

		// apply equal and opposite forces 
		ApplyForce(-force, _contact - m_position);
		_actor2->ApplyForce(force, _contact - _actor2->GetPosition());
	}
}

float RigidBody::GetKineticEnergy()
{
	float kineticEnergy = m_mass * (m_velocity.length() * m_velocity.length()) * 0.5f;

	return kineticEnergy;
}

float RigidBody::GetPotentialEnergy(glm::vec2 _gravity)
{
	float potentialEnergy = -m_mass * glm::dot(_gravity, GetPosition());
	return potentialEnergy;
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

void RigidBody::CalculateSmoothedPosition(float _alpha)
{
	m_smoothedPosition = _alpha * m_position + (1 - _alpha) * m_lastPosition;

	float smootherOrientation = _alpha * m_orientation + (1 - _alpha) * m_lastOrientation;

	float sn = sinf(smootherOrientation);
	float cs = cosf(smootherOrientation);
	m_smoothedLocalX = glm::vec2(cs, sn);
	m_smoothedLocalY = glm::vec2(-sn, cs);
}
