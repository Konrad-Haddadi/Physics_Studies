#include "GameStateManager.h"
#include "States.h"

GameStateManager::GameStateManager(PhysicsGameStates* _physicsApp, States* _firstState, PhysicsScene* _physicsScene, aie::Renderer2D* _renderer)
	: StateManager(_firstState), physicsScene(_physicsScene), renderer(_renderer), physicsApp(_physicsApp)
{
}