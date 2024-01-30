#pragma once

class States;

class StateManager
{
public:
	StateManager() {}
	StateManager(States* _firstState) : currentState(_firstState) {}
	~StateManager() {}

	void SetNextState(States* _newState) { nextState = _newState; }
	
	void StartUp();
	void Update(float _dt);
	void Draw();
	void ShutDown();

public:
	States* currentState;
	States* nextState;
};

