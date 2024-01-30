#pragma once

#include "States.h"
#include "Input.h"

class GameStates : public States
{
public:
	GameStates() {}
	~GameStates() {}

	void StateEnter(StateManager * _stateManager) = 0;
	void StateUpdate(StateManager* _stateManager) = 0;
	void StateDraw(StateManager* _stateManager) = 0;
	void StateExit(StateManager* _stateManager) = 0;

protected:
	aie::Input* m_input;

};