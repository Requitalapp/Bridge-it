//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
//#include <iostream>
//#include "BridgeIt.h"
//using namespace std;
//
//const float OFFSET = 50;
//const float RADIUS = 15;
//const unsigned WINDOW_WIDTH = 800;
//const unsigned WINDOW_HEIGHT = 600;
//
//BridgeIT::BridgeIT()
//{
//	state = new MenuState(this);
//	//initialize_drawings();
//}
//
//BridgeIT::~BridgeIT()
//{
//	delete state;
//}
//
//void BridgeIT::changeState(GameState* newState)
//{
//	delete state;
//	state = newState;
//}
//
//void BridgeIT::close()
//{
//	// закрытие игры
//	window.close();
//}
////void BridgeIT::сreate_window()
////{
////	window.create(sf::VideoMode(1280, 720), "Bridge-IT");
////	window.setFramerateLimit(70);
////}
//
//void BridgeIT::loop()
//{
//	while (window.isOpen())
//	{
//		while (window.pollEvent(event))
//		{
//			// обработка событий
//			state->handleInput(event);
//			switch (event.type)
//			{
//			case sf::Event::Closed:
//				close();
//				return;
//			}
//		}
//		// обновление
//		state->update(elapsed);
//		// отрисовка
//		state->draw(window);
//	}
//}
//void BridgeIT::initialize_drawings()
//{
//	for (int i = 0; i < 6; i++)
//	{
//		for (int j = 0; j < 5; j++)
//		{
//			redShapes[i][j].setRadius(RADIUS);
//			redShapes[i][j].setFillColor(sf::Color::Red);
//			blueShapes[j][i].setRadius(RADIUS);
//			blueShapes[j][i].setFillColor(sf::Color::Blue);
//		}
//	}
//}
//
//
//void BridgeIT::draw_field()
//{
//	sf::Event event;
//	while (window.pollEvent(event))
//	{
//		/*std::cout << sf::Event::Closed << std::endl;
//		cout << (event.type == sf::Event::KeyPressed) << '\n';
//		cout << (event.key.code == sf::Keyboard::Escape) << '\n';
//		getchar();*/
//		if (event.type == sf::Event::Closed)
//		{
//			window.close();
//			return;
//		}
//
//		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
//		{
//			window.close();
//			return;
//		}
//		window.clear();
//		for (int i = 0; i < 5; i++)
//		{
//			for (int j = 0; j < 6; j++)
//			{
//				redShapes[i][j].setPosition(OFFSET + j * OFFSET, 100 + i * OFFSET);
//				window.draw(redShapes[i][j]);
//				/*std::cout << i << ' ' << j;
//				std::getchar();*/
//			}
//		}
//		for (int i = 0; i < 6; i++)
//		{
//			for (int j = 0; j < 5; j++)
//			{
//				blueShapes[j][i].setPosition(OFFSET + 0.5*OFFSET + j * OFFSET, OFFSET + 0.5*OFFSET + i * OFFSET);
//				window.draw(blueShapes[j][i]);
//
//			}
//		}
//		window.display();
//	}
//}
//
////void BridgeIT::draw_field()//!
////{
////	bridgeitWindow.clear(sf::Color(255, 255, 255));
////
////	for (int a = 0; a < 4; a++)
////		for (int b = 0; b < 4; b++)
////			if (HraciaPlocha[a][b].Cislo == 0)
////				;
////
////			else
////			{
////				HraciaPlocha[a][b].Obrazok.SetPosition(a * 50, b * 50 + 21);
////				PuzzleWindow.Draw(HraciaPlocha[a][b].Obrazok);
////			}
////
////	VypisCas();
////	bridgeitWindow.draw(Button);
////
////	PuzzleWindow.Display();
////
////	return;
////}
//
//GameState::GameState(BridgeIT* game)
//{
//	// указатель на игру
//	this->game = game;
//}