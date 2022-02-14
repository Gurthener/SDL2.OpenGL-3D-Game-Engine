#include "Projectile.h"

std::list<BallisticProjectile> BallisticProjectile::projectileList;

BallisticProjectile::BallisticProjectile() : pos(0), vel0(0), acc(0), time0(0), aliveTill(0), fragmentations(0), pos0(0) {};

BallisticProjectile::BallisticProjectile(glm::vec3 p,
										 glm::vec3 v0,
										 uint32_t spawn,
										 uint32_t deathTime,
										 uint32_t frags) :
	pos(p), vel0(v0), acc({0,9.8,0}), time0(spawn), aliveTill(deathTime), fragmentations(frags), pos0(p) {}

glm::vec3 BallisticProjectile::getPos0() {
	return pos0;
}

BallisticProjectile& BallisticProjectile::setPos0(glm::vec3 p0) {
	pos0 = p0;
	return *this;
}

glm::vec3 BallisticProjectile::getVel0() {
	return vel0;
}

BallisticProjectile& BallisticProjectile::setVel0(glm::vec3 v0) {
	vel0 = v0;
	return *this;
}

glm::vec3 BallisticProjectile::getPos() {
	return pos;
}

BallisticProjectile& BallisticProjectile::setPos(glm::vec3 p) {
	pos = p;
	return *this;
}

glm::vec3 BallisticProjectile::getAcc() {
	return acc;
}

BallisticProjectile& BallisticProjectile::setAcc(glm::vec3 a) {
	acc = a;
	return *this;
}

uint32_t BallisticProjectile::getTime0() {
	return time0;
}

BallisticProjectile& BallisticProjectile::setTime0(uint32_t t0) {
	time0 = t0;
	return *this;
}

uint32_t BallisticProjectile::getAliveTill() {
	return aliveTill;
}

BallisticProjectile& BallisticProjectile::setAliveTill(uint32_t at) {
	aliveTill = at;
	return *this;
}

uint32_t BallisticProjectile::getFragmentations() {
	return fragmentations;
}

BallisticProjectile& BallisticProjectile::setfragmentations(uint32_t f) {
	fragmentations = f;
	return *this;
}

void BallisticProjectile::addToList(glm::vec3 position0, glm::vec3 vel0, glm::vec3 direction, float velocity, uint32_t time0, uint32_t timeout, uint32_t frags) {
	projectileList.push_back(BallisticProjectile(position0,
												 direction * velocity + vel0,
												 time0,
												 timeout + time0,
												 frags));
}

void BallisticProjectile::projectilePhysics() {
	uint32_t oldTime = SDL_GetTicks();
	auto currentTime = oldTime;

	while (true) {
		currentTime = SDL_GetTicks();
		for (auto itProjectile = projectileList.begin(); itProjectile != projectileList.end(); ++itProjectile) {
			if (currentTime >= itProjectile->aliveTill) {
				if (itProjectile->fragmentations) {
					for (int i = 0; i < itProjectile->fragmentations; ++i) {
						//случайная точка на сфере
						glm::vec3 directionVector(randRange(-1, 1), randRange(-1, 1), randRange(-1, 1));
						if (glm::length(directionVector) > 1) {
							--i;
							continue;
						}
						normalizeVector(directionVector, directionVector);

						auto currentVelocity = itProjectile->vel0;
						currentVelocity.y = itProjectile->vel0.y + GRAVITY * (currentTime - itProjectile->time0) / 1000;
						addToList(itProjectile->pos, currentVelocity, directionVector, 30, currentTime, 100000, 0);
					}
				}
				//удаление исчезнувших снарядов
				itProjectile = projectileList.erase(itProjectile);
				if (itProjectile == projectileList.end())
					break;
			}

			//текущая позиция по корректной баллистике
			float timeAlive = (currentTime - itProjectile->time0) / 1000.f;
			itProjectile->pos = itProjectile->vel0 * timeAlive + itProjectile->pos0
				+ std::move(glm::vec3(0, GRAVITY * timeAlive * timeAlive / 2, 0));

			//рассчёт отскока от "земли" 
			if (itProjectile->pos.y <= 0) {
				ResultQuadraticEquation calculatedTimeVariants = solveQuadraticEquation(GRAVITY / 2,
																						itProjectile->vel0.y,
																						itProjectile->pos0.y);
				float timeToCollision = 0;
				if (calculatedTimeVariants.numOfRoots == 2) {
					if (calculatedTimeVariants.firstRoot > calculatedTimeVariants.secondRoot)
						timeToCollision = calculatedTimeVariants.firstRoot;
					else
						timeToCollision = calculatedTimeVariants.secondRoot;
				} else if (calculatedTimeVariants.numOfRoots == 1) {
					timeToCollision = calculatedTimeVariants.firstRoot;
				}

				itProjectile->vel0.y = abs(itProjectile->vel0.y + GRAVITY * timeToCollision);

				itProjectile->pos0.x += itProjectile->vel0.x * timeToCollision;
				itProjectile->pos0.z += itProjectile->vel0.z * timeToCollision;
				itProjectile->pos0.y = 0;

				itProjectile->time0 += timeToCollision * 1000.f;

				timeAlive = (currentTime - itProjectile->time0) / 1000.0f;
				itProjectile->pos = itProjectile->vel0 * timeAlive + itProjectile->pos0 +
					std::move(glm::vec3(0, GRAVITY * timeAlive * timeAlive / 2, 0));
			}

		}
	//SDL_Delay(10);
	}
	return;
}

