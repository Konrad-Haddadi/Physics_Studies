#pragma once
#include <glm/glm.hpp>

enum ShapeType
{
	plane = 0,
	circle,
	box
};

class PhysicsObject
{
protected:
	PhysicsObject(ShapeType _shapeID) : m_shapeID(_shapeID) {}

public:
	virtual void FixedUpdate(glm::vec2 _gravity, float _timeStep) = 0;
	virtual void Draw(float _alpha) = 0;
	virtual void ResetPosition() {};

	ShapeType* GetShapeID() { return &m_shapeID; }

protected:
	ShapeType m_shapeID;
};

