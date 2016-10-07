#include "Main.h"

using namespace std;

//-- Sphere Collision Checking Method --//
bool spCollisionCheck(sphere & subject, ray & testRay, point & focalPoint);

int main()
{
	cout << "This is a simple ray tracer program created for the Computer Graphics course at Sabanci University." << endl;

	sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Ray - Tracer Version 1.1");

	//-- Canvas and Temporary row Definition --//
	vector<vector<sf::RectangleShape>> viewCanvas;
	vector<sf::RectangleShape> tempRow;

	//-- Dummy pixel data --//
	sf::RectangleShape blackPixel;
	blackPixel.setSize(sf::Vector2f(1, 1));
	blackPixel.setFillColor(sf::Color::Black);

	//-- 3-D World Definitions --//

	vector<sphere> spheresVect;
	
	sphere mainSphere;
	mainSphere.xPos = 0;
	mainSphere.yPos = 0;
	mainSphere.zPos = 150;
	spheresVect.push_back(mainSphere);

	point focalPoint;
	focalPoint.xPos = 400;
	focalPoint.yPos = 300;
	focalPoint.zPos = -400;

	light mainIllum;
	mainIllum.xPos = 0;
	mainIllum.yPos = -300;
	mainIllum.zPos = 0;
	mainIllum.brightness = 0.3;

	int ambientLight = 0.09;

	//---------------------------//

	sf::Clock testCLK;
	testCLK.restart();

	//-- Perform the Ray tracing operation updating the user of the execution progress --//
	for (int i = 0; i < 600; i++)
	{
		for (int j = 0; j < 800; j++)
		{
			blackPixel.setPosition(j, i);

			//-- We inflate newRay to increase the maximum draw distance --//
			ray newRay;
			newRay.xPos = j*maxDistance;
			newRay.yPos = i*maxDistance;
			newRay.zPos = 0*maxDistance;

			//-- Calculate if the ray collides with any of the objects --//
			//-- We check all the possible object matrices--//
			//-- The Focal Point is constant --//

			for (int i = 0; i < spheresVect.size(); i++)
			{
				
			}


			
		




			tempRow.push_back(blackPixel);
		}

		viewCanvas.push_back(tempRow);
		tempRow.clear();
	}

	
	//-- Logical operators and variables --//

	
	cout << "Ray Tracing Operation Completed in " << testCLK.getElapsedTime().asSeconds() << "Seconds." << endl;
	system("PAUSE");

	//-- Framerate Clock --//
	sf::Clock fpsClock;
	fpsClock.restart();

	//-- Main 2-D rendering and Window loop --//
	//-- The 2-D Drawing is done after the Ray-Tracing Operation is complete --//
	while (mainWindow.isOpen())
	{
		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				mainWindow.close();
		}

		mainWindow.clear(sf::Color::White);
		
		
		//-- Draw the most up-to date version of the ray-traced image --//
		for (int i = 0; i < viewCanvas.size(); i++)
		{
			for (int j = 0; j < viewCanvas[0].size(); j++)
			{
				mainWindow.draw(viewCanvas[i][j]);
			}
		}

		cout << "Frame Drawn in " << fpsClock.getElapsedTime().asMilliseconds() << "ms" << endl;
		fpsClock.restart();

		
		mainWindow.display();
	}

	return 0;
}

bool spCollisionCheck(sphere & subject, ray & testRay, point & focalPoint)
{
	double resVal;

	//-- Collision Checking depends on the three main components alpha beta and gamma (a, b, g) --//
	//-- The formula is (b * b - 4 * a * g) --//
	//-- Resource : http://paulbourke.net/geometry/circlesphere/index.html#linesphere --//

	double a = pow((testRay.xPos - focalPoint.xPos), 2) + pow((testRay.yPos - focalPoint.yPos), 2) + pow((testRay.zPos - focalPoint.zPos), 2);
	
	double b = 2 * ((testRay.xPos - focalPoint.xPos) * (focalPoint.xPos - subject.xPos) + (testRay.yPos - focalPoint.yPos) * (focalPoint.yPos - subject.yPos) + (testRay.zPos - focalPoint.zPos) * (focalPoint.zPos - subject.zPos));

	double g = pow(subject.xPos, 2) + pow(subject.yPos, 2) + pow(subject.zPos, 2);

	g += pow(testRay.xPos, 2) + pow(testRay.yPos, 2) + pow(testRay.zPos, 2);

	g -= 2 * (subject.xPos * testRay.xPos + subject.yPos * testRay.yPos + subject.zPos * testRay.zPos);

	g -= pow(subject.radius, 2);

	//-- Result Calculation --//

	resVal = b * b - 4 * a * g;

	//-- Two Collision Points --//
	if (resVal > 0)
	{
		return true;
	}

	//-- Single Collision Point --//
	else if (resVal == 0)
	{
		return true;
	}

	//-- No Collision --//
	else
	{
		return false;
	}


}