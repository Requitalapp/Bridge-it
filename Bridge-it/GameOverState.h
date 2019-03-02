#pragma once

#include "SFML/Graphics.hpp"
#include "Game.h"
#include "State.h"

namespace bridgeit
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef);

		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);
	private:
		GameDataRef _data;

		sf::Sprite _retryButton;
		sf::Sprite _homeButton;

	};
}