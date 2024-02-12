#pragma once
#include <vector>
class GameObject;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Update(float _dt);
	void Draw();
	void SpawnObject(GameObject* _obj);
	void RemoveObject(GameObject* _obj);

public:
	std::vector<GameObject*> objectList;
};

