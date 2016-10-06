#include "Main.h"

using namespace std;

int main()
{
	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Ray - Tracer Version 1.0");

	//-- Canvas Definition --//
	vector<vector<sf::RectangleShape>> viewCanvas;

	//-- Dummy pixel data --//
	sf::RectangleShape blackPixel;
	blackPixel.setSize(sf::Vector2f(1, 1));
	blackPixel.setFillColor(sf::Color::Black);

	//-- Fill the canvas with black dummy pixels --//
	for (int i = 0; i < 800; i++)
	{
		vector<sf::RectangleShape> tempRow;

		for (int j = 0; j < 600; j++)
		{
			blackPixel.setPosition(i, j);
			tempRow.push_back(blackPixel);
		}

		viewCanvas.push_back(tempRow);
	}

	//-- 3-D World Definitions --//
	
	sphere mainSphere;
	mainSphere.xPos = 0;
	mainSphere.yPos = 0;
	mainSphere.zPos = 150;

	//---------------------------//

	cout << "This is a simple ray tracer program created for the Computer Graphics course at Sabanci University." << endl;



	//-- Render the whole scene and dum the pixel data to a matrix of pixels --//




	//-- Framerate Clock --//
	sf::Clock fpsClock;
	fpsClock.restart();

	//-- Main 2-D rendering and Window loop --//
	//-- This loop runs after the ray tracing operation has been completed --//
	while (mainWindow.isOpen())
	{
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mainWindow.close();
		}




		mainWindow.clear(sf::Color::White);
		
		
		for (int i = 0; i < viewCanvas.size(); i++)
		{
			for (int j = 0; j < viewCanvas[0].size(); j++)
			{
				mainWindow.draw(viewCanvas[i][j]);
			}
		}

		cout << "Render Complete in " << fpsClock.getElapsedTime().asMilliseconds() << "ms" << endl;
		fpsClock.restart();

		
		mainWindow.display();
	}

	return 0;
}