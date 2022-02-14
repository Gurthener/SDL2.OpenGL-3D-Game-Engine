#pragma once
#include <list>
#include <glm.hpp>
#include <SDL.h>

#include "UtilityFunctions.h"

constexpr auto GRAVITY = -9.81f;

class BallisticProjectile {
private:
	glm::vec3 pos0;
	glm::vec3 vel0;
	glm::vec3 pos;
	glm::vec3 acc;
	uint32_t time0;
	uint32_t aliveTill;
	uint32_t fragmentations;

public:
	static std::list<BallisticProjectile> projectileList;

	BallisticProjectile();

	BallisticProjectile(glm::vec3 p,
						glm::vec3 v0,
						uint32_t spawn,
						uint32_t deathTime,
						uint32_t frags);

	glm::vec3 getPos0();
	BallisticProjectile& setPos0(glm::vec3);

	glm::vec3 getVel0();
	BallisticProjectile& setVel0(glm::vec3);

	glm::vec3 getPos();
	BallisticProjectile& setPos(glm::vec3);

	glm::vec3 getAcc();
	BallisticProjectile& setAcc(glm::vec3);

	uint32_t getTime0();
	BallisticProjectile& setTime0(uint32_t);

	uint32_t getAliveTill();
	BallisticProjectile& setAliveTill(uint32_t);

	uint32_t getFragmentations();
	BallisticProjectile& setfragmentations(uint32_t);

	static void addToList(glm::vec3 position0, glm::vec3 vel0, glm::vec3 direction, float velocity, uint32_t time0, uint32_t timeout, uint32_t frags);
	static void projectilePhysics();
};

