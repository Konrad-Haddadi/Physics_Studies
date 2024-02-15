#pragma once

#include "Circle.h"
#include "PhysicsScene.h"
#include "GameObject.h"
#include <glm/glm.hpp>
#include "Texture.h"
#include "Renderer2D.h"

class Pig : public Circle
{
public:
	Pig(glm::vec2 _pos, glm::vec2 _size, glm::vec2 _force, float _mass, aie::Texture* _texture, float _health);
	~Pig();

	void Draw(aie::Renderer2D* _renderer) override;
	void Update(float _dt) override;

public:
	float health;
	PhysicsScene* physicsScene;
	aie::Texture* texture;
	bool dead;
};

