#pragma once
#include "Renderer2D.h"
#include "Input.h"
#include "PhysicsGameApp.h"

class Button;

class ButtonManager
{
public:
	ButtonManager(aie::Renderer2D* _renderer, aie::Input* _input);
	~ButtonManager();

	void Update();
	void Draw(/*PhysicsGameStates* _app*/);
	void SpawnButton(Button* _button);
	void RemoveButton(Button* _button);

private:
	std::vector<Button*> m_buttonList;
	aie::Renderer2D* m_renderer;
	aie::Input* m_input;
};

