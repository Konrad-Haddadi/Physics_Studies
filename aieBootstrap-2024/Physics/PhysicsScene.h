#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "PhysicsObject.h"
#include "Renderer2D.h"

class Plane;
class Circle;
class RigidBody;

class PhysicsScene
{
public:
	PhysicsScene(aie::Renderer2D* _renderer);
	~PhysicsScene();

	void AddActor(PhysicsObject* _actor);
	void RemoveActor(PhysicsObject* _actor);
	void ClearActors();

	void Update(float _dt);
	void Draw();

	void SetGravity(const glm::vec2 _gravity) { m_gravity = _gravity; }
	glm::vec2 GetGravity() const { return m_gravity; }

	void SetTimeStep(const float _timeStep) { m_timeStep = _timeStep; }
	float GetTimeStep() const { return m_timeStep; }
	float GetTotalEnergy();

	void CheckForCollision();

	static bool Plane2Plane(PhysicsObject* _lhs, PhysicsObject* _rhs);//
	static bool Plane2Circle(PhysicsObject* _lhs, PhysicsObject* _rhs);//
	static bool Plane2Box(PhysicsObject* _lhs, PhysicsObject* _rhs);//

	static bool Circle2Circle(PhysicsObject* _lhs, PhysicsObject* _rhs);//
	static bool Circle2Plane(PhysicsObject* _lhs, PhysicsObject* _rhs);
	static bool Circle2Box(PhysicsObject* _lhs, PhysicsObject* _rhs);//
	
	static bool Box2Plane(PhysicsObject* _lhs, PhysicsObject* _rhs);
	static bool Box2Circle(PhysicsObject* _lhs, PhysicsObject* _rhs);
	static bool Box2Box(PhysicsObject* _lhs, PhysicsObject* _rhs);//

protected:
	aie::Renderer2D* m_renderer;
	glm::vec2 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
};