#pragma once

#include "RigidBody.h"
#include <glm/glm.hpp>
class Box : public RigidBody
{
public:

	Box(glm::vec2 _pos, glm::vec2 _velocity, float _orientation, float _mass, glm::vec2 _extents, glm::vec4 _color);
	~Box() {};

	void DrawGizmos(float _alpha) override;
	glm::vec2 GetExtents() const { return m_extents; }
	void SetColor(glm::vec4 _color) { m_color = _color; }
	bool CheckBoxCorners(const Box& box, glm::vec2& contact, int& numContacts, float& pen, glm::vec2& edgeNormal);	
	
	float GetWidth() { return m_width; }
	float GetHeight() { return m_height; }

	bool IsInside(glm::vec2 _pos) override;

protected:

	glm::vec2 m_extents;

	float m_width;
	float m_height;
	glm::vec4 m_color;

	// Inherited via RigidBody
	void Update(float _dt) override;
};

