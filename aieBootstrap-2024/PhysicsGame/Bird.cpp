#include "Bird.h"
#include "Circle.h"


Bird::Bird(glm::vec2 _pos, glm::vec2 _size, glm::vec2 _force, float _mass, aie::Texture* _texture, float _lifeTimer)
	: Circle(_pos, _force, _mass, _size.x, glm::vec4(1, 1, 1, 1)) , lifeTimer(_lifeTimer), timer(0), texture(_texture) 
{
	
}


Bird::~Bird()
{
}


void Bird::Update(float _dt)
{
	timer += _dt;

	if (timer > lifeTimer)
		physicsScene->RemoveActor(this);
}



void Bird::Draw(aie::Renderer2D* _renderer)
{
	_renderer->drawSprite(texture, m_position.x, m_position.y, m_radius * 5, m_radius * 5, m_orientation);
}