#include "Entity.h"

std::list<Entity> predators;
std::list<Entity> preys;
std::list<Entity> blues;

Entity::Entity(glm::vec3 p, glm::vec3 v, float mS, bool dead) : pos(p), maxSpeed(mS), dead(dead), vel(v), acc {0,0,0}, speed(0) {
}

void entityPreyMoving() {
	auto oldTime = SDL_GetTicks();
	auto currentTime = oldTime;

	while (running) {
		currentTime = SDL_GetTicks();
		auto timeElapsed = (currentTime - oldTime) / 1000.0f;
		oldTime = currentTime;
		for (auto& object : preys) {
			object.pos += object.vel * timeElapsed;
			object.vel += object.acc * timeElapsed;

			float minimalDistance;
			bool first = true;
			glm::vec3 targetSubject;
			for (auto const& subject : predators) {
				glm::vec3 relativeVector(subject.pos - object.pos);
				float distanceBetween = glm::length(relativeVector);
				if (first) {
					first = false;
					minimalDistance = distanceBetween;
					targetSubject = std::move(relativeVector);
				} else if (distanceBetween < minimalDistance) {
					minimalDistance = distanceBetween;
					targetSubject = std::move(relativeVector);
				}
			}
			object.acc = std::move(targetSubject);
		}
		SDL_Delay(10);
	}
	return;
}

void entityPredMoving() {
	auto oldTime = SDL_GetTicks();
	auto currentTime = oldTime;

	while (running) {
		currentTime = SDL_GetTicks();
		auto timeElapsed = (currentTime - oldTime) / 1000.0f;
		oldTime = currentTime;

		for (auto& prey : predators) {
			prey.pos += prey.vel * timeElapsed;
			prey.vel += prey.acc * timeElapsed;

			float minDist;
			bool first = true;
			glm::vec3 relPrey;
			for (auto const& pred : blues) {
				glm::vec3 rel(pred.pos - prey.pos);
				float dist = glm::length(rel);
				if (first) {
					first = false;
					minDist = dist;
					//prey.targetId = pred.id;
					relPrey = std::move(rel);
				} else if (dist < minDist) {
					minDist = dist;
					//prey.targetId = pred.id;
					relPrey = std::move(rel);
				}
			}
			prey.acc = std::move(relPrey);
		}
		SDL_Delay(10);
	}
	return;
}

void entityBlueMoving() {
	auto oldTime = SDL_GetTicks();
	auto currentTime = oldTime;

	while (running) {
		[[likely]]
		currentTime = SDL_GetTicks();
		auto timeElapsed = (currentTime - oldTime) / 1000.0f;
		oldTime = currentTime;

		for (auto& prey : blues) {
			prey.pos += prey.vel * timeElapsed;
			prey.vel += prey.acc * timeElapsed;

			float minDist;
			bool first = true;
			glm::vec3 relPrey;
			for (auto const& pred : preys) {
				glm::vec3 rel(pred.pos - prey.pos);
				float dist = glm::length(rel);
				if (first) {
					first = false;
					minDist = dist;
					//prey.targetId = pred.id;
					relPrey = std::move(rel);
				} else if (dist < minDist) {
					minDist = dist;
					//prey.targetId = pred.id;
					relPrey = std::move(rel);
				}
			}
			prey.acc = std::move(relPrey);
		}
		SDL_Delay(10);
	}
	return;
}