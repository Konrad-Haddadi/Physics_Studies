#pragma once
#include "GameStates.h"

class Box;
class StateManager;

class PlayState : public GameStates
{
public:
	PlayState(StateManager* _stateMachine, aie::Renderer2D* _renderer, PhysicsScene* _physicsScene) 
		: GameStates(_stateMachine, _renderer, _physicsScene) {}
	~PlayState() {}


	// Inherited via GameStates
	void StateEnter() override;
	void StateUpdate(float _dt) override;
	void StateDraw() override;
	void StateExit() override;

	void AngryBirdsControls(aie::Input* _input, float _dt);

public:
	Box* slingShot;
	bool pull;
};

