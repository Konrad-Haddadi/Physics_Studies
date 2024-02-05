#include "Plane.h"
#include "Gizmos.h"
#include "RigidBody.h"
#include <iostream>
#include <glm/glm.hpp>

using glm::vec2;
using glm::vec4;
using aie::Gizmos;

Plane::Plane(glm::vec2 _normal, float _dist)
	: PhysicsObject(ShapeType::PLANE), m_distanceToOrigin(_dist), m_normal(glm::normalize(_normal)), m_color((1,1,1,1))
{

}

Plane::~Plane()
{
}

void Plane::FixedUpdate(glm::vec2 _gravity, float _timeStep)
{
}

void Plane::Draw(float _alpha)
{
	float lineSegmentLength = 300;
	vec2 centerPoint = m_normal * m_distanceToOrigin;

	vec2 parallel(m_normal.y, -m_normal.x);
	
	vec4 colourFade = m_color;
	colourFade.a = 0;

	vec2 start = centerPoint + (parallel * lineSegmentLength);
	vec2 end = centerPoint - (parallel * lineSegmentLength);

	Gizmos::add2DTri(start, end, start - m_normal * 10.0f, m_color, m_color, colourFade);
	Gizmos::add2DTri(end, end - m_normal * 10.0f, start - m_normal * 10.0f, m_color, colourFade, colourFade);
}

void Plane::ResetPosition()
{
}

void Plane::ResolveCollision(RigidBody* _actor2)
{
	glm::vec2 vRel = _actor2->GetVelocity();

	float e = 1;
	float j = glm::dot(-(1 + e) * (vRel), m_normal) / (1 / _actor2->GetMass());

	glm::vec2 force = m_normal * j;
	_actor2->ApplyForce(force);
}

void Plane::ApplyContactForces(RigidBody* _body2, glm::vec2 _norm, float _pen)
{
	float body2Mass = _body2 ? _body2->GetMass() : INT_MAX;
	float body1Factor = body2Mass / INT_MAX + body2Mass;

	if (_body2)
		_body2->SetPosition(_body2->GetPosition() + (1 - body1Factor) * _norm * _pen);
}

void Plane::ResolveCollision(RigidBody* _actor2, glm::vec2 _contact)
{
	glm::vec2 localContact = _contact - _actor2->GetPosition();

	// the plane isn't moving, so the relative velocity is just actor2's velocity at the contact point
	glm::vec2 vRel = _actor2->GetVelocity() + _actor2->GetAngularVelocity() * glm::vec2(-localContact.y, localContact.x);
	float velocityIntoPlane = glm::dot(vRel, m_normal);

	// average the elasticity of the plane and the rigidbody
	float e = (GetElasticity() + _actor2->GetElasticity()) / 2.0f;

	// this is the perpendicular distance we apply the force at relative to the COM, so Torque = F*r
	float r = glm::dot(localContact, glm::vec2(m_normal.y, -m_normal.x));

	// work out the "effective mass" - this is a combination of moment of
	// inertia and mass, and tells us how much the contact point velocity 
	// will change with the force we're applying
	float mass0 = 1.0f / (1.0f / _actor2->GetMass() + (r * r) / _actor2->GetMoment());

	float j = -(1 + e) * velocityIntoPlane * mass0;

	glm::vec2 force = m_normal * j;

	float kePre = _actor2->GetKineticEnergy();

	_actor2->ApplyForce(force, _contact - _actor2->GetPosition());

	float pen = glm::dot(_contact, m_normal) - m_distanceToOrigin;
	ApplyContactForces(_actor2, m_normal, pen);

	float kePost = _actor2->GetKineticEnergy();

	float deltaKE = kePost - kePre;
	if (deltaKE > kePost * 0.01f)
		std::cout << "Kinetic Energy discrepancy greater than 1% detected!!";



}

float Plane::GetPotentialEnergy(glm::vec2 _gravity)
{
	return 0.0f;
}
