#pragma once

#include "RigidBody.h"

#include <glm/glm.hpp>
#include <vector>


class QuadTree
{
public:
	QuadTree(glm::vec2 _size, glm::vec2 _pos, int _limit, QuadTree* _quadTree);
	~QuadTree() {}

	void Update(float _dt);
	void Draw();
	void Split();
	
	bool CheckContents(RigidBody* _obj);
	bool DoesContrain(glm::vec2 _pos);
	void RemoveQuad(QuadTree* _quad);

	int GetBrachContentSize();

public:
	std::vector<RigidBody*> contents;
	std::vector<QuadTree*> quads;
private:

	glm::vec2 m_extents;
	glm::vec2 m_pos;
	int m_limit;
	bool m_split;
	QuadTree* m_quadTree;
};

