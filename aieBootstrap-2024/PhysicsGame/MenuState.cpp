#include "MenuState.h"
#include "Gizmos.h"
#include "StateManager.h"
#include "PlayState.h"
#include "GameStateManager.h"
#include "Button.h"
#include "ButtonManager.h"
#include "PhysicsGameApp.h"
#include <glm/glm.hpp>

//Button* button;

void MenuState::StateEnter()
{
	aie::Texture* buttonTexture = new aie::Texture("../bin/textures/ship.png");

	/*button = new Button(glm::vec2(50, 50), glm::vec2(50, 50), buttonTexture);
	m_buttonManager = new ButtonManager(m_renderer, m_input);
	m_buttonManager->SpawnButton(button);*/
}

void MenuState::StateUpdate(float _dt)
{
	if (m_input->isKeyDown(aie::INPUT_KEY_SPACE))
		m_gameStateManager->SetNextState(new PlayState(m_gameStateManager, m_renderer, m_physicsScene));

	//m_buttonManager->Update();
}

void MenuState::StateDraw()
{

	aie::Gizmos::add2DCircle(glm::vec2(0), 5, 12, glm::vec4(0, 1, 0, 1));
	//m_buttonManager->Draw();
}

void MenuState::StateExit()
{
}
