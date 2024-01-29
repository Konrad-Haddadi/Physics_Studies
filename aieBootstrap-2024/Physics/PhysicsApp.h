#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Input.h"
#include "Circle.h"

class PhysicsApp : public aie::Application {
public:

	PhysicsApp();
	virtual ~PhysicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	void Draw();
	void DrawText();

protected:

	PhysicsScene* m_physicsScene;
	Circle* rocket;
	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;


// ==== For Demos Only ====
public:
	void DemoStartUp(int _num);
	void DemoUpdate(aie::Input* _input, float _dt);
};