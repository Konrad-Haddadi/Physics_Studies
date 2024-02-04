#pragma once
#include "GameStates.h"

class GameStateManager;

class PlayState : public GameStates
{
public:
	PlayState(GameStateManager* _stateMachine) : GameStates(_stateMachine) {}
	~PlayState() {}


	// Inherited via GameStates
	void StateEnter() override;

	void StateUpdate() override;

	void StateDraw() override;

	void StateExit() override;

};

