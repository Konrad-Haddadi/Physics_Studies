#pragma once
#include "Box.h"
#include "PhysicsScene.h"
#include "GameObject.h"
#include <glm/glm.hpp>
#include "Texture.h"
#include "Renderer2D.h"

class SlingShot : public Box
{
public:
	SlingShot(glm::vec2 _pos, glm::vec2 _size, aie::Texture* _texture);
	~SlingShot();

	void Draw(aie::Renderer2D* _renderer) override;
	void Update(float _dt) override;

public:

	aie::Texture* texture;
};

