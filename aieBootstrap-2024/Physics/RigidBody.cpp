#include "RigidBody.h"
#include "PhysicsObject.h"

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
