#pragma once

#include "SFML/Graphics.hpp"
#include "State.h"
#include "Game.h"

namespace bridgeit
{
	class SplashState : public State
	{
	public:
		SplashState(GameDataRef);

		void init();

		void handleInput();
		void draw(float dt);
		void update(float dt);

	private:
		GameDataRef _data;

		sf::Clock _clock;

		sf::Sprite _background;
	};
}
