#include "Circle.h"
#include "RigidBody.h"
#include "Gizmos.h"

Circle::Circle(glm::vec2 _pos, glm::vec2 _vel, float _mass, float _radius, glm::vec4 _color)
	: RigidBody(ShapeType::circle, _pos, _vel, 0, _mass), m_radius(_radius), m_color(_color)
{

}

Circle::~Circle()
{
}


void Circle::Draw(float _alpha)
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 15, m_color);	
}
