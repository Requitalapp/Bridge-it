#include <sstream>
#include <iostream>
#include <stack>

#include "Definitions.h"
#include "GameState.h"
#include "PauseState.h"
#include "GameOverState.h"

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
				if (this->_data->input.isSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window))
				{
					if (STATE_PLAYING == gameState)
					{
						this->checkAndPlacePiece();
					}
				}
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
		for (int y = 0; y < BOARD_SIZE; y+=2)
		{
			for (int x = 0; x < BOARD_SIZE; x+=2)
			{
				_gridPieces[y][x].setTexture(this->_data->assets.getTexture("Red Piece"));

				
				_gridPieces[y][x].setPosition(_gridSprite.getPosition().x + (GRID_OFFSET + CIRCLE_SIZE * (x/2+1) + tempSpriteSize.x*(x/2)),
				_gridSprite.getPosition().y + (CIRCLE_SIZE * (y/2 + 1) + tempSpriteSize.y*y/2) + GRID_OFFSET);
							
				_gridPieces[y][x].setColor(sf::Color(255, 255, 255, 0));
			}
		}

		//Initialization of blue pieces
		for (int y = 1; y < BOARD_SIZE; y += 2)
		{
			for (int x = 1; x < BOARD_SIZE; x += 2)
			{
				_gridPieces[y][x].setTexture(this->_data->assets.getTexture("Blue Piece"));

				_gridPieces[y][x].setPosition(_gridSprite.getPosition().x + (GRID_OFFSET + CIRCLE_SIZE * (x/2 + 1) + tempSpriteSize.x * (x/2)+ROW_OFFSET),
					_gridSprite.getPosition().y + (GRID_OFFSET + CIRCLE_SIZE * (y / 2) + tempSpriteSize.y * y / 2)+SPACE_BETWEEN_ROWS);

				_gridPieces[y][x].setColor(sf::Color(255, 255, 255, 0));

			}
		}
	}

	void GameState::checkAndPlacePiece()
	{
		int row=-1, column=-1;

		while ((row == -1) && (column == -1))
		{
			for (int y = 0; y < BOARD_SIZE; y++)
			{
				for (int x = 0; x < BOARD_SIZE; x++)
				{
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

		if (PLAYER_PIECE == turn)
		{
			if (row % 2 == 1)
			{
				_gridPieces[row][column].setTexture(this->_data->assets.getTexture("Red Piece Vertical"));
			}
			else
			{
				_gridPieces[row][column].setTexture(this->_data->assets.getTexture("Red Piece"));
			}
			gridArray[row][column].value = RED_PIECE;
			checkHasPlayerWon(turn);
			turn = AI_PIECE;
		}
		else
		{
			if (row % 2 == 1)
			{
				_gridPieces[row][column].setTexture(this->_data->assets.getTexture("Blue Piece"));
			}
			else
			{
				_gridPieces[row][column].setTexture(this->_data->assets.getTexture("Blue Piece Vertical"));
			}
			gridArray[row][column].value = BLUE_PIECE;
			checkHasPlayerWon(turn);
			turn = PLAYER_PIECE;
		}

		_gridPieces[row][column].setColor(sf::Color(255,255,255,255));

		for (int y=0; y < BOARD_SIZE; y++)	//!
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
	}


	void GameState::checkHasPlayerWon(int turn)
	{
		int **was = new int* [BOARD_SIZE];
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			was[i] = new int[BOARD_SIZE];
		}
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				was[i][j] = EMPTY_PIECE;
			}
		}
		std::stack<piece> stack;

		piece p;

		if (turn == PLAYER_PIECE)
		{
			for (int y = 0; y < BOARD_SIZE; y += 2)
			{
				stack.push(gridArray[y][0]);
			}

			while (!stack.empty())
			{
				p = stack.top();
				std::cout << "p = " << p.value << std::endl;
				stack.pop();
				if (gridArray[p.y][p.x].value == RED_PIECE)
				{
					if (was[p.y][p.x] == EMPTY_PIECE)
					{
						was[p.y][p.x] = CLOSED_PIECE;
						if (p.x == BOARD_SIZE - 1)
						{
							gameState = STATE_WON;
							break;
						}

						if (p.x % 2 == 1)
						{
							if (p.y > 1)
							{
								stack.push(gridArray[p.y - 2][p.x]);
							}

							if (p.y != BOARD_SIZE - 2)
							{
								stack.push(gridArray[p.y + 2][p.x]);
							}
						}

						if (p.y % 2 == 0)
						{
							stack.push(gridArray[p.y][p.x + 2]);
						}

						if (p.x > 1)
						{
							stack.push(gridArray[p.y][p.x - 2]);						
						}

						if (p.y != BOARD_SIZE - 1)
						{
							stack.push(gridArray[p.y + 1][p.x + 1]);
						}

						if (p.y != 0)
						{
							stack.push(gridArray[p.y - 1][p.x + 1]);
						}

						
					}
				}
			}
		}
		else
		{
			for (int x = 0; x < BOARD_SIZE; x += 2)
			{
				stack.push(gridArray[0][x]);
			}

			while (!stack.empty())
			{
				p = stack.top();
				std::cout << "p = " << p.value << std::endl;
				stack.pop();
				if (gridArray[p.y][p.x].value == BLUE_PIECE)
				{
					if (was[p.y][p.x] == EMPTY_PIECE)
					{
						was[p.y][p.x] = CLOSED_PIECE;
						if (p.y == BOARD_SIZE - 1)
						{
							gameState =	STATE_LOSE;
							break;
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


						if (p.x % 2 == 0)
						{
							stack.push(gridArray[p.y + 2][p.x]);
						}
						
						if (p.y > 1)
						{
							stack.push(gridArray[p.y - 2][p.x]);
						}

						if (p.x != 0)
						{
							stack.push(gridArray[p.y + 1][p.x - 1]);
						}

						if (p.x != BOARD_SIZE - 1)
						{
							stack.push(gridArray[p.y + 1][p.x + 1]);
						}

						

					}
				}
			}
		}

		std::cout << gameState << std::endl;	//!
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			delete[] was[i];
		}
		delete[] was;
	}
}


