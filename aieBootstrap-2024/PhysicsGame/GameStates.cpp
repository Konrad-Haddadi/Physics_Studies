#include "GameStates.h"
#include "GameStateManager.h"

GameStates::GameStates(StateManager* _stateManager)
	: States(_stateManager), m_input(aie::Input::getInstance())
{
	gameStateManager = dynamic_cast<GameStateManager*>(_stateManager);
}