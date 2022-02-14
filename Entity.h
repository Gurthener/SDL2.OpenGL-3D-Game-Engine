#pragma once
#include <list>

#include <SDL.h>
#include <glm.hpp>

#include "Globals.h"

struct Entity {
	glm::vec3 pos;
	glm::vec3 vel;
	glm::vec3 acc;
	bool dead;
	float speed;
	const float maxSpeed;

	Entity(glm::vec3 p, glm::vec3 v, float mS, bool dead);
};

extern std::list<Entity> predators;
extern std::list<Entity> preys;
extern std::list<Entity> blues;

void entityPreyMoving();

void entityPredMoving();

void entityBlueMoving();
