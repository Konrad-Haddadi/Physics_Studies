#pragma once

#include "GameStates.h"

class MenuState : public GameStates
{
public:
	MenuState() {}
	~MenuState() {}

	void StateEnter(StateManager* _stateManager) override;
	void StateUpdate(StateManager* _stateManager) override;
	void StateDraw(StateManager* _stateManager) override;
	void StateExit(StateManager* _stateManager) override;


};

