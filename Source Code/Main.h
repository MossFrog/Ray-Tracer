#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <vector>
#include <string>


//-- Structures --//

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