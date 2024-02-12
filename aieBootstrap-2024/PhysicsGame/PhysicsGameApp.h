#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Application.h"

class GameStateManager;

static float m_aspectRatio = 16.f / 9.f;
static float m_extents = 100;

class PhysicsGameStates : public aie::Application {
public:

	PhysicsGameStates();
	virtual ~PhysicsGameStates();

	void DrawFPS();
	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	glm::vec2 ScreenToWorld(glm::vec2 screenPos);
	void AngryBirdShootLine(glm::vec2 _startPos, float _inclination, float _speed, float _gravity);

protected:

	GameStateManager* m_gameStateManager;
	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;
	PhysicsScene* m_physicsScene;
};