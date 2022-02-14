#include "LifeCell.h"

map<int8_t, map<int8_t, LifeCell>> LifeCell::cellsMap;
random_device LifeCell::randomDevice;
mt19937_64 LifeCell::mersenneTwister(LifeCell::randomDevice());


LifeCell::LifeCell() : neighbours(0), state(DEAD), stateChanged(NO), neighboursChanged(NO) {}

LifeCell::status LifeCell::getState() {
	return state;
}

LifeCell::boolean LifeCell::getStateChanged() {
	return stateChanged;
}

LifeCell::boolean LifeCell::getNeighboursChanged() {
	return neighboursChanged;
}

uint8_t LifeCell::getNeighbours() {
	return neighbours;
}

LifeCell& LifeCell::addNeighbour() {
	++neighbours;
	return *this;
}

LifeCell& LifeCell::subNeighbour() {
	--neighbours;
	return *this;
}

LifeCell& LifeCell::setNeighbours(uint8_t count) {
	neighbours = count;
	return *this;
}

LifeCell& LifeCell::setState(status st) {
	state = st;
	return *this;
}

LifeCell& LifeCell::setStateChanged(boolean st) {
	stateChanged = st;
	return *this;
}

LifeCell& LifeCell::setNeighboursChanged(boolean st) {
	neighboursChanged = st;
	return *this;
}

LifeCell::status LifeCell::checkSurvival() {
	switch (getNeighbours()) {
	case 2:
		return getState();
	case 3:
		return ALIVE;
	default:
		return DEAD;
	}
}

void LifeCell::addGlider(uint8_t x, uint8_t y) {
	cellsMap[x][y].setState(ALIVE).setStateChanged(YES);
	cellsMap[x][y + 1].setState(ALIVE).setStateChanged(YES);
	cellsMap[x - 1][y].setState(ALIVE).setStateChanged(YES);
	cellsMap[x - 2][y].setState(ALIVE).setStateChanged(YES);
	cellsMap[x - 1][y + 2].setState(ALIVE).setStateChanged(YES);
}

void LifeCell::updateMap() {
	//удаление мертвых клеток
	for (auto& [x, line] : cellsMap) {
		erase_if(line, [](auto& item) {
			auto& [key, value] = item;
			return (!(value.getState() || value.getNeighbours() || value.getNeighboursChanged()));
				 });
	}
   //удаление пустых карт
	erase_if(cellsMap, [](auto& item) {
		return item.second.empty();
			 });
}

void LifeCell::fillMap(int radius, int count) {
	for (int i = 0; i < count; ++i) {
		glm::vec2 cellPosition(uniform_int_distribution(-radius, radius)(mersenneTwister),
							   uniform_int_distribution(-radius, radius)(mersenneTwister));
		if (glm::length(cellPosition) > radius) {
			--i;
			continue;
		}
		//cellsMap[cellPosition.x][cellPosition.y].setState(ALIVE).setStateChanged(YES);

		addGlider(cellPosition.x, cellPosition.y);
	}
}

LifeCell& LifeCell::addOneToNeighbours(int8_t x, int8_t y) {
	const int8_t lx = x - 1, rx = x + 1,
		ly = y - 1, ry = y + 1;

	cellsMap[lx][ly].addNeighbour().setNeighboursChanged(YES);
	cellsMap[lx][y].addNeighbour().setNeighboursChanged(YES);
	cellsMap[lx][ry].addNeighbour().setNeighboursChanged(YES);
	cellsMap[x][ly].addNeighbour().setNeighboursChanged(YES);
	cellsMap[x][ry].addNeighbour().setNeighboursChanged(YES);
	cellsMap[rx][ly].addNeighbour().setNeighboursChanged(YES);
	cellsMap[rx][y].addNeighbour().setNeighboursChanged(YES);
	cellsMap[rx][ry].addNeighbour().setNeighboursChanged(YES);
	setNeighboursChanged(YES);
	return *this;
}

LifeCell& LifeCell::subOneFromNeighbours(int8_t x, int8_t y) {
	const int8_t lx = x - 1, rx = x + 1,
		ly = y - 1, ry = y + 1;

	cellsMap[lx][ly].subNeighbour().setNeighboursChanged(YES);
	cellsMap[lx][y].subNeighbour().setNeighboursChanged(YES);
	cellsMap[lx][ry].subNeighbour().setNeighboursChanged(YES);
	cellsMap[x][ly].subNeighbour().setNeighboursChanged(YES);
	cellsMap[x][ry].subNeighbour().setNeighboursChanged(YES);
	cellsMap[rx][ly].subNeighbour().setNeighboursChanged(YES);
	cellsMap[rx][y].subNeighbour().setNeighboursChanged(YES);
	cellsMap[rx][ry].subNeighbour().setNeighboursChanged(YES);
	setNeighboursChanged(YES);
	return *this;
}



void LifeCell::basicLoop() {
	while (true) {
		fillMap(255, 1);

		for (auto& [x, line] : cellsMap) {
			for (auto& [y, cell] : line) {
				if (cell.getStateChanged()) {
					if (cell.getState())
						cell.addOneToNeighbours(x, y);
					else
						cell.subOneFromNeighbours(x, y);
					cell.setStateChanged(NO);
				}
			}
		}

		updateMap();

		for (auto& [x, line] : cellsMap) {
			for (auto& [y, cell] : line) {
				if (cell.getNeighboursChanged()) {
					if (cell.getState() == cell.checkSurvival()) {
					} else {
						cell.setState(cell.checkSurvival()).setStateChanged(YES);
					}
					cell.setNeighboursChanged(NO);
				}
			}
		}
		SDL_Delay(10);
	}
}