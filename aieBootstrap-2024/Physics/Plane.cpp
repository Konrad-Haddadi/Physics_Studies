#include "Plane.h"
#include "Gizmos.h"
#include "RigidBody.h"

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

void Plane::ResolveCollision(RigidBody* _actor2, glm::vec2 _contact)
{
	glm::vec2 vRel = _actor2->GetVelocity();

	float e = 1;
	float j = glm::dot(-(1 + e) * (vRel), m_normal) / (1 / _actor2->GetMass());

	glm::vec2 force = m_normal * j;
	_actor2->ApplyForce(force, _contact - _actor2->GetPosition());

}

float Plane::GetPotentialEnergy(glm::vec2 _gravity)
{
	return 0.0f;
}
