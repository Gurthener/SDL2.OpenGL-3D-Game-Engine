#pragma once
/* Попытка создать класс клетки из игры жизнь на основе мапов для возможности использовать бесконечное поле */
#include <map>
#include <random>

#include <glm.hpp>
#include <SDL.h>

using namespace std;

class LifeCell {
private:
	enum status : uint8_t {
		DEAD = 0,
		ALIVE = 1
	};

	enum boolean : uint8_t {
		NO = 0,
		YES = 1
	};

	uint8_t neighbours : 4;
	status state : 1;
	boolean stateChanged : 1;
	boolean neighboursChanged : 1;

public:
	static map<int8_t, map<int8_t, LifeCell>> cellsMap;
	static random_device randomDevice;
	static mt19937_64 mersenneTwister;

	static void updateMap();
	static void fillMap(int radius, int count);
	static void basicLoop();
	static void addGlider(uint8_t x, uint8_t y);

	LifeCell();

	uint8_t getNeighbours();
	LifeCell& addNeighbour();
	LifeCell& subNeighbour();
	LifeCell& setNeighbours(uint8_t count);

	LifeCell& addOneToNeighbours(int8_t x, int8_t y);
	LifeCell& subOneFromNeighbours(int8_t x, int8_t y);

	status getState();
	LifeCell& setState(status state);

	boolean getStateChanged();
	LifeCell& setStateChanged(boolean state);

	boolean getNeighboursChanged();
	LifeCell& setNeighboursChanged(boolean state);

	status checkSurvival();
};
