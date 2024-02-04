#pragma once

#include "StateManager.h"
#include "Renderer2D.h"

class PhysicsScene;
class States;

class GameStateManager : public StateManager
{
public:
	GameStateManager(States* _firstState, PhysicsScene* _physicsScene, aie::Renderer2D* _renderer);

public:
	PhysicsScene* physicsScene;
	aie::Renderer2D* renderer;
};

