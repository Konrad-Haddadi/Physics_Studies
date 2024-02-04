#pragma once

#include "States.h"
#include "Input.h"

class StateManager;
class GameStateManager;

class GameStates : public States
{
public:
	GameStates(StateManager* _stateManager);
	~GameStates() {}

	virtual void StateEnter() = 0;
	virtual void StateUpdate() = 0;
	virtual void StateDraw() = 0;
	virtual void StateExit() = 0;

protected:
	aie::Input* m_input;
	PhysicsScene* m_physicsScene;
	GameStateManager* gameStateManager;
};