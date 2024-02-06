#include "Box.h"
#include "RigidBody.h"
#include "Gizmos.h"
#include <glm/glm.hpp>

Box::Box(glm::vec2 _pos, glm::vec2 _velocity, float _orientation, float _mass, glm::vec2 _extents, glm::vec4 _color)
	: RigidBody(ShapeType::BOX, _pos, _velocity, _orientation, _mass), m_extents(_extents), m_color(_color)
{
	m_width = _extents.x * 2;
	m_height = _extents.y * 2;
	
	m_moment = 1.0f / 12.0f * m_mass * (m_width * m_width) + (m_height * m_height);
}

void Box::Draw(float _alpha)
{
	CalculateSmoothedPosition(_alpha);

	glm::vec2 p1 = m_smoothedPosition - m_smoothedLocalX * m_extents.x - m_smoothedLocalY * m_extents.y;
	glm::vec2 p2 = m_smoothedPosition + m_smoothedLocalX * m_extents.x - m_smoothedLocalY * m_extents.y;
	glm::vec2 p3 = m_smoothedPosition - m_smoothedLocalX * m_extents.x + m_smoothedLocalY * m_extents.y;
	glm::vec2 p4 = m_smoothedPosition + m_smoothedLocalX * m_extents.x + m_smoothedLocalY * m_extents.y;

	aie::Gizmos::add2DTri(p1, p2, p4, m_color);
	aie::Gizmos::add2DTri(p1, p4, p3, m_color);
}


bool Box::CheckBoxCorners(const Box& box, glm::vec2& contact, int& numContacts, float& pen, glm::vec2& edgeNormal)
{
	float minX;
	float maxX;
	float minY;
	float maxY;

	float boxW = box.GetExtents().x * 2;
	float boxH = box.GetExtents().y * 2;

	int numLocalContacts = 0;
	glm::vec2 localContact(0, 0);
	bool first = true;

	// loop over all corners of the other box
	for (float x = -box.GetExtents().x; x < boxW; x += boxW)
	{
		for (float y = -box.GetExtents().y; y < boxH; y += boxH)
		{
			// Get the position in worldspace
			glm::vec2 p = box.GetPosition() + x * box.m_localX + y * box.m_localY;
			// Get the position in our box's space
			glm::vec2 p0(glm::dot(p - m_position, m_localX),
				glm::dot(p - m_position, m_localY));

			// update the extents in each cardinal direction in our box's space
			// (ie extents along the separating axes)
			if (first || p0.x < minX) minX = p0.x;
			if (first || p0.x > maxX) maxX = p0.x;
			if (first || p0.y < minY) minY = p0.y;
			if (first || p0.y > maxY) maxY = p0.y;

			// if this corner is inside the box, add it to the list of contact points
			if (p0.x >= -m_extents.x && p0.x <= m_extents.x &&
				p0.y >= -m_extents.y && p0.y <= m_extents.y)
			{
				numLocalContacts++;
				localContact += p0;
			}
			first = false;
		}
	}

	// if we lie entirely to one side of the box along one axis, we've found a separating
	// axis, and we can exit
	if (maxX <= -m_extents.x || minX >= m_extents.x ||
		maxY <= -m_extents.y || minY >= m_extents.y)
		return false;
	if (numLocalContacts == 0)
		return false;

	bool res = false;
	contact += m_position + (localContact.x * m_localX + localContact.y * m_localY) /
		(float)numLocalContacts;
	numContacts++;

	// find the minimum penetration vector as a penetration amount and normal
	float pen0 = m_extents.x - minX;
	if (pen0 > 0 && (pen0 < pen || pen == 0)) 
	{
		edgeNormal = m_localX;
		pen = pen0;
		res = true;
	}
	pen0 = maxX + m_extents.x;
	if (pen0 > 0 && (pen0 < pen || pen == 0))
	{
		edgeNormal = -m_localX;
		pen = pen0;
		res = true;
	}
	pen0 = m_extents.y - minY;
	if (pen0 > 0 && (pen0 < pen || pen == 0)) 
	{
		edgeNormal = m_localY;
		pen = pen0;
		res = true;
	}
	pen0 = maxY + m_extents.y;
	if (pen0 > 0 && (pen0 < pen || pen == 0)) 
	{
		edgeNormal = -m_localY;
		pen = pen0;
		res = true;
	}
	return res;
}

bool Box::IsInside(glm::vec2 _pos)
{
	if (_pos.x > m_position.x - m_extents.x &&
		_pos.x < m_position.x + m_extents.x &&
		_pos.y > m_position.y - m_extents.y &&
		_pos.y < m_position.y + m_extents.y)
		return true;

	return false;
}




