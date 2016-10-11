#include "Main.h"

using namespace std;

//-- Sphere Collision Checking Method --//
bool spCollisionCheck(sphere & subject, point & p1, point & p2);

//-- Sphere Intersection Point Method --//
point spCloseIntersect(sphere & subject, point & p1, point & p2);

//-- Distance Calculation between two point p1 and p2 --//
long double delta(point & p1, point & p2);

//-- Line Segment Sphere Collision Calculation --//
bool spSegmentCheck(sphere & subject, point & p1, point & p2);

int main()
{
	cout << "This is a simple ray tracer program created for the Computer Graphics course at Sabanci University." << endl;

	sf::RenderWindow mainWindow(sf::VideoMode(600, 600), "Ray - Tracer Version 0.4");

	//-- Canvas and Temporary row Definition --//
	vector<vector<sf::RectangleShape>> viewCanvas;
	vector<sf::RectangleShape> tempRow;

	//-- Dummy pixel data --//
	sf::RectangleShape blackPixel;
	blackPixel.setSize(sf::Vector2f(1, 1));
	blackPixel.setFillColor(sf::Color::Black);


	//-- Focal Point definition --//
	point focalPoint;
	focalPoint.xPos = 300.500;
	focalPoint.yPos = 300.500;
	focalPoint.zPos = 0;

	//-- 3-D World Definitions --//

	vector<sphere> spheresVect;


	sphere tempSphere;
	tempSphere.xPos = 100;
	tempSphere.yPos = 200;
	tempSphere.zPos = 700;
	tempSphere.radius = 20;
	tempSphere.color = sf::Color(55, 0, 55);
	spheresVect.push_back(tempSphere);


	tempSphere.xPos = 200;
	tempSphere.yPos = 300;
	tempSphere.zPos = 1000;
	tempSphere.radius = 200;
	tempSphere.color = sf::Color(0, 55, 0);
	spheresVect.push_back(tempSphere);

	tempSphere.xPos = 300;
	tempSphere.yPos = 1300;
	tempSphere.zPos = 1000;
	tempSphere.radius = 800;
	tempSphere.color = sf::Color(0, 0, 55);
	spheresVect.push_back(tempSphere);

	light mainIllum;
	mainIllum.xPos = 0;
	mainIllum.yPos = 300;
	mainIllum.zPos = 600;
	mainIllum.brightness = 0.3;

	//---------------------------//

	sf::Clock testCLK;
	testCLK.restart();

	//-- Perform the Ray tracing operation updating the user of the execution progress --//
	for (int i = 0; i < 600.0; i++)
	{
		for (int j = 0; j < 600.0; j++)
		{
			blackPixel.setPosition(j, i);

			//-- Determine the ray's starting point --//
			point rayPoint;
			rayPoint.xPos = j + .5;
			rayPoint.yPos = i + .5;
			rayPoint.zPos = planeZ;

			//-- Convert the ray into a unit vector --//
			long double deltaRay = delta(rayPoint, focalPoint);

			long double deltaX = rayPoint.xPos - focalPoint.xPos;
			long double deltaY = rayPoint.yPos - focalPoint.yPos;
			long double deltaZ = rayPoint.zPos - focalPoint.zPos;


			//-- Normalize the rays to obtain accurate and non distorted projections --//
			rayPoint.xPos = focalPoint.xPos + deltaX / deltaRay;
			rayPoint.yPos = focalPoint.yPos + deltaY / deltaRay;
			rayPoint.zPos = focalPoint.zPos + deltaZ / deltaRay;

			//-- foremostVal is used for depth calculations --//
			double foremostVal = 10000;

			//-- Calculate if the ray collides with any of the objects --//
			//-- We check all the possible object matrices--//
			//-- The Focal Point is constant --//

			for (int i = 0; i < spheresVect.size(); i++)
			{
				if (spCollisionCheck(spheresVect[i], focalPoint, rayPoint))
				{

					//-- LAMBERTIAN SHADING SECTION --//
					//-- Get the closest point of collision with the ray --//
					point collisionPnt = spCloseIntersect(spheresVect[i], focalPoint, rayPoint);
					if (collisionPnt.zPos < foremostVal)
					{
						foremostVal = collisionPnt.zPos;

						bool obscured = false;
						point lightPos;
						lightPos.xPos = mainIllum.xPos;
						lightPos.yPos = mainIllum.yPos;
						lightPos.zPos = mainIllum.zPos;

						//-- Check if the light ray is obscured --//
						for (int k = 0; k < spheresVect.size(); k++)
						{
							if (spSegmentCheck(spheresVect[k], lightPos, collisionPnt) == true)
							{
								if (i != k)
								{
									//obscured = true;
								}
							}
						}


						//-- Convert the point of collision into a normal vector --//
						point normalVector;
						normalVector.xPos = spheresVect[i].xPos;
						normalVector.yPos = spheresVect[i].yPos;
						normalVector.zPos = spheresVect[i].zPos;

						//-- Convert into a unit vector --//
						//-- Although we express this vector as a point in reality it is a vector extending from the origin --//
						double deltaNormal = delta(collisionPnt, normalVector);

						normalVector.xPos = (collisionPnt.xPos - spheresVect[i].xPos) / deltaNormal;
						normalVector.yPos = (collisionPnt.yPos - spheresVect[i].yPos) / deltaNormal;
						normalVector.zPos = (collisionPnt.zPos - spheresVect[i].zPos) / deltaNormal;

						//-- Calculate a similar light vector that extends from the collision point to the directional light source --//
						point lightVector;
						lightVector.xPos = mainIllum.xPos;
						lightVector.yPos = mainIllum.yPos;
						lightVector.zPos = mainIllum.zPos;

						double deltaLight = delta(collisionPnt, lightVector);

						lightVector.xPos = (collisionPnt.xPos - mainIllum.xPos) / deltaLight;
						lightVector.yPos = (collisionPnt.yPos - mainIllum.yPos) / deltaLight;
						lightVector.zPos = (collisionPnt.zPos - mainIllum.zPos) / deltaLight;


						//-- Calculate the dot product of the normal vector with the vector from the collision point to the light source --//

						double dotProduct = lightVector.xPos * normalVector.xPos + lightVector.yPos * normalVector.yPos + lightVector.zPos * normalVector.zPos;
						dotProduct = -dotProduct;

						if (obscured)
						{
							blackPixel.setFillColor(sf::Color(0, 0, 0) + spheresVect[i].color);
						}

						//-- Shade if less than or equal to zero --//
						else if (dotProduct <= 0)
						{
							blackPixel.setFillColor(sf::Color(0, 0, 0) + spheresVect[i].color);
						}

						else
						{
							blackPixel.setFillColor(sf::Color(200 * dotProduct, 200 * dotProduct, 200 * dotProduct) + spheresVect[i].color);
						}

						//------------------------------------//
					}

					else
					{

					}
				}
			}

			tempRow.push_back(blackPixel);

			//-- Reset the black Pixel --//
			blackPixel.setFillColor(sf::Color::Black);
		}

		viewCanvas.push_back(tempRow);
		tempRow.clear();
	}


	//-- Update the user on the time taken to process the image --//
	cout << "Ray Tracing Operation Completed in " << testCLK.getElapsedTime().asSeconds() << "Seconds." << endl;

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

bool spCollisionCheck(sphere & subject, point & p1, point & p2)
{
	long double resVal;

	//-- Collision Checking depends on the three main components alpha beta and gamma (a, b, g) --//
	//-- The formula is (b * b - 4 * a * g) --//
	//-- Resource : http://paulbourke.net/geometry/circlesphere/index.html#linesphere --//

	long double a = pow((p2.xPos - p1.xPos), 2) + pow((p2.yPos - p1.yPos), 2) + pow((p2.zPos - p1.zPos), 2);

	long double b = 2 * ((p2.xPos - p1.xPos) * (p1.xPos - subject.xPos) + (p2.yPos - p1.yPos) * (p1.yPos - subject.yPos) + (p2.zPos - p1.zPos) * (p1.zPos - subject.zPos));

	long double g = pow(subject.xPos, 2) + pow(subject.yPos, 2) + pow(subject.zPos, 2);

	g += pow(p2.xPos, 2) + pow(p2.yPos, 2) + pow(p2.zPos, 2);

	g -= 2 * (subject.xPos * p2.xPos + subject.yPos * p2.yPos + subject.zPos * p2.zPos);

	g -= subject.radius * subject.radius;

	//-- Result Calculation --//

	resVal = b * b - 4 * a * g;

	//-- Two Collision Points --//
	if (resVal > 0.0)
	{
		return true;
	}

	//-- Single Collision Point --//
	else if (resVal == 0.0)
	{
		return true;
	}

	//-- No Collision --//
	else
	{
		return false;
	}
}

point spCloseIntersect(sphere & subject, point & p1, point & p2)
{
	//-- Resulting intersection Points --//
	point isPoint1;
	point isPoint2;

	//-- After Calculating the below main components we can use the 3-D Quadratic equation to discover the points if there are any (This Checking has to be done prior or else the value is imaginary) --//
	double a = pow((p2.xPos - p1.xPos), 2) + pow((p2.yPos - p1.yPos), 2) + pow((p2.zPos - p1.zPos), 2);

	double b = 2 * ((p2.xPos - p1.xPos) * (p1.xPos - subject.xPos) + (p2.yPos - p1.yPos) * (p1.yPos - subject.yPos) + (p2.zPos - p1.zPos) * (p1.zPos - subject.zPos));

	double g = pow(subject.xPos, 2) + pow(subject.yPos, 2) + pow(subject.zPos, 2);

	g += pow(p2.xPos, 2) + pow(p2.yPos, 2) + pow(p2.zPos, 2);

	g -= 2 * (subject.xPos * p2.xPos + subject.yPos * p2.yPos + subject.zPos * p2.zPos);

	g -= subject.radius * subject.radius;

	//-- The formula is (-b +- sqrt(b^2 - 4(a.g)) / 2a --//

	double component = (-b + sqrt(pow(b, 2) - 4 * a * g)) / (2 * a);

	isPoint1.xPos = p1.xPos + component*(p2.xPos - p1.xPos);
	isPoint1.yPos = p1.yPos + component*(p2.yPos - p1.yPos);
	isPoint1.zPos = p1.zPos + component*(p2.zPos - p1.zPos);

	component = (-b - sqrt(pow(b, 2) - 4 * a*g)) / (2 * a);

	isPoint2.xPos = p1.xPos + component*(p2.xPos - p1.xPos);
	isPoint2.yPos = p1.yPos + component*(p2.yPos - p1.yPos);
	isPoint2.zPos = p1.zPos + component*(p2.zPos - p1.zPos);

	//-- Check which of the points is closer to the focal-point --//
	double deltax = isPoint1.xPos - p1.xPos;
	double deltay = isPoint1.yPos - p1.yPos;
	double deltaz = isPoint1.zPos - p1.zPos;

	double delta1 = sqrt(pow(deltax, 2) + pow(deltay, 2) + pow(deltaz, 2));

	deltax = isPoint2.xPos - p1.xPos;
	deltay = isPoint2.yPos - p1.yPos;
	deltaz = isPoint2.zPos - p1.zPos;


	double delta2 = sqrt(pow(deltax, 2) + pow(deltay, 2) + pow(deltaz, 2));

	//-- Return the closest intersection point --//
	if (delta1 > delta2)
	{
		return isPoint2;
	}

	else
	{
		return isPoint1;
	}
}

long double delta(point & p1, point & p2)
{
	long double deltax = p1.xPos - p2.xPos;
	long double deltay = p1.yPos - p2.yPos;
	long double deltaz = p1.zPos - p2.zPos;

	long double deltaVal = sqrt(pow(deltax, 2) + pow(deltay, 2) + pow(deltaz, 2));

	return deltaVal;
}


bool spSegmentCheck(sphere & subject, point & p1, point & p2)
{
	double x1 = p1.xPos;
	double x2 = p2.xPos;
	double x3 = subject.xPos;

	double y1 = p1.yPos;
	double y2 = p2.yPos;
	double y3 = subject.yPos;

	double z1 = p1.zPos;
	double z2 = p2.zPos;
	double z3 = subject.zPos;

	double top = (x3 - x1)*(x2 - x1) + (y3 - y1)*(y2 - y1) + (z3 - z1)*(z2 - z1);
	double bottom = pow((x2 - x1), 2) + pow((y2 - y1), 2) + pow((z2 - z1), 2);

	double result = top / bottom;

	if (result <= 1 && result >= 0)
	{
		return true;
	}

	else
	{
		return false;
	}
}