#pragma once

class StateManager;

class States
{
public:
	States(StateManager* _stateManager) { };
	~States() {};

	virtual void StateEnter() = 0;
	virtual void StateUpdate(float _dt) = 0;
	virtual void StateDraw() = 0;
	virtual void StateExit() = 0;

};

