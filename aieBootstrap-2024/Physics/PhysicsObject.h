#pragma once
#include "Renderer2D.h"
#include <glm/glm.hpp>

enum ShapeType
{
	JOINT = -1,
	PLANE = 0,
	CIRCLE,
	BOX,
	SHAPE_COUNT
};

class PhysicsObject
{
protected:
	PhysicsObject(ShapeType _shapeID) : m_shapeID(_shapeID), m_elasticity(0.3f){}

public:
	virtual void FixedUpdate(glm::vec2 _gravity, float _timeStep) = 0;
	virtual void Update(float _dt) { };

	virtual void DrawGizmos(float _alpha) = 0;
	virtual void Draw(aie::Renderer2D* _renderer) {};
	
	virtual void ResetPosition() {};
	virtual float GetPotentialEnergy(glm::vec2 _gravity) = 0;

	ShapeType GetShapeID() { return m_shapeID; }
	float GetElasticity() { return m_elasticity; }

protected:
	ShapeType m_shapeID;
	float m_elasticity;
};

