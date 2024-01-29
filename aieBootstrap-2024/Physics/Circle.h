#pragma once

#include "RigidBody.h"
#include <glm/glm.hpp>

class Circle : public RigidBody
{
public:

	Circle(glm::vec2 _pos, glm::vec2 _vel, float _mass, float _radius, glm::vec4 _color);
	~Circle();

	virtual void Draw(float _alpha);

	float GetRadius() { return m_radius; }
	glm::vec4 GetColor() { return m_color; }


protected:
	float m_radius;
	glm::vec4 m_color;
};

