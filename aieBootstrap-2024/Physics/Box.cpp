#include "Box.h"
#include "RigidBody.h"
#include "Gizmos.h"
#include <glm/glm.hpp>

Box::Box(glm::vec2 _pos, glm::vec2 _velocity, float _orientation, float _mass, float _width, float _height, glm::vec4 _color)
	: RigidBody(ShapeType::BOX, _pos, _velocity, _orientation, _mass), m_width(_width), m_height(_height), m_color(_color)
{
	m_moment = 1.0f / 12.0f * m_mass * (m_width * m_width) + (m_height * m_height);
}

void Box::Draw(float _alpha)
{
	aie::Gizmos::add2DAABBFilled(m_position, glm::vec2(m_width, m_height), m_color);
}
