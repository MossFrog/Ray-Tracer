#include "Main.h"

using namespace std;

int main()
{
	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Ray - Tracer Version 1.0");

	cout << "This is a simple ray tracer program created for the Computer Graphics course at Sabanci University." << endl;

	while (mainWindow.isOpen())
	{
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mainWindow.close();
		}

		mainWindow.clear();
		//mainWindow.draw(shape);
		mainWindow.display();
	}

	return 0;
}