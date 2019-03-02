#pragma once

#include "SFML/Graphics.hpp"
#include "Game.h"
#include "State.h"

namespace bridgeit
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef);

		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);
	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _playButton;

		sf::Sprite _title;
	};
}