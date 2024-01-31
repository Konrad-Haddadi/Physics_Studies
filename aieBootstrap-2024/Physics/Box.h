#pragma once

#include "RigidBody.h"
#include <glm/glm.hpp>
class Box : public RigidBody
{
public:

	Box(glm::vec2 _pos, glm::vec2 _velocity, float _orientation, float _mass, float _width, float _height, glm::vec4 _color);
	~Box() {};

	void Draw(float _alpha) override;
	glm::vec2 GetExtent() { return glm::vec2(m_width, m_height); }
	void SetColor(glm::vec4 _color) { m_color = _color; }

private:

	float m_width;
	float m_height;
	glm::vec4 m_color;
};

