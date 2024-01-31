#pragma once

class States;

class StateManager
{
public:
	StateManager() : currentState(nullptr), nextState(nullptr) {}
	StateManager(States* _firstState) : currentState(_firstState), nextState(nullptr) {}
	~StateManager() {}

	void SetNextState(States* _newState) { nextState = _newState; }
	
	void StartUp();
	void virtual Update(float _dt);
	void Draw();
	void ShutDown();

public:
	States* currentState;
	States* nextState;
};

