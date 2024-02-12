#include "WoodenBox.h"
#include "Box.h"
#include <glm/glm.hpp>

WoodenBox::WoodenBox(glm::vec2 _pos, glm::vec2 _velocity, float _orientation, float _mass, glm::vec2 _extents, aie::Texture* _texture, int _health)
	: Box(_pos, _velocity, _orientation, _mass, _extents, glm::vec4(1, 1, 1, 1)), texture(_texture), health(_health)
{
}

WoodenBox::~WoodenBox()
{
}

void WoodenBox::Draw(aie::Renderer2D* _renderer)
{
	_renderer->drawSprite(texture, m_position.x, m_position.y, m_extents.x * 2, m_extents.y * 2, m_orientation);

}
