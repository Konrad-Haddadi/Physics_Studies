#include "PlayState.h"
#include "Gizmos.h"
#include <glm/glm.hpp>
#include "StateManager.h"
#include "MenuState.h"

void PlayState::StateEnter(StateManager* _stateManager)
{
	m_input = aie::Input::getInstance();
}

void PlayState::StateUpdate(StateManager* _stateManager)
{
	if (m_input->isKeyDown(aie::INPUT_KEY_BACKSPACE))
		_stateManager->SetNextState(new MenuState);
}

void PlayState::StateDraw(StateManager* _stateManager)
{
	aie::Gizmos::add2DCircle(glm::vec2(0), 5, 12, glm::vec4(1, 0, 0, 1));
}

void PlayState::StateExit(StateManager* _stateManager)
{
}
