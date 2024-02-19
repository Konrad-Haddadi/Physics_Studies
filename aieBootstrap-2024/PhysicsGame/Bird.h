#pragma once

#include "Circle.h"
#include "PhysicsScene.h"
#include <glm/glm.hpp>
#include "Texture.h"
#include "Renderer2D.h"


class Bird : public Circle
{
public:
	Bird(glm::vec2 _pos, glm::vec2 _size, glm::vec2 _force, float _mass, aie::Texture* _texture, float _lifeTimer, int _damage);
	~Bird();		

	void Draw(aie::Renderer2D* _renderer) override;
	void DrawGizmos(float _alpha) override;

	void Update(float _dt) override;
	void OnCollisionEnter(RigidBody* _other) override;

public: 
	float timer;
	float lifeTimer;
	PhysicsScene* physicsScene;
	aie::Texture* texture;
	int damage;
	bool countDown;
	bool remove;
};

