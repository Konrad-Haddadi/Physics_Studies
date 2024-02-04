#include "PlayState.h"
#include "Gizmos.h"
#include <glm/glm.hpp>
#include "GameStateManager.h"
#include "MenuState.h"

void PlayState::StateEnter()
{

}

void PlayState::StateUpdate()
{
	if (m_input->isKeyDown(aie::INPUT_KEY_BACKSPACE))
		gameStateManager->SetNextState(new MenuState(gameStateManager));
}

void PlayState::StateDraw()
{
	aie::Gizmos::add2DCircle(glm::vec2(0), 5, 12, glm::vec4(1, 0, 0, 1));
	

}

void PlayState::StateExit()
{

}
