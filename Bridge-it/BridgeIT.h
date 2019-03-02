//#ifndef _BRIDGE_H_
//#define _BRIDGE_H_
//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/System.hpp>
////sf::Sprite sprite;
//
//class BridgeIT
//{
//	sf::RenderWindow window;
//	sf::Event event;
//	void initialize_drawings();
//	int offset;
//	int radius;
//	/*sf::Image Lines[2];
//	sf::Image Background;
//	sf::Image iButton;
//	sf::Sprite button;
//*/
//public:
//	BridgeIT();
//	void loop();
//	void changeState(GameState* newState);
//	void close();
//	//sf::RenderWindow gameWindow;
//	//void сreate_window();
//	void draw_field();
//	sf::CircleShape redShapes[6][5];
//	sf::CircleShape blueShapes[5][6];
//};
//
//
//class GameState 
//{
//
//public:
//	GameState(BridgeIT* game);
//	virtual void init()=0;
//	virtual void cleanup()=0;
//	virtual ~GameState() {}
//
//	// чистые виртуальные методы состояния
//	virtual void handleInput(sf::Event& event)=0;
//	virtual void update(float time)=0;
//	virtual void draw(sf::RenderTarget& window)=0;
//
//protected:
//	BridgeIT* game;
//};
//
//#endif
