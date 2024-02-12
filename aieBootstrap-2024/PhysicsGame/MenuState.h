#pragma once

#include "GameStates.h"

class StateManager;
class PhysicsScene;

class MenuState : public GameStates
{
public:
	MenuState(StateManager* _stateMachine, aie::Renderer2D* _renderer, PhysicsScene* _physicsScene) 
		: GameStates(_stateMachine, _renderer, _physicsScene) {}
	~MenuState() {}

	// Inherited via GameStates
	void StateEnter() override;

	void StateUpdate(float _dt) override;

	void StateDraw() override;

	void StateExit() override;

	
};

