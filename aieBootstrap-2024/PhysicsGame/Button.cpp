#include "Button.h"
#include "Renderer2D.h"
#include "Gizmos.h";
#include "Input.h"

Button::Button(glm::vec2 _pos , glm::vec2 _size, aie::Texture* _texture)
	:pos(_pos), size(_size), texture(_texture), overlay((0,0,0,0))
{

}

Button::~Button()
{

}

void Button::Update(aie::Input* _input)
{
	glm::vec2 mousePos = glm::vec2(_input->getMouseX(), _input->getMouseY());

	if (mousePos.x >= pos.x - size.x / 2 && mousePos.x <= pos.x + size.x / 2 &&
		mousePos.y >= pos.y - size.y / 2 && mousePos.y <= pos.y + size.y / 2)
		hovered = true;
	else
		hovered = false;

	if (hovered)
		overlay = glm::vec4(1, 1, 1, 0.5f);
	else
		overlay = glm::vec4(0, 0, 0, 0);
}

void Button::Draw(aie::Renderer2D* _renderer)
{
	_renderer->drawSprite(texture, pos.x, pos.y, size.x, size.y);
}

