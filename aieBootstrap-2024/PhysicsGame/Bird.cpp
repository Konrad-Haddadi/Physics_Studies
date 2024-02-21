#include "Bird.h"
#include "Circle.h"
#include "WoodenBox.h"
#include "Pig.h"
#include "SlingShot.h"
#include <Gizmos.h>

Bird::Bird(glm::vec2 _pos, glm::vec2 _size, glm::vec2 _force, float _mass, aie::Texture* _texture, float _lifeTimer, int _damage)
	: Circle(_pos, _force, _mass, _size.x, glm::vec4(1, 1, 1, 1)) , lifeTimer(_lifeTimer), timer(0), texture(_texture), damage(_damage), countDown(false)
{
	remove = false;
}


Bird::~Bird()
{
}


void Bird::Update(float _dt)
{
	if (!countDown)
		return;

	timer += _dt;

	if (timer > lifeTimer)
	{
		remove = true;
		physicsScene->RemoveActor(this);
	}
}

void Bird::DrawGizmos(float _alpha)
{
	CalculateSmoothedPosition(_alpha);

	aie::Gizmos::add2DCircle(m_position, m_radius, 15, m_color);
}

void Bird::OnCollisionEnter(RigidBody* _other)
{
	WoodenBox* box = dynamic_cast<WoodenBox*>(_other);
	Pig* pig = dynamic_cast<Pig*>(_other);
	SlingShot* sling = dynamic_cast<SlingShot*>(_other);

	float force = glm::abs(GetVelocity().x) + glm::abs(GetVelocity().y);
	force /= 100;

	if(_other!= nullptr && sling == nullptr)
		countDown = true;

	if (box != nullptr)
	{
		if (force > 1 )
		{
			box->health -= damage;
		}
	}

	if (pig != nullptr)
	{
		if (force > 1)
		{
			pig->health -= damage;
			pig->damaged = true;
		}	
	}
}



void Bird::Draw(aie::Renderer2D* _renderer)
{
	_renderer->drawSprite(texture, m_position.x, m_position.y, m_radius * 5, m_radius * 5, m_orientation);
}