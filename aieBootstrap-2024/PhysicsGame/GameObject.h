#pragma once

#include "Renderer2D.h"
#include "Texture.h"

#include <glm/glm.hpp>

class GameObject
{
public:
	GameObject(glm::vec2 _pos, glm::vec2 _size, aie::Texture* _texture) : pos(_pos), size(_size), texture(_texture) {};

	virtual void Load() = 0;
	virtual void Update(float _dt) = 0;
	virtual void Draw(aie::Renderer2D* _renderer) = 0;
	virtual void Unload() = 0;

protected:
	glm::vec2 pos;
	glm::vec2 size;
	aie::Texture* texture;
};

