#include "ButtonManager.h"
#include "Button.h"
#include "Gizmos.h"
#include "PhysicsGameApp.h"

#include <vector>
ButtonManager::ButtonManager(aie::Renderer2D* _renderer, aie::Input* _input)
	: m_renderer(_renderer), m_input(_input)
{
	m_buttonList = std::vector<Button*>();
}

ButtonManager::~ButtonManager()
{
	for (int i = 0; i < m_buttonList.size(); i++)
	{
		delete m_buttonList[i];
	}

	m_buttonList.clear();
}

void ButtonManager::Update()
{
	for (Button* button : m_buttonList)
		button->Update(m_input);
}

void ButtonManager::Draw(/*PhysicsGameStates* _app*/)
{
	for (Button* button : m_buttonList)
	{
		button->Draw(m_renderer);
		//aie::Gizmos::add2DAABBFilled(_app->ScreenToWorld(button->pos), button->size * 0.5f, button->overlay);
	}
}

void ButtonManager::SpawnButton(Button* _button)
{
	m_buttonList.push_back(_button);
}

void ButtonManager::RemoveButton(Button* _button)
{
	for (int i = 0; i < m_buttonList.size(); i++)
	{
		if (m_buttonList[i] == _button)
		{
			delete _button;

			m_buttonList.erase(m_buttonList.begin() + i);
			return;
		}
	}
}
