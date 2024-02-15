#pragma once
#include "GameStates.h"
#include "Texture.h"
#include <vector>
#include <string>
#include <glm/glm.hpp>

class Pig;
class SlingShot;
class StateManager;
class PhysicsScene;

class PlayState : public GameStates
{
public:
	PlayState(StateManager* _stateMachine, aie::Renderer2D* _renderer, PhysicsScene* _physicsScene) 
		: GameStates(_stateMachine, _renderer, _physicsScene) {}
	~PlayState() {}

	void StateEnter() override;
	void StateUpdate(float _dt) override;
	void StateDraw() override;
	void StateExit() override;

	void AngryBirdsControls(aie::Input* _input, float _dt);
	void BuildWorld();
	void LevelBuilder(PhysicsScene* _scene, glm::vec2 _pos, float _spacing, std::vector<std::string>& _strings);
	void LevelSelect(int _level, glm::vec2 _pos);

	void SpawnRandomLevel();
public:
	SlingShot* slingShot;
	std::vector<Pig*> pigs;
	aie::Texture* win;
	bool pull;
};

