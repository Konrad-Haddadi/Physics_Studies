#include "RigidBody.h"
#include "PhysicsObject.h"
#include <iostream>

RigidBody::RigidBody(ShapeType _shapeID, glm::vec2 _pos, glm::vec2 _velocity, float _orientation, float _mass)
	: PhysicsObject(_shapeID), m_position(_pos), m_velocity(_velocity), m_orientation(_orientation), m_mass(_mass), 
	m_angularVelocity(0), m_linearDrag(0.3f), m_angularDrag(0.3f), m_isKinematic(false), m_lastOrientation(0), m_lastPosition(glm::vec2(0))
{
	m_localX = glm::vec2(0);
	m_localY = glm::vec2(0);

	m_smoothedLocalX = glm::vec2(0);
	m_smoothedLocalY = glm::vec2(0);

	m_smoothedPosition = glm::vec2(0);

	CalculateAxes();
}

RigidBody::~RigidBody()
{

}

void RigidBody::FixedUpdate(glm::vec2 _gravity, float _timeStep)
{	
	if (m_isKinematic)
	{
		m_velocity = glm::vec2(0);
		m_angularVelocity = 0;
		return;
	}

	CalculateAxes();

	m_lastOrientation = m_orientation;
	m_lastPosition = m_position;
	

	m_position += m_velocity * _timeStep;
	ApplyForce(_gravity * m_mass * _timeStep);

	m_velocity -= m_velocity * m_linearDrag * _timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * _timeStep;
	
	m_orientation += m_angularVelocity * _timeStep;

	if (length(m_velocity) < MIN_LINEAR_THRESHOLD)
		m_velocity = glm::vec2(0);	

	if (abs(m_angularVelocity) < MIN_ANGULAR_THRESHOLD)
		m_angularVelocity = 0;
}

void RigidBody::ApplyForce(glm::vec2 _force)
{
	m_velocity += _force / GetMass();
}

void RigidBody::ApplyForce(glm::vec2 _force, glm::vec2 _pos)
{
	m_velocity += _force / GetMass();
	m_angularVelocity += (_force.y * _pos.x - _force.x * _pos.y) / GetMoment();
}

void RigidBody::CalculateAxes()
{
	float sn = sinf(m_orientation);
	float cs = cosf(m_orientation);

	m_localX = glm::normalize(glm::vec2(cs, sn));
	m_localY = glm::normalize(glm::vec2(-sn, cs));
}

void RigidBody::ApplyForceToActor(RigidBody* _inputActor, glm::vec2 _force)
{
	_inputActor->ApplyForce(_force);
	ApplyForce(-_force);
}


void RigidBody::ApplyForceToActor(RigidBody* _inputActor, glm::vec2 _force, glm::vec2 _collision)
{
	_inputActor->ApplyForce(_force, _collision);
	ApplyForce(-_force, _collision);
}

void RigidBody::ResolveCollision(RigidBody* _actor2, glm::vec2 _contact, glm::vec2* _collisionNomral, float _pen )
{
	OnCollisionEnter(_actor2);
	_actor2->OnCollisionEnter(this);

	// find the vector between their centres, or use the provided direction
	// of force, and make sure it's normalised
	glm::vec2 normal = glm::normalize(_collisionNomral ? *_collisionNomral : _actor2->GetPosition() - GetPosition());
	glm::vec2 relativeVelocity = _actor2->GetVelocity() - GetVelocity();

	//get the vector perpendicular to the collision nomral
	glm::vec2 perp(normal.y, -normal.x);

	// determine the total velocity of the contact points for the two objects, for both linear and rotational

	// 'r' is the radius from axis to application of force
	float r1 = glm::dot(_contact - GetPosition(), -perp);
	float r2 = glm::dot(_contact - _actor2->GetPosition(), perp);

	// velocity of the contact point on this object
	float v1 = glm::dot(GetVelocity(), normal) - r1 * GetAngularVelocity();

	// velocity of contact point on actor 2
	float v2 = glm::dot(_actor2->GetVelocity(), normal) + r2 * _actor2->GetAngularVelocity();

	if (v1 > v2) // they're moving closer
	{
		// calculate the effective mass at ocntact point for each object ie how the contact point will move due to the force applied.
		float mass1 = 1.0f / (1.0f / GetMass() + (r1 * r1) / GetMoment());
		float mass2 = 1.0f / (1.0f / _actor2->GetMass() + (r2 * r2) / _actor2->GetMoment());

		float elasticity = (GetElasticity() + _actor2->GetElasticity()) / 2.0f;

		glm::vec2 force = (1.0f + elasticity) * mass1 * mass2 / (mass1 + mass2) * (v1 - v2) * normal;

		float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) / glm::dot(normal, normal * ((1 / GetMass()) + (1 / _actor2->GetMass())));

		if (_pen > 0)
			ApplyContactForces(_actor2, normal, _pen);
		
		ApplyForce(-force, _contact - m_position);
		_actor2->ApplyForce(force, _contact - _actor2->m_position);
	}


}

void RigidBody::ApplyContactForces(RigidBody* _body2, glm::vec2 _norm, float _pen)
{
	float body2Mass = _body2 ? _body2->GetMass() : INT_MAX;
	float body1Factor = body2Mass / (GetMass() + body2Mass);

	SetPosition(GetPosition() - body1Factor * _norm * _pen);

	if (_body2)
		_body2->SetPosition(_body2->GetPosition() + (1 - body1Factor) * _norm * _pen);
}

float RigidBody::GetKineticEnergy()
{
	float kineticEnergy = 0.5f * (GetMass() * glm::dot(GetVelocity(), GetVelocity()) +
		GetMoment() * GetAngularVelocity() * GetAngularVelocity());

	return kineticEnergy;
}

float RigidBody::GetPotentialEnergy(glm::vec2 _gravity)
{
	float potentialEnergy = -GetMass() * glm::dot(_gravity, GetPosition());
	return potentialEnergy;
}

glm::vec2 RigidBody::ToWorld(glm::vec2 _contact, float _aplha)
{
	return m_position + m_localX * _contact.x + m_localY * _contact.y;
}

void RigidBody::ResolveCollision(RigidBody* _actor2)
{
	OnCollisionEnter(_actor2);
	_actor2->OnCollisionEnter(this);

	glm::vec2 normal = glm::normalize(_actor2->GetPosition() - GetPosition());
	glm::vec2 relativeVelocity = _actor2->GetVelocity() - GetVelocity();

	if (glm::dot(normal, relativeVelocity) >= 0)
		return;

	float elasticity = 1;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) / ((1 / GetMass()) + (1 / _actor2->GetMass()));

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

	float smoothedOrientation = _alpha * m_orientation + (1 - _alpha) * m_lastOrientation;

	float sn = sinf(smoothedOrientation);
	float cs = cosf(smoothedOrientation);

	m_smoothedLocalX = glm::vec2(cs, sn);
	m_smoothedLocalY = glm::vec2(-sn, cs);
}
