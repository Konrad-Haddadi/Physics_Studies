#pragma once
#include "GameStates.h"

class StateManager;

class PlayState : public GameStates
{
public:
	PlayState(StateManager* _stateMachine) : GameStates(_stateMachine) {}
	~PlayState() {}


	// Inherited via GameStates
	void StateEnter() override;

	void StateUpdate() override;

	void StateDraw() override;

	void StateExit() override;

};

