#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"

class GameStateManager;

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

	GameStateManager* m_gameStateManager;
	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;
	PhysicsScene* m_physicsScene;
};