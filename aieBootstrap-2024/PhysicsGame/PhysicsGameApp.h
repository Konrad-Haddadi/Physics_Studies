#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "../Physics/PhysicsScene.h"

class StateManager;

class PhysicsGameStates : public aie::Application {
public:

	PhysicsGameStates();



	virtual ~PhysicsGameStates();

	void DrawFPS();
	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	StateManager* m_gameStateManager;
	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;
};