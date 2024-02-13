#include "SlingShot.h"

SlingShot::SlingShot(glm::vec2 _pos, glm::vec2 _size, aie::Texture* _texture)
	: Box(_pos, glm::vec2(0), 0, 0, _size, glm::vec4(0)), texture(_texture)
{
	SetKinematic(true);
}

SlingShot::~SlingShot()
{
}

void SlingShot::Draw(aie::Renderer2D* _renderer)
{
	_renderer->drawSprite(texture, m_position.x, m_position.y, m_extents.x * 2, m_extents.y * 2, m_orientation);

}

void SlingShot::Update(float _dt)
{

}
