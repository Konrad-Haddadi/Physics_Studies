#include "MenuState.h"
#include "Gizmos.h"
#include "StateManager.h"
#include "PlayState.h"
#include <glm/glm.hpp>

void MenuState::StateEnter(StateManager* _stateManager)
{
	m_input = aie::Input::getInstance();
}

void MenuState::StateUpdate(StateManager* _stateManager)
{
	if (m_input->isKeyDown(aie::INPUT_KEY_SPACE))
		_stateManager->SetNextState(new PlayState);
}

void MenuState::StateDraw(StateManager* _stateManager)
{
	aie::Gizmos::add2DCircle(glm::vec2(0), 5, 12, glm::vec4(0, 1, 0, 1));
}

void MenuState::StateExit(StateManager* _stateManager)
{
}
