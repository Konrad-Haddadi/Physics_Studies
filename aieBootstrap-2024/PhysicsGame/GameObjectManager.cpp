#include "GameObjectManager.h"
#include "GameObject.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	for (int i = 0; i < objectList.size(); i++)
	{
		delete objectList[i];
	}

	objectList.clear();
}

void GameObjectManager::Update(float _dt)
{
	for (GameObject* object : objectList)
		object->Update(_dt);
}

void GameObjectManager::Draw()
{
}

void GameObjectManager::SpawnObject(GameObject* _obj)
{
	objectList.push_back(_obj);
}

void GameObjectManager::RemoveObject(GameObject* _obj)
{
}
