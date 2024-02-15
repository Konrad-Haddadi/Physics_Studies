#include "Pig.h"

Pig::Pig(glm::vec2 _pos, glm::vec2 _size, glm::vec2 _force, float _mass, aie::Texture* _texture, float _health)
	: Circle(_pos, _force, _mass, _size.x, glm::vec4(1, 1, 1, 1)), health(_health), texture(_texture)
{
	SetLinearDrag(.5f);
	SetAngularDrag(.5f);
	dead = false;
}

Pig::~Pig()
{
}

void Pig::Draw(aie::Renderer2D* _renderer)
{
	_renderer->drawSprite(texture, m_position.x, m_position.y, m_radius * 2, m_radius * 2, m_orientation);
}

void Pig::Update(float _dt)
{
	if (health <= 0)
	{
		dead = true;
		physicsScene->RemoveActor(this);
	}
}
