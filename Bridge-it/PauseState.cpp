#include <sstream>
#include <iostream>

#include "Definitions.h"
#include "PauseState.h"
#include "GameState.h"
#include "MainMenuState.h"

namespace bridgeit
{
	PauseState::PauseState(GameDataRef data) : _data(data)
	{

	}

	void PauseState::init()
	{
		this->_data->assets.loadTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
		this->_data->assets.loadTexture("Resume Button", RESUME_BUTTON);
		this->_data->assets.loadTexture("Home Button", HOME_BUTTON);

		this->_background.setTexture(this->_data->assets.getTexture("Pause Background"));
		this->_resumeButton.setTexture(this->_data->assets.getTexture("Resume Button"));
		this->_homeButton.setTexture(this->_data->assets.getTexture("Home Button"));

		this->_resumeButton.setPosition((this->_data->window.getSize().x / 2) - (this->_resumeButton.getGlobalBounds().width / 2),
			(this->_data->window.getSize().y / 3) - (this->_resumeButton.getGlobalBounds().height / 2));

		this->_homeButton.setPosition((this->_data->window.getSize().x / 2) - (this->_homeButton.getGlobalBounds().width / 2),
			(this->_data->window.getSize().y / 3 * 2) - (this->_homeButton.getGlobalBounds().height / 2));
	}

	void PauseState::handleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}

			if (this->_data->input.isSpriteClicked(this->_resumeButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.removeState();
			}

			if (this->_data->input.isSpriteClicked(this->_homeButton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.removeState();
				this->_data->machine.addState(StateRef(new MainMenuState(_data)), true);
			}
		}
	}

	void PauseState::update(float dt)
	{

	}

	void PauseState::draw(float dt)
	{
		this->_data->window.clear(sf::Color::White);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_resumeButton);
		this->_data->window.draw(this->_homeButton);

		this->_data->window.display();

	}
}