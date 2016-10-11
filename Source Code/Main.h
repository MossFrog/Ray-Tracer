#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <math.h>


//-- Structures --//

struct point
{
	double xPos;
	double yPos;
	double zPos;
};

struct sphere
{
	double radius;
	double xPos;
	double yPos;
	double zPos;
	sf::Color color;
};

struct light
{
	double xPos;
	double yPos;
	double zPos;
	int brightness;
};

struct polygon
{
	point p1;
	point p2;
	point p3;
};

//-- Constant Values --//
double maxDistance = INT_MAX;
double planeZ = 600;
double ambientLight = 0.2;
