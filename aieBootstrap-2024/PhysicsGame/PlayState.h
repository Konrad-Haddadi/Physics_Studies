#pragma once

#include "GameStates.h"

class PlayState : public GameStates
{
public:
	PlayState() {}
	~PlayState() {}
	
	void StateEnter(StateManager* _stateManager) override;
	void StateUpdate(StateManager* _stateManager) override;
	void StateDraw(StateManager* _stateManager) override;
	void StateExit(StateManager* _stateManager) override;
};

