#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Input.h"
#include "Circle.h"
#include "Box.h"
#include "QuadTree.h"

static float m_aspectRatio = 16.f / 9.f;
static float m_extents = 100;

class PhysicsApp : public aie::Application {
public:

	PhysicsApp();
	virtual ~PhysicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void Update(float _dt);
	void Draw();
	void DrawText();
	void SetupContinuousDemo(glm::vec2 _startPos, float _inclination, float _speed, float _gravity);
	void AngryBirdShootLine(glm::vec2 _startPos, float _inclination, float _speed, float _gravity);

	void AngryBirdsControls(aie::Input* _input, float _dt);
	void Controls(aie::Input* _input, float _dt);
	glm::vec2 ScreenToWorld(glm::vec2 screenPos);

protected:

	aie::Texture* m_texture;
	PhysicsScene* m_physicsScene;
	Circle* rocket;
	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;
	float m_cameraX, m_cameraY;
	Box* slingShot;
	QuadTree* m_quadTree;

// ==== For Demos Only ====
public:
	void DemoStartUp(int _num);
	void DemoUpdate(aie::Input* _input, float _dt);
};