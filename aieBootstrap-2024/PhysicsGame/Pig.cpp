#include "Pig.h"
#include <Gizmos.h>

Pig::Pig(glm::vec2 _pos, glm::vec2 _size, glm::vec2 _force, float _mass, aie::Texture* _texture, float _health)
	: Circle(_pos, _force, _mass, _size.x, glm::vec4(1, 1, 1, 1)), health(_health), texture(_texture)
{
	SetLinearDrag(.5f);
	SetAngularDrag(.5f);
	dead = false;
	damageCounter = 0;
	damageTimer = 0;
	damaged = false;
}

Pig::~Pig()
{
}

void Pig::Draw(aie::Renderer2D* _renderer)
{
	_renderer->drawSprite(texture, m_position.x, m_position.y, m_radius * 2, m_radius * 2, m_orientation);

	if (damaged)
	{
		if (damageTimer > .2f)
			_renderer->drawCircle(m_position.x, m_position.y, m_radius);
	}
}


void Pig::DrawGizmos(float _alpha)
{
	CalculateSmoothedPosition(_alpha);

	aie::Gizmos::add2DCircle(m_position, m_radius, 15, m_color);
}

void Pig::Update(float _dt)
{
	if (health <= 0)
	{
		physicsScene->RemoveActor(this);
		dead = true;	
		return;
	}


	if (damaged)
	{
		if (damageCounter >= 3)
		{
			damageTimer = 0;
			damageCounter = 0;
			damaged = false;
		}

		damageTimer += _dt;

		if (damageTimer > .4f)
		{
			damageCounter++;
			damageTimer = 0;
		}
	}
}


void Pig::OnCollisionEnter(RigidBody* _other)
{
	float force = glm::abs(GetVelocity().x) + glm::abs(GetVelocity().y);
	force /= 100;	

	if (force > health)
	{
		damaged = true;
		health -= 1;
	}
}
