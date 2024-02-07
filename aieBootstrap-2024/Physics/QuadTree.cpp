#include "QuadTree.h"
#include "Gizmos.h"
#include <glm/glm.hpp>

QuadTree::QuadTree(glm::vec2 _size, glm::vec2 _pos, int _limit, QuadTree* _quadTree)
	: m_extents(_size), m_pos(_pos), m_limit(_limit), m_quadTree(_quadTree), m_split(false)
{
}

void QuadTree::Update(float _dt)
{
	/*if (m_split)
	{
		for (QuadTree* quad : quads)
			quad->Update(_dt);		
	}

	if (contents.size() >= m_limit)
	{
		Split();
		contents.clear();
	}

	if (GetBrachContentSize() <= m_limit)
	{
		for (int i = 0; i < quads.size(); i++)
		{
			for (int j = 0; j < quads[0]->contents.size(); j++)
			{
				contents.push_back(quads[0]->contents[j]);
			}

			RemoveQuad(quads[0]);
		}
	}*/


	for (int j = 0; j < contents.size(); j++)
	{
		if (!CheckContents(contents[j]))
		{
			contents.erase(contents.begin() + j);
			break;
		}
	}

}

void QuadTree::Draw()
{
	if (m_split)
	{
		for (QuadTree* quad : quads)
			quad->Draw();
	}

	aie::Gizmos::add2DAABB(m_pos, m_extents * 0.5f, glm::vec4(1, 1, 1, 1));

}

void QuadTree::Split()
{
	for (float x = -0.5; x < 1.5; x++)
	{
		for (float y = -0.5; y < 1.5 ; y++)
		{
			quads.push_back(new QuadTree(m_extents * .5f, glm::vec2(m_pos.x + (m_extents.x * .5f) * x, m_pos.y + (m_extents.y * .5f) * y), m_limit, this));
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < contents.size(); j++)
		{
			glm::vec2 boxPos = quads[i]->m_pos;
			glm::vec2 boxSize = quads[i]->m_extents;

			glm::vec2 contentPos = contents[j]->GetPosition();

			if (contentPos.x > boxPos.x - boxSize.x &&
				contentPos.x < boxPos.x + boxSize.x &&
				contentPos.y > boxPos.y - boxSize.y &&
				contentPos.y < boxPos.y + boxSize.y)
				quads[i]->contents.push_back(contents[j]);
		}
	}
	m_split = true;
}

bool QuadTree::CheckContents(RigidBody* _obj)
{	
	if (!DoesContrain(_obj->GetPosition()))
	{
		if (m_quadTree)
		{
			m_quadTree->CheckContents(_obj);
		}		

		return false;
	}

	return true;
}

bool QuadTree::DoesContrain(glm::vec2 _pos)
{
	for (int i = 0; i < quads.size(); i++)
	{		
		glm::vec2 boxPos = quads[i]->m_pos;
		glm::vec2 boxSize = quads[i]->m_extents;
		
		if (_pos.x > boxPos.x - boxSize.x &&
			_pos.x < boxPos.x + boxSize.x &&
			_pos.y > boxPos.y - boxSize.y &&
			_pos.y < boxPos.y + boxSize.y)
			return true;
		
	}
	return false;
}

void QuadTree::RemoveQuad(QuadTree* _quad)
{
	for (int j = 0; j < quads.size(); j++)
	{
		if(quads[j] == _quad)
		{
			quads.erase(quads.begin() + j);
			return;
		}
	}
}

int QuadTree::GetBrachContentSize()
{

	int contentLimit = 0;

	for (int i = 0; i < quads.size(); i++)
	{
		contentLimit += quads[i]->contents.size();
		contentLimit += quads[i]->GetBrachContentSize();
	}

	return contentLimit;
}
