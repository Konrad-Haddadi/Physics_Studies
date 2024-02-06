#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

class PhysicsScene;

class SoftBody
{
public:
	static void BuildCircle(PhysicsScene* _scene, glm::vec2 _pos, float _damping, float _springForce ,float _spacing, std::vector<std::string>& _strings);
	static void BuildSquare(PhysicsScene* _scene, glm::vec2 _pos, float _damping, float _springForce, float _spacing, std::vector<std::string>& _strings);

};

