#include "StateManager.h"
#include "States.h"

void StateManager::StartUp()
{
	if (currentState != nullptr)
		currentState->StateEnter(this);

	nextState = nullptr;
}

void StateManager::Update(float _dt)
{
	if (currentState != nullptr)
		currentState->StateUpdate(this);

	if (nextState != nullptr)
	{
		currentState->StateExit(this);

		delete currentState;
		currentState = nextState;

		nextState = nullptr;
		currentState->StateEnter(this);
	}
}

void StateManager::Draw()
{
	if (currentState != nullptr)
		currentState->StateDraw(this);
}

void StateManager::ShutDown()
{
	if (currentState != nullptr)
	{
		currentState->StateExit(this);
		delete currentState;
	}

}
