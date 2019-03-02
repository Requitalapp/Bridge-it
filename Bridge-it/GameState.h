#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace bridgeit
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void init();

		void handleInput();
		void update(float dt);
		void draw(float dt);

	private:
		void initGridPieces();

		void checkAndPlacePiece();

		void checkHasPlayerWon(int turn);

		GameDataRef _data;

		sf::Sprite _background;

		sf::Sprite _pauseButton;

		sf::Sprite _gridSprite;

		struct piece
		{
			int value;
			int x, y;
		};

		sf::Sprite _gridPieces[BOARD_SIZE][BOARD_SIZE];
		piece gridArray[BOARD_SIZE][BOARD_SIZE];

		int turn;
		int gameState;
	};
}