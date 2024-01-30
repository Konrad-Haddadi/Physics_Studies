#pragma once

class StateManager;

class States
{
public:
	States() {};
	~States() {};

	virtual void StateEnter(StateManager* _stateManager) = 0;
	virtual void StateUpdate(StateManager* _stateManager) = 0;
	virtual void StateDraw(StateManager* _stateManager) = 0;
	virtual void StateExit(StateManager* _stateManager) = 0;

};

