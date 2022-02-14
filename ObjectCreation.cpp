#pragma once
#include "ObjectCreation.h"

void createCube(glm::vec3 mul, glm::vec3 offset, glm::vec4 color) {
	mesh cube;
	for (float i {}; i < 2; i++)
		for (float j {}; j < 2; j++)
			for (float k {}; k < 2; k++)
				cube.vertices.push_back({mul.x * i + offset.x, mul.y * j + offset.y, mul.z * k + offset.z});
	cube.lines = {0,1,5,4,0,2,3,7,6,2,-1,6,4,-1,7,5,-1,3,1};
	cube.color = color;
	cubesArray.push_back(std::move(cube));
}

void createCube(float mul, glm::vec3 offset, glm::vec4 color) {
	createCube({mul,mul,mul}, offset, color);
}

void createCube() {
	createCube(1);
}


void createPoint(glm::vec3 offset, glm::vec4 color) {
	mesh point;
	point.vertices.push_back({offset});
	point.lines = {-1};
	point.color = color;
	meshList.push_back(std::move(point));
}

glm::vec3 attractionPoint(750, 0, 125);

void createHorizon() {
	mesh horizon;
	int line = 0;
	for (float i = 0; i < PI * 2 - PI / 72; i += PI / 36) {
		horizon.vertices.push_back({cos(i) * INT_MAX, 0, sin(i) * INT_MAX});
		horizon.lines.push_back(line++);
	}
	horizon.lines.push_back(0);
	horizon.color = glm::vec4(0.5, 0, 0, 1);
	meshList.push_back(std::move(horizon));
}

void createRainCircle(glm::vec3& o, float v, long s, long l) {
	rainCircle newCircle;

	int line = 0;
	for (float i = 0; i < PI * 2 - PI / 60; i += PI / 30) {
		newCircle.circle.vertices.push_back(
			{
				(float) (o.x + cos(i) * 0.01),
				0,
				(float) (o.z + sin(i) * 0.01)
			}
		);
		newCircle.circle.lines.push_back(line++);
	}
	newCircle.circle.lines.push_back(0);

	newCircle.origin = {o.x, 0, o.z};
	newCircle.velocity = v;
	newCircle.spawnTime = s;
	newCircle.lifeTime = l;
	rainCircleList.push_back(std::move(newCircle));
}


void createLandscape() {
	const int landSize = 100000;
	for (int x = -landSize; x <= landSize; x += 1000) {
		for (int z = -landSize; z <= landSize; z += 1000) {
			landscapeVertices.push_back(glm::vec3(x, randRange(0, glm::length(glm::vec2(x, z)) / 50), z));
		}
	}

	int size = sqrt(landscapeVertices.size());

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			landscapeLines.push_back(j + i * size);
			landscapeLines.push_back(j + 1 + i * size);
		}
	}

	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size; j++) {
			landscapeLines.push_back(j + i * size);
			landscapeLines.push_back(j + size + i * size);
		}
	}
}

