#include "SoftBody.h"
#include "Circle.h"
#include <vector>

void SoftBody::Build(PhysicsScene* _scene, glm::vec2 _pos, float _damping, float _springForce,float _spacing, std::vector<std::string>& _strings)
{
	int numColumns = _strings.size();
	int numRows = _strings[0].length();

	Circle** circles = new Circle* [numRows * numColumns];

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColumns; j++)
		{
			
		}
	}


}
