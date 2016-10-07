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
};

struct ray
{
	double xPos;
	double yPos;
	double zPos;
};

struct light
{
	int xPos;
	int yPos;
	int zPos;
	int brightness;
};

//-- Constant Values --//
double maxDistance = 1;
double planeZ = 300;