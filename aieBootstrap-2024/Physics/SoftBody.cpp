#include "SoftBody.h"
#include "Circle.h"
#include "Box.h"
#include "PhysicsScene.h"
#include "Spring.h"
#include <vector>

void SoftBody::BuildCircle(PhysicsScene* _scene, glm::vec2 _pos, float _damping, float _springForce,float _spacing, std::vector<std::string>& _strings)
{
	int numColumns = _strings.size();
	int numRows = _strings[0].length();

	Circle** circles = new Circle* [numRows * numColumns];

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColumns; j++)
		{
			if (_strings[j][i] == '0')
			{
				circles[i * numColumns + j] = new Circle(_pos + glm::vec2(i, j) * _spacing, glm::vec2(0), 1.0f, 2.0f, glm::vec4(1, 0, 0, 1));
				_scene->AddActor(circles[i * numColumns + j]);
			}
			else
				circles[i * numColumns + j] = nullptr;
		}
	}

	for (int i = 1; i < numRows; i++)
	{
		for (int j = 1; j < numColumns; j++)
		{
			Circle* s11 = circles[i * numColumns + j];
			Circle* s01 = circles[(i - 1) * numColumns + j];
			Circle* s10 = circles[i * numColumns + j - 1];
			Circle* s00 = circles[(i - 1) * numColumns + j - 1];

			// make springs to cardinal neighbours
			if (s11 && s01)
				_scene->AddActor(new Spring(s11, s01, _springForce, _damping, _spacing, glm::vec4(1,0,0,1)));
			if (s11 && s10)
				_scene->AddActor(new Spring(s11, s10, _springForce, _damping, _spacing, glm::vec4(1, 0, 0, 1)));
			if (s10 && s00)
				_scene->AddActor(new Spring(s10, s00, _springForce, _damping, _spacing, glm::vec4(1, 0, 0, 1)));
			if (s01 && s00)
				_scene->AddActor(new Spring(s01, s00, _springForce, _damping, _spacing, glm::vec4(1, 0, 0, 1)));

			if(s11 && s00)
				_scene->AddActor(new Spring(s11, s00, _springForce, _damping));
			if (s01 && s10)
				_scene->AddActor(new Spring(s01, s10, _springForce, _damping));


			bool endOfJ = j == numColumns - 1;
			bool endOfI = i == numRows - 1;

			Circle* s22 = (!endOfI && !endOfJ) ? circles[(i + 1) * numColumns + (j + 1)] : nullptr;
			Circle* s02 = !endOfJ ? circles[(i - 1) * numColumns + (j + 1)] : nullptr;
			Circle* s20 = !endOfI ? circles[(i + 1) * numColumns + j - 1] : nullptr;

			if (s22 && s02)
				_scene->AddActor(new Spring(s22, s02, _springForce, _damping));

			if (s22 && s20)
				_scene->AddActor(new Spring(s22, s20, _springForce, _damping));

			if (s20 && s00)
				_scene->AddActor(new Spring(s20, s00, _springForce, _damping));

			if (s02 && s00)
				_scene->AddActor(new Spring(s02, s00, _springForce, _damping));

		}
	}


}

void SoftBody::BuildSquare(PhysicsScene* _scene, glm::vec2 _pos, float _damping, float _springForce, float _spacing, std::vector<std::string>& _strings)
{
	int numColumns = _strings.size();
	int numRows = _strings[0].length();

	Box** boxes = new Box * [numRows * numColumns];

	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numColumns; j++)
		{
			if (_strings[j][i] == '0')
			{
				boxes[i * numColumns + j] = new Box(_pos + glm::vec2(i, j) * _spacing, glm::vec2(0), 0.f, 1.0f, glm::vec2(_spacing *.25f, _spacing * .25f), glm::vec4(1, 0, 0, 1));
				_scene->AddActor(boxes[i * numColumns + j]);
			}
			else
				boxes[i * numColumns + j] = nullptr;
		}
	}

	for (int i = 1; i < numRows; i++)
	{
		for (int j = 1; j < numColumns; j++)
		{
			Box* s11 = boxes[i * numColumns + j];
			Box* s01 = boxes[(i - 1) * numColumns + j];
			Box* s10 = boxes[i * numColumns + j - 1];
			Box* s00 = boxes[(i - 1) * numColumns + j - 1];

			// make springs to cardinal neighbours
			if (s11 && s01)
				_scene->AddActor(new Spring(s11, s01, _springForce, _damping, _spacing, glm::vec4(1, 0, 0, 1)));
			if (s11 && s10)
				_scene->AddActor(new Spring(s11, s10, _springForce, _damping, _spacing, glm::vec4(1, 0, 0, 1)));
			if (s10 && s00)
				_scene->AddActor(new Spring(s10, s00, _springForce, _damping, _spacing, glm::vec4(1, 0, 0, 1)));
			if (s01 && s00)
				_scene->AddActor(new Spring(s01, s00, _springForce, _damping, _spacing, glm::vec4(1, 0, 0, 1)));

			if (s11 && s00)
				_scene->AddActor(new Spring(s11, s00, _springForce, _damping));
			if (s01 && s10)
				_scene->AddActor(new Spring(s01, s10, _springForce, _damping));


			bool endOfJ = j == numColumns - 1;
			bool endOfI = i == numRows - 1;

			Box* s22 = (!endOfI && !endOfJ) ? boxes[(i + 1) * numColumns + (j + 1)] : nullptr;
			Box* s02 = !endOfJ ? boxes[(i - 1) * numColumns + (j + 1)] : nullptr;
			Box* s20 = !endOfI ? boxes[(i + 1) * numColumns + j - 1] : nullptr;

			if (s22 && s02)
				_scene->AddActor(new Spring(s22, s02, _springForce, _damping));

			if (s22 && s20)
				_scene->AddActor(new Spring(s22, s20, _springForce, _damping));

			if (s20 && s00)
				_scene->AddActor(new Spring(s20, s00, _springForce, _damping));

			if (s02 && s00)
				_scene->AddActor(new Spring(s02, s00, _springForce, _damping));

		}
	}
}
