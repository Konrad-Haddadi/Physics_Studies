#pragma once

#include "Texture.h"
#include "Input.h"
#include "Renderer2D.h"
#include <glm/glm.hpp>

class Button
{
public:
	Button(glm::vec2 _pos ,glm::vec2 _size, aie::Texture* _texture);
	~Button();

	void Update(aie::Input* _input);
	void Draw(aie::Renderer2D* _renderer);

public:
	glm::vec2 pos;
	glm::vec2 size;
	aie::Texture* texture;
	glm::vec4 overlay;
	bool hovered;
};

