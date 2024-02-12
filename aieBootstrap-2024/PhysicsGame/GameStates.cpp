#include "GameStates.h"
#include "GameStateManager.h"

GameStates::GameStates(StateManager* _stateManager, aie::Renderer2D* _renderer, PhysicsScene* _physicsScene)
	: States(_stateManager), m_input(aie::Input::getInstance()), m_renderer(_renderer), m_physicsScene(_physicsScene), m_buttonManager(nullptr)
{
	m_gameStateManager = dynamic_cast<GameStateManager*>(_stateManager);
}