#pragma once

#include "PhysicsObject.h"
#include <glm/glm.hpp>

class RigidBody : public PhysicsObject
{
public:
	RigidBody(ShapeType _shapeID, glm::vec2 _pos, glm::vec2 _velocity, float _orientation, float _mass);
	~RigidBody();

	void FixedUpdate(glm::vec2 _gravity, float _timeStep) override;
	void ApplyForce(glm::vec2 _force);
	void ApplyForce(glm::vec2 _force, glm::vec2 _pos);
	void ApplyForceToActor(RigidBody* _inputActor, glm::vec2 _force);
	
	virtual void Draw(float _alpha) = 0;
	
	void ResolveCollision(RigidBody* _actor2, glm::vec2 _contact, glm::vec2* _collisionNomral = nullptr);
	void ResolveCollision(RigidBody* _actor2);
	void CalculateSmoothedPosition(float _alpha);
	
	float GetKineticEnergy();


	glm::vec2 GetPosition() { return m_position; }
	glm::vec2 GetVelocity() { return m_velocity; }
	

	float GetOrientation() { return m_orientation; }
	float GetMass() { return m_mass; }
	float GetMoment() { return m_moment; }
	float GetPotentialEnergy(glm::vec2  _gravity);

	void SetMass(float _mass) { m_mass = _mass; }
	void SetPosition(glm::vec2 _pos) { m_position = _pos; }
	
public:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	glm::vec2 m_lastPosition;

	float m_mass;
	float m_orientation;
	float m_angularVelocity;
	float m_moment;

	float m_lastOrientation;

	glm::vec2 m_smoothedPosition;
	glm::vec2 m_smoothedLocalX;
	glm::vec2 m_smoothedLocalY;

};

