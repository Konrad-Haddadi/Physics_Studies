#include "MenuState.h"
#include "Gizmos.h"
#include "StateManager.h"
#include "PlayState.h"
#include "GameStateManager.h"
#include <glm/glm.hpp>


void MenuState::StateEnter()
{

}

void MenuState::StateUpdate()
{
	if (m_input->isKeyDown(aie::INPUT_KEY_SPACE))
		gameStateManager->SetNextState(new PlayState(gameStateManager));
}

void MenuState::StateDraw()
{
	aie::Gizmos::add2DCircle(glm::vec2(0), 5, 12, glm::vec4(0, 1, 0, 1));

}

void MenuState::StateExit()
{
}
