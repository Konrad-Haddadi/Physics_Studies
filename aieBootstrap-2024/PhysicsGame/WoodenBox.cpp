#include "WoodenBox.h"
#include "Box.h"
#include "Pig.h"
#include <glm/glm.hpp>
#include <Gizmos.h>

WoodenBox::WoodenBox(glm::vec2 _pos, glm::vec2 _velocity, float _orientation, float _mass, glm::vec2 _extents, aie::Texture* _texture, int _health, bool _invincible)
	: Box(_pos, _velocity, _orientation, _mass, _extents, glm::vec4(1, 1, 1, 1)), texture(_texture), health(_health), invincible(_invincible)
{
	dead = false;
	m_friction = .8f;
}

WoodenBox::~WoodenBox()
{
}

void WoodenBox::Draw(aie::Renderer2D* _renderer)
{
	_renderer->drawSprite(texture, m_position.x, m_position.y, m_extents.x * 2, m_extents.y * 2, m_orientation);

	if(m_velocity.length() > .5f)
		_renderer->drawLine(m_position.x, m_position.y, m_position.x + m_velocity.x, m_position.y + m_velocity.y);
}

void WoodenBox::Update(float _dt)
{
	if (invincible)
		return;

	if (dead)
	{
		physicsScene->RemoveActor(this);
		return;
	}	
	if (health <= 0)
		dead = true;
}

void WoodenBox::OnCollisionEnter(RigidBody* _other)
{
	Pig* pig = dynamic_cast<Pig*>(_other);

	float force = glm::abs(GetVelocity().x) + glm::abs(GetVelocity().y);
	force /= 100;

	if (pig != nullptr)
	{
		if (force > .75f)
		{
			pig->health -= 1;
			pig->damaged = true;

			health -= 1;
		}
	}

	if (force > health)
		health -= 1;
}

void WoodenBox::DrawGizmos(float _alpha)
{
	CalculateSmoothedPosition(_alpha);

	glm::vec2 p1 = m_smoothedPosition - m_smoothedLocalX * m_extents.x - m_smoothedLocalY * m_extents.y;
	glm::vec2 p2 = m_smoothedPosition + m_smoothedLocalX * m_extents.x - m_smoothedLocalY * m_extents.y;
	glm::vec2 p3 = m_smoothedPosition - m_smoothedLocalX * m_extents.x + m_smoothedLocalY * m_extents.y;
	glm::vec2 p4 = m_smoothedPosition + m_smoothedLocalX * m_extents.x + m_smoothedLocalY * m_extents.y;

	aie::Gizmos::add2DTri(p1, p2, p4, m_color);
	aie::Gizmos::add2DTri(p1, p4, p3, m_color);


}
