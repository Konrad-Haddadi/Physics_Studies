#include "StateManager.h"
#include "States.h"
#include "Gizmos.h"

void StateManager::StartUp()
{
	if (nextState != nullptr)
	{		
		currentState = nextState;
		nextState = nullptr;		
	}

	if (currentState != nullptr)
		currentState->StateEnter();

	
}

void StateManager::Update(float _dt)
{
	if (currentState != nullptr)
		currentState->StateUpdate(_dt);

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
	aie::Gizmos::clear();

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
