#pragma once

#include <memory>
#include <string>

#include "SFML/Graphics.hpp"

#include "AssetManager.h"
#include "InputManager.h"
#include "StateMachine.h"

namespace bridgeit
{
	struct GameData
	{
		StateMachine machine;
		InputManager input;
		AssetManager assets;
		sf::RenderWindow window;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class Game
	{
	public:
		Game(int width, int height, std::string title);
	private:
		const float dt = 1.0f / 60.0f;
		sf::Clock _clock;

		GameDataRef _data = std::make_shared<GameData>();
		void run();
	};
}