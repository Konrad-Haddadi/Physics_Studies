#pragma once

#include "States.h"
#include "Input.h"
#include "Renderer2D.h"

class StateManager;
class GameStateManager;
class PhysicsScene;
class ButtonManager;


class GameStates : public States
{
public:
	GameStates(StateManager* _stateManager, aie::Renderer2D* _renderer, PhysicsScene* _physicsScene);

	virtual void StateEnter() = 0;
	virtual void StateUpdate(float _dt) = 0;
	virtual void StateDraw() = 0;
	virtual void StateExit() = 0;

protected:
	aie::Input* m_input;
	PhysicsScene* m_physicsScene;
	GameStateManager* m_gameStateManager;
	ButtonManager* m_buttonManager;
	aie::Renderer2D* m_renderer;
};