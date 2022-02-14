#pragma once
#include <vector>
#include <list>
#include <bitset>

#include <SDL.h>
#include <glm.hpp>

extern const int width; // ширина окна
extern const int height; // высота окна
extern const int cubeVertices[];
extern const float SPEED;
constexpr auto PI = 3.14159265f;

extern bool running;
extern float g_fov;
extern SDL_Window* gameWindow; // задаем окно для SDL
extern bool firing;

enum states {
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	BOOST,
	CLEAR,
	PAUSE,
	FOV_PLUS,
	FOV_MINUS,
	LIFE_EVOLVE,
	STATE_COUNT
};

struct star {
	glm::vec3 pos;
	glm::vec4 color;

	star(glm::vec3 p, glm::vec4 c) : pos(p), color(c) {}
};

struct mesh {
	std::vector<glm::vec3> vertices;
	std::vector<int> lines;
	glm::vec4 color;
};

struct rainCircle {
	mesh circle;
	glm::vec3 origin;
	float velocity;
	long spawnTime;
	long lifeTime;
};


extern std::bitset<STATE_COUNT> state;
extern std::vector<glm::vec3> landLines;
extern std::vector<mesh> meshList;
extern std::list<rainCircle> rainCircleList;
extern std::vector<mesh> cubesArray;
extern std::vector<star> starList;
extern std::vector<glm::vec3> landscapeVertices;
extern std::vector<unsigned short> landscapeLines;