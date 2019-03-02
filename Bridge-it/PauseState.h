#pragma once

#include "SFML/Graphics.hpp"
#include "Game.h"
#include "State.h"

namespace bridgeit
{
	class PauseState : public State
	{
	public:
		PauseState(GameDataRef);

		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);
	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _resumeButton;
		sf::Sprite _homeButton;
	};
}