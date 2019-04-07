#include <iostream>
#include <stack>

#include "Definitions.h"
#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"
#define DEBUG

namespace bridgeit
{
	GameState::GameState(GameDataRef data) : _data(data)
	{

	}

	void GameState::init()
	{
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;

		this->_data->assets.loadTexture("Pause Button", PAUSE_BUTTON);
		this->_data->assets.loadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		this->_data->assets.loadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		this->_data->assets.loadTexture("Red Piece", RED_PIECE_FILEPATH);
		this->_data->assets.loadTexture("Blue Piece", BLUE_PIECE_FILEPATH);
		this->_data->assets.loadTexture("Red Piece Vertical", RED_PIECE_VERTICAL_FILEPATH);
		this->_data->assets.loadTexture("Blue Piece Vertical", BLUE_PIECE_VERTICAL_FILEPATH);

		_background.setTexture(this->_data->assets.getTexture("Game Background"));
		_pauseButton.setTexture(this->_data->assets.getTexture("Pause Button"));
		_gridSprite.setTexture(this->_data->assets.getTexture("Grid Sprite"));

		_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getGlobalBounds().width,
			_pauseButton.getPosition().y);
		_gridSprite.setPosition((SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));

		initGridPieces();

		for (int y = 0; y < BOARD_SIZE; y++)
		{
			if (y % 2 == 0)
			{
				for (int x = 0; x < BOARD_SIZE; x++)
				{
					if (x % 2 == 0)
					{
						gridArray[y][x].value = EMPTY_PIECE;
						gridArray[y][x].x = x;
						gridArray[y][x].y = y;
					}
					else
					{
						gridArray[y][x].value = CLOSED_PIECE;
						gridArray[y][x].x = x;
						gridArray[y][x].y = y;
					}
				}
			}
			else
			{
				for (int x = 0; x < BOARD_SIZE; x++)
				{
					if (x % 2 == 0)
					{
						gridArray[y][x].value = CLOSED_PIECE;
						gridArray[y][x].x = x;
						gridArray[y][x].y = y;
					}
					else
					{
						gridArray[y][x].value = EMPTY_PIECE;
						gridArray[y][x].x = x;
						gridArray[y][x].y = y;
					}
				}
			}

		}
	}

	void GameState::handleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (this->_data->input.isSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.addState(StateRef(new PauseState(_data)), false);

			}
			else
			{
				if (gameState == STATE_PLAYING)
				{
					if (turn == PLAYER_PIECE)
					{
						if (this->_data->input.isSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window))
						{
							this->checkAndPlacePiece();
						}
					}
					else
					{
						this->checkAndPlacePiece();
					}
				}
				else
				{
					this->_data->machine.removeState();	//add win/lose states
				}
				/*if (this->_data->input.isSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window))
				{
					if (STATE_PLAYING == gameState)
					{
						this->checkAndPlacePiece();
					}
				}*/
			}
		}
	}

	void GameState::update(float dt)
	{

	}

	void GameState::draw(float dt)
	{
		this->_data->window.clear(sf::Color::White);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_pauseButton);
		this->_data->window.draw(this->_gridSprite);

		for (int y = 0; y < BOARD_SIZE; y++)
		{
			for (int x = 0; x < BOARD_SIZE; x++)
			{
				this->_data->window.draw(this->_gridPieces[y][x]);
			}
		}

		this->_data->window.display();

	}

	void GameState::initGridPieces()
	{
		sf::Vector2u tempSpriteSize = this->_data->assets.getTexture("Red Piece").getSize();

		//Initialization of red pieces
		for (int y = 0; y < BOARD_SIZE; y += 2)
		{
			for (int x = 0; x < BOARD_SIZE; x += 2)
			{
				_gridPieces[y][x].setTexture(this->_data->assets.getTexture("Red Piece"));


				_gridPieces[y][x].setPosition(_gridSprite.getPosition().x + (GRID_OFFSET + CIRCLE_SIZE * (x / 2 + 1) + tempSpriteSize.x*(x / 2)),
					_gridSprite.getPosition().y + (CIRCLE_SIZE * (y / 2 + 1) + tempSpriteSize.y*y / 2) + GRID_OFFSET);

				_gridPieces[y][x].setColor(sf::Color(255, 255, 255, 0));
			}
		}

		//Initialization of blue pieces
		for (int y = 1; y < BOARD_SIZE; y += 2)
		{
			for (int x = 1; x < BOARD_SIZE; x += 2)
			{
				_gridPieces[y][x].setTexture(this->_data->assets.getTexture("Blue Piece"));

				_gridPieces[y][x].setPosition(_gridSprite.getPosition().x + (GRID_OFFSET + CIRCLE_SIZE * (x / 2 + 1) + tempSpriteSize.x * (x / 2) + ROW_OFFSET),
					_gridSprite.getPosition().y + (GRID_OFFSET + CIRCLE_SIZE * (y / 2) + tempSpriteSize.y * y / 2) + SPACE_BETWEEN_ROWS);

				_gridPieces[y][x].setColor(sf::Color(255, 255, 255, 0));

			}
		}
	}

	void GameState::checkAndPlacePiece()
	{
		int row = -1, column = -1;
		
		if (turn==PLAYER_PIECE)
		{
			std::cout << "PLAYER TURN" << std::endl;	//!
			while ((row == -1) && (column == -1))
			{
				for (int y = 0; y < BOARD_SIZE; y++)
				{
					for (int x = 0; x < BOARD_SIZE; x++)
					{
						//std::cout << "mouse pressed" << std::endl;
						if (this->_data->input.isSpriteClicked(_gridPieces[y][x], sf::Mouse::Button::Left, this->_data->window))
						{
							row = y;
							column = x;
						}
					}
				}
			}


			if (gridArray[row][column].value == EMPTY_PIECE)
			{
				gridArray[row][column].value = turn;
			}
			else
			{
				return;
			}


			if (row % 2 == 1)
			{
				_gridPieces[row][column].setTexture(this->_data->assets.getTexture("Red Piece Vertical"));
			}
			else
			{
				_gridPieces[row][column].setTexture(this->_data->assets.getTexture("Red Piece"));
			}
			_gridPieces[row][column].setColor(sf::Color(255, 255, 255, 255));
			gridArray[row][column].value = RED_PIECE;
			if (getPathLength(turn) == 8)
			{
				gameState = STATE_WON;
			}
			std::getchar();	//!
			turn = AI_PIECE;
		}
		else
		{
			std::cout << "AI TURN" << std::endl;	//!
			std::cout << "AI turn before minmax" << std::endl;	//!
			int alpha=-1000, beta=1000;
			int score = minimax(AI_PIECE, 0, alpha, beta);
			std::cout << "Ai turn after minmax";	//!

			if (score != -1000)
			{
				row = best_row;
				column = best_column;
			}

			if (row % 2 == 1)
			{
				_gridPieces[row][column].setTexture(this->_data->assets.getTexture("Blue Piece"));
			}
			else
			{
				_gridPieces[row][column].setTexture(this->_data->assets.getTexture("Blue Piece Vertical"));
			}
			_gridPieces[row][column].setColor(sf::Color(255, 255, 255, 255));
			gridArray[row][column].value = BLUE_PIECE;
			if (getPathLength(turn) == 8)
			{
				gameState = STATE_LOSE;
			}
			turn = PLAYER_PIECE;
		}
#ifdef DEBUG
		for (int y = 0; y < BOARD_SIZE; y++)	//!
		{
			for (int x = 0; x < BOARD_SIZE; x++)
			{
				/*if (gridArray[y][x].value != CLOSED_PIECE)
				{
					std::cout << gridArray[y][x].value << " ";
				}*/
				std::cout << gridArray[y][x].value << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		//std::getchar();
#endif
	}

	void GameState::deleteIntArray(int **arr)
	{
		for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
		{
			delete[] arr[i];
		}
		delete[] arr;
	}

	void GameState::getPossibleMoves(std::vector <std::vector<int> >& possibleMoves, int x, int y , int player)
	{
		
		if (player == PLAYER_PIECE)
		{
			if (x % 2 == 1)
			{
				if (y > 1)
				{
					/*possibleMoves[y - 2][x].x = x;
					possibleMoves[y - 2][x].y = y-2;*/
					possibleMoves[y - 2][x]= CLOSED_PIECE;
				}

				if (y < BOARD_SIZE - 2)
				{
					/*possibleMoves[y + 2][x].x = x;
					possibleMoves[y + 2][x].y = y + 2;*/
					possibleMoves[y + 2][x] = CLOSED_PIECE;
				}
			}

			if (y % 2 == 0 )
			{
				if (x < BOARD_SIZE - 2) 
				{
					/*possibleMoves[y][x + 2].x = x + 2;
					possibleMoves[y][x + 2].y = y;*/
					possibleMoves[y][x + 2] = CLOSED_PIECE;
				}

				if (x > 1)
				{
					/*possibleMoves[y][x - 2].x = x - 2;
					possibleMoves[y][x - 2].y = y;*/
					possibleMoves[y][x - 2] = CLOSED_PIECE;
				}
			}


			if (y < BOARD_SIZE - 1 && x < BOARD_SIZE - 1)
			{
				/*possibleMoves[y + 1][x + 1].x = x + 1;
				possibleMoves[y + 1][x + 1].y = y + 1;*/
				possibleMoves[y + 1][x + 1] = CLOSED_PIECE;
			}

			if (y > 0 && x < BOARD_SIZE - 1)
			{
				/*possibleMoves[y - 1][x + 1].x = x + 1;
				possibleMoves[y - 1][x + 1].y = y - 1;*/
				possibleMoves[y - 1][x + 1] = CLOSED_PIECE;
			}

			if (y > 0 && x > 0)
			{
				/*possibleMoves[y - 1][x + 1].x = x + 1;
				possibleMoves[y - 1][x + 1].y = y - 1;*/
				possibleMoves[y - 1][x - 1] = CLOSED_PIECE;
			}

			if (y < BOARD_SIZE - 1 && x > 0)
			{
				/*possibleMoves[y - 1][x + 1].x = x + 1;
				possibleMoves[y - 1][x + 1].y = y - 1;*/
				possibleMoves[y + 1][x - 1] = CLOSED_PIECE;
			}
		}
		else
		{
			if (y % 2 == 1)
			{
				if (x > 1)
				{
					/*possibleMoves[y][x - 2].x = x - 2;
					possibleMoves[y][x - 2].y = y;*/
					possibleMoves[y][x - 2] = CLOSED_PIECE;
				}

				if (x < BOARD_SIZE - 2)
				{
					/*possibleMoves[y][x + 2].x = x + 2;
					possibleMoves[y][x + 2].y = y;*/
					possibleMoves[y][x + 2] = CLOSED_PIECE;
				}
			}


			if (x % 2 == 0 && y < BOARD_SIZE -2)
			{
				/*possibleMoves[y + 2][x].x = x;
				possibleMoves[y + 2][x].y = y + 2;*/
				possibleMoves[y + 2][x] = CLOSED_PIECE;
			}

			if (y > 1)
			{
				/*possibleMoves[y - 2][x].x = x;
				possibleMoves[y - 2][x].y = y - 2;*/
				possibleMoves[y - 2][x] = CLOSED_PIECE;
			}

			if (x > 0 && y < BOARD_SIZE - 1)
			{
				/*possibleMoves[y + 1][x - 1].x = x - 1;
				possibleMoves[y + 1][x - 1].y = y + 1;*/
				possibleMoves[y + 1][x - 1] = CLOSED_PIECE;
			}

			if (x < BOARD_SIZE - 1 && y < BOARD_SIZE - 1)
			{
				/*possibleMoves[y + 1][x + 1].x = x + 1;
				possibleMoves[y + 1][x + 1].y = y + 1;*/
				possibleMoves[y + 1][x + 1] = CLOSED_PIECE;
			}

			if (x < BOARD_SIZE - 1 && y > 0)
			{
				/*possibleMoves[y + 1][x + 1].x = x + 1;
				possibleMoves[y + 1][x + 1].y = y + 1;*/
				possibleMoves[y - 1][x + 1] = CLOSED_PIECE;
			}

			if (x > 0 && y > 0)
			{
				/*possibleMoves[y + 1][x + 1].x = x + 1;
				possibleMoves[y + 1][x + 1].y = y + 1;*/
				possibleMoves[y - 1][x - 1] = CLOSED_PIECE;
			}
		}
	}
	
	
	int GameState::getPathLength(int player)
	{
		std::vector<std::vector <int>> movesGrid(BOARD_SIZE, std::vector<int>(BOARD_SIZE, EMPTY_PIECE));
		std::stack<piece> stack;

		piece p;

		int pathLength = 0, maxPathLength = 0;
		
		if (player == PLAYER_PIECE)
		{

			for (int y = 0; y < BOARD_SIZE; y++)
			{
				for (int x = y % 2; x < BOARD_SIZE; x += 2)
				{
					if (gridArray[y][x].value == RED_PIECE)
					{
						if (movesGrid[y][x] == EMPTY_PIECE)
						{
							stack.push(gridArray[y][x]);
						}

						getPossibleMoves(movesGrid, x, y, player);
						
					}
				}
			}

			for (int i = 0; i < BOARD_SIZE; i++)
			{
				for (int j = 0; j < BOARD_SIZE; j++)
				{
					movesGrid[i][j] = EMPTY_PIECE;
				}
			}
			int lastY = -1;
			int lastX = -1;
			while (!stack.empty())
			{
				p = stack.top();
				std::cout << "p = " << p.value << std::endl; //!
				std::cout << "p.x = " << p.x <<"p.y = "<< p.y << std::endl; //!
				stack.pop();

				if (pathLength > maxPathLength)
				{
					maxPathLength = pathLength;
				}

				if (gridArray[p.y][p.x].value == RED_PIECE)
				{
					if (movesGrid[p.y][p.x] == EMPTY_PIECE)
					{
						movesGrid[p.y][p.x] = CLOSED_PIECE;



						if (p.y > lastY + 1 || p.y < lastY -1)
						{
							lastX = p.x;
							lastY = p.y;
							pathLength = 0;
						}


						if (p.x > lastX)
						{
							if (lastX == -1)
							{
								pathLength = 0;
							}
							else
							{
								pathLength += p.x - lastX;
							}
							
							lastX = p.x;
							lastY = p.y;
						}

						if (pathLength == BOARD_SIZE - 1)
						{
							return pathLength;
						}

						if (p.x % 2 == 1)
						{
							if (p.y > 1)
							{
								stack.push(gridArray[p.y - 2][p.x]);
							}

							if (p.y < BOARD_SIZE - 2)
							{
								stack.push(gridArray[p.y + 2][p.x]);
							}
						}

						if (p.y % 2 == 0 && p.x < BOARD_SIZE - 2)
						{
							stack.push(gridArray[p.y][p.x + 2]);
						}

						if (p.x > 1)
						{
							stack.push(gridArray[p.y][p.x - 2]);
						}

						if (p.y != BOARD_SIZE - 1 && p.x !=BOARD_SIZE -1)
						{
							stack.push(gridArray[p.y + 1][p.x + 1]);
						}

						if (p.y != 0 && p.x != BOARD_SIZE - 1)
						{
							stack.push(gridArray[p.y - 1][p.x + 1]);
						}

						if (p.y > 0 && p.x > 0)
						{
							stack.push(gridArray[p.y - 1][p.x - 1]);
						}

						if (p.y < BOARD_SIZE - 1 && p.x > 0)
						{
							stack.push(gridArray[p.y + 1][p.x - 1]);
						}
					}
				}
			}
		}

		else
		{
			for (int y = 0; y < BOARD_SIZE; y++)
			{
				for (int x = y % 2; x < BOARD_SIZE; x += 2)
				{
					if (gridArray[y][x].value == BLUE_PIECE)
					{
						if (movesGrid[y][x] == EMPTY_PIECE)
						{
							stack.push(gridArray[y][x]);
						}
						getPossibleMoves(movesGrid, x , y, player);

					}
				}
			}
			for (int i = 0; i < BOARD_SIZE; i++)
			{
				for (int j = 0; j < BOARD_SIZE; j++)
				{
					movesGrid[i][j] = EMPTY_PIECE;
				}
			}

			int lastX = -1;
			int lastY = -1;
				while (!stack.empty())
				{
					p = stack.top();
					std::cout << "p = " << p.value << std::endl; //!
					stack.pop();
					if (pathLength > maxPathLength)
					{
						maxPathLength = pathLength;
					}
					if (gridArray[p.y][p.x].value == BLUE_PIECE)
					{
						if (movesGrid[p.y][p.x] == EMPTY_PIECE)
						{
							movesGrid[p.y][p.x] = CLOSED_PIECE;
							if (p.x > lastX + 1 || p.x < lastX - 1)
							{
								lastX = p.x;
								lastY = p.y;
								pathLength = 0;
								/*for (int i = 0; i < BOARD_SIZE; i++)
								{
									for (int j = 0; j < BOARD_SIZE; j++)
									{
										movesGrid[i][j] = EMPTY_PIECE;
									}
								}

								movesGrid[p.y][p.x] = CLOSED_PIECE;*/

							}
							if (p.y > lastY)
							{
								if (lastY == -1)
								{
									pathLength = 0;
								}
								else
								{
									pathLength += p.y - lastY;
								}

								lastY = p.y;
								lastX = p.x;
							}


							if (pathLength == BOARD_SIZE - 1)
							{
								return pathLength;
							}

							if (p.y % 2 == 1)
							{
								if (p.x > 1)
								{
									stack.push(gridArray[p.y][p.x - 2]);
								}

								if (p.x != BOARD_SIZE - 2)
								{
									stack.push(gridArray[p.y][p.x + 2]);
								}
							}


							if (p.x % 2 == 0 && p.y < BOARD_SIZE -2)
							{
								stack.push(gridArray[p.y + 2][p.x]);
							}

							if (p.y > 1)
							{
								stack.push(gridArray[p.y - 2][p.x]);
							}

							if (p.x != 0 && p.y != BOARD_SIZE -1)
							{
								stack.push(gridArray[p.y + 1][p.x - 1]);
							}

							if (p.x != BOARD_SIZE - 1 && p.y != BOARD_SIZE -1)
							{
								stack.push(gridArray[p.y + 1][p.x + 1]);
							}
						}
					}
				}
			}

			std::cout << "maxPathLength = " << maxPathLength << std::endl;	//!
			return maxPathLength;
		}

	int GameState::minimax(int player, int depth ,int alpha, int beta)  
	{
		int i, j;
#ifdef DEBUG

		for (int y = 0; y < BOARD_SIZE; y++)	//!
		{
			for (int x = 0; x < BOARD_SIZE; x++)
			{
				std::cout << gridArray[y][x].value << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
#endif
		int pathLength = getPathLength(player);
		// if we have gone too deep, return;
		int pathLengthNext = getPathLength(-1*player);
		if (depth == MAX_DEPTH || pathLength == 8)
		{
			return pathLength-pathLengthNext;
		}


		// see if someone has won

		


		int move_row;
		int move_column;

		// For all possible locations (moves),
		for (i = 0; i < BOARD_SIZE; i++) //Change increment
		{
			for (j = i % 2; j < BOARD_SIZE; j+=2) //Change increment
			{
				if (gridArray[i][j].value == EMPTY_PIECE)
				{
					// If this is a legal move,
					gridArray[i][j].value = player; //Try the move
					int thisScore = minimax(-1 * player, depth + 1, alpha, beta)-pathLength;
					gridArray[i][j].value = EMPTY_PIECE;//Reset board after try
					if (player == AI_PIECE)
					{
						// my move, so maximize the score          
						if (thisScore >= alpha) {
							alpha = thisScore;
							move_row = i;
							move_column = j;
						}
					}
					else
					{
						// not my move, so minimize the score
						if (thisScore <= beta) {
							beta = thisScore;
							move_row = i;
							move_column = j;
						}
					}
					if (alpha >= beta)
					{
						break;
					}
				}
			}
		}
		best_row = move_row;
		best_column = move_column;
		if (player == AI_PIECE)
		{
			return alpha;
		}
		else
		{
			return beta;
		}
		//if (move_row == -1) return 0;  // no valid moves, so it is a tie.
		
		//return score;
	}

}





