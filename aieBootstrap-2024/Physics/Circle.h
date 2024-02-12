#pragma once

#include "RigidBody.h"
#include <glm/glm.hpp>

class Circle : public RigidBody
{
public:
	Circle(glm::vec2 _pos, glm::vec2 _vel, float _mass, float _radius, glm::vec4 _color);
	~Circle();

	virtual void DrawGizmos(float _alpha);
	virtual void Update(float _dt) override;
	virtual void Draw(aie::Renderer2D* _renderer) {};

	float GetRadius() { return m_radius; }
	glm::vec4 GetColor() { return m_color; }
	bool IsInside(glm::vec2 _pos) override;


protected:
	float m_radius;
	glm::vec4 m_color;

	// Inherited via RigidBody
};

