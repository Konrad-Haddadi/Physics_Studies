#pragma once

#include "GameStates.h"

class GameStateManager;

class MenuState : public GameStates
{
public:
	MenuState(GameStateManager* _stateMachine) : GameStates(_stateMachine) {}
	~MenuState() {}

	// Inherited via GameStates
	void StateEnter() override;

	void StateUpdate() override;

	void StateDraw() override;

	void StateExit() override;

};

