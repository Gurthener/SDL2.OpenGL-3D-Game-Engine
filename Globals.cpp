#pragma once
#include "Globals.h"

std::vector<glm::vec3> landLines;

float g_fov = 60;
SDL_Window* gameWindow; // задаем окно для SDL
const int width = 1600; // ширина окна
const int height = 900; // высота окна
bool firing = false;

const int cubeVertices[] = {0,1,3,2,
							0,2,6,4,
							0,4,5,1,
							4,6,7,5,
							2,3,7,6,
		                    7,3,1,5};


std::bitset<STATE_COUNT> state;

const float SPEED = 6.0f;
bool running = true;

std::vector<mesh> meshList;
std::vector<mesh> cubesArray;

std::list<rainCircle> rainCircleList;
std::vector<star> starList;
std::vector<glm::vec3> landscapeVertices;
std::vector<unsigned short> landscapeLines;