#include "StateManager.h"
#include "States.h"

void StateManager::StartUp()
{
	if (currentState != nullptr)
		currentState->StateEnter();

	nextState = nullptr;
}

void StateManager::Update(float _dt)
{
	if (currentState != nullptr)
		currentState->StateUpdate();

	if (nextState != nullptr)
	{
		currentState->StateExit();

		delete currentState;
		currentState = nextState;

		nextState = nullptr;
		currentState->StateEnter();
	}
}

void StateManager::Draw()
{
	if (currentState != nullptr)
		currentState->StateDraw();
}

void StateManager::ShutDown()
{
	if (currentState != nullptr)
	{
		currentState->StateExit();
		delete currentState;
	}

}
