#include "Circle.h"
#include "RigidBody.h"
#include "Gizmos.h"
#include <glm/glm.hpp>

Circle::Circle(glm::vec2 _pos, glm::vec2 _vel, float _mass, float _radius, glm::vec4 _color)
	: RigidBody(ShapeType::CIRCLE, _pos, _vel, 0, _mass), m_radius(_radius), m_color(_color)
{
	m_moment = 0.5f * m_mass * (m_radius * m_radius);
}


Circle::~Circle()
{

}


void Circle::DrawGizmos(float _alpha)
{
	CalculateSmoothedPosition(_alpha);

	aie::Gizmos::add2DCircle(m_position, m_radius, 15, m_color);		
}

bool Circle::IsInside(glm::vec2 _pos)
{
	return glm::distance(_pos, m_position) <= m_radius;
}

void Circle::Update(float _dt)
{
}
