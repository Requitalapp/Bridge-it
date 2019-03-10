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
		struct piece
		{
			int value;
			int x, y;
		};

		void initGridPieces();

		void checkAndPlacePiece();

		int checkForWinner(piece grid[BOARD_SIZE][BOARD_SIZE]);

		double rating(int r, int c, int stone, int coef);

		int minimax(piece hypothetical_board[BOARD_SIZE][BOARD_SIZE], int player, bool mymove, int depth);

		GameDataRef _data;

		sf::Sprite _background;

		sf::Sprite _pauseButton;

		sf::Sprite _gridSprite;

		sf::Sprite _gridPieces[BOARD_SIZE][BOARD_SIZE];
		piece gridArray[BOARD_SIZE][BOARD_SIZE];

		int turn;
		int gameState;
		int best_row, best_column;
	};
}