#include <sstream>
#include <iostream>

#include "Definitions.h"
#include "GameOverState.h"
#include "GameState.h"
#include "MainMenuState.h"

namespace bridgeit
{
	GameOverState::GameOverState(GameDataRef data) : _data(data)
	{

	}

	void GameOverState::init()
	{
		this->_data->assets.loadTexture("Retry Button", RETRY_BUTTON);
		this->_data->assets.loadTexture("Home Button", HOME_BUTTON);
		
		this->_retryButton.setTexture(this->_data->assets.getTexture("Retry Button"));
		this->_homeButton.setTexture(this->_data->assets.getTexture("Home Button"));

		this->_retryButton.setPosition((this->_data->window.getSize().x / 2) - (this->_retryButton.getGlobalBounds().width / 2),
			(this->_data->window.getSize().y / 3) - (this->_retryButton.getGlobalBounds().height / 2));

		this->_homeButton.setPosition((this->_data->window.getSize().x / 2) - (this->_homeButton.getGlobalBounds().width / 2),
			(this->_data->window.getSize().y / 3 * 2) - (this->_homeButton.getGlobalBounds().height / 2));
	}

	void GameOverState::handleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (this->_data->input.isSpriteClicked(this->_retryButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.addState(StateRef(new GameState(_data)), true);
			}

			if (this->_data->input.isSpriteClicked(this->_homeButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.addState(StateRef(new MainMenuState(_data)), true);
			}
		}
	}

	void GameOverState::update(float dt)
	{

	}

	void GameOverState::draw(float dt)
	{
		this->_data->window.clear(sf::Color::White);

		this->_data->window.draw(this->_retryButton);
		this->_data->window.draw(this->_homeButton);

		this->_data->window.display();

	}
}