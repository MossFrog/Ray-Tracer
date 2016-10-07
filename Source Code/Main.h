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
	int xPos;
	int yPos;
	int zPos;
};

struct sphere
{
	float radius;
	int xPos;
	int yPos;
	int zPos;
};

struct ray
{
	int xPos;
	int yPos;
	int zPos;
	float xAngle;
	float yAngle;
};

struct light
{
	int xPos;
	int yPos;
	int zPos;
	int brightness;
};

//-- Constant Values --//
int maxDistance = 100;