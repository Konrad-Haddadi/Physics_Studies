#pragma once
#include "Box.h"
#include "Texture.h"
#include "PhysicsScene.h"

class WoodenBox : public Box
{
public:
	WoodenBox(glm::vec2 _pos, glm::vec2 _velocity, float _orientation, float _mass,	glm::vec2 _extents, aie::Texture* _texture, int _health);
	~WoodenBox();

	void Draw(aie::Renderer2D* _renderer) override;
	void DrawGizmos(float _alpha) override;


	void Update(float _dt) override;
	void OnCollisionEnter(RigidBody* _other) override;

public:
	aie::Texture* texture;
	int health;
	PhysicsScene* physicsScene;
};

