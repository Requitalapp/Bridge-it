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

		/*struct possibleMove
		{
			int x=-5, y=-5;
		};*/

		void initGridPieces();

		void checkAndPlacePiece();

		int getPathLength(int player);

		void deleteIntArray(int **array);

		void getPossibleMoves(std::vector <std::vector<int> >& possibleMoves, int x, int y, int player);

		double rating(int r, int c, int stone, int coef);

		int minimax(int player, int depth , int alpha, int beta);

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