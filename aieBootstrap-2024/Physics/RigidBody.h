#pragma once

#include "PhysicsObject.h"
#include <glm/glm.hpp>

const float MIN_ANGULAR_THRESHOLD = 10;
const float MIN_LINEAR_THRESHOLD = 10;

class RigidBody : public PhysicsObject
{
public:
	RigidBody(ShapeType _shapeID, glm::vec2 _pos, glm::vec2 _velocity, float _orientation, float _mass);
	~RigidBody();

	void FixedUpdate(glm::vec2 _gravity, float _timeStep) override;
	void ApplyForce(glm::vec2 _force);
	void ApplyForce(glm::vec2 _force, glm::vec2 _pos);
	void ApplyForceToActor(RigidBody* _inputActor, glm::vec2 _force);
	void ApplyForceToActor(RigidBody* _inputActor, glm::vec2 _force, glm::vec2 _collision);
	
	virtual void Draw(float _alpha) = 0;

	//virtual bool OnCollisionEnter(glm::vec2 _pos) {};
	//virtual bool OnTriggerEnter(glm::vec2 _pos) {};
	//
	//virtual void IsInsideTrigger() = 0;
	
	virtual bool IsInside(glm::vec2 _pos) { return false; };

	void ResolveCollision(RigidBody* _actor2, glm::vec2 _contact, glm::vec2* _collisionNomral = nullptr, float _pen = 0);
	void ResolveCollision(RigidBody* _actor2);
	void CalculateSmoothedPosition(float _alpha);
	void ApplyContactForces(RigidBody* _body2, glm::vec2 _norm, float _pen = 0);

	void CalculateAxes();
	float GetKineticEnergy();

	//glm::vec2 GetPosition() { return m_position; }
	glm::vec2 GetPosition() const { return m_position; }

	glm::vec2 GetVelocity() { return m_velocity; }
	
	float GetOrientation() { return m_orientation; }
	float GetAngularVelocity() { return m_angularVelocity; }

	float GetMass() { return m_isKinematic ? INT_MAX : m_mass; }
	float GetMoment() { return m_isKinematic ? INT_MAX : m_moment; }

	glm::vec2 GetLocalX() { return m_localX; }
	glm::vec2 GetLocalY() { return m_localY; }

	float GetLinearDrag() { return m_linearDrag; }
	float GetAngularDrag() { return m_angularDrag; }

	float GetPotentialEnergy(glm::vec2  _gravity);
	
	void SetMass(float _mass) { m_mass = _mass; }
	void SetPosition(glm::vec2 _pos) { m_position = _pos; }
	void SetKinematic(bool _state) { m_isKinematic = _state; }

	void SetLinearDrag(float _drag) { m_linearDrag = _drag; }
	void SetAngularDrag(float _drag) { m_angularDrag = _drag; }

	glm::vec2 ToWorld(glm::vec2 _contact, float _aplha);

	bool IsKinematic() { return m_isKinematic; }
public:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	glm::vec2 m_lastPosition;

	float m_mass;
	float m_orientation;
	float m_angularVelocity;
	float m_moment;

	float m_lastOrientation;

	glm::vec2 m_localX;
	glm::vec2 m_localY;

	glm::vec2 m_smoothedPosition;
	glm::vec2 m_smoothedLocalX;
	glm::vec2 m_smoothedLocalY;

	bool m_isKinematic;
	float m_linearDrag;
	float m_angularDrag;

	
};

