#pragma once
#include <random>
#include <glm.hpp>

struct ResultQuadraticEquation {
	unsigned char numOfRoots;
	float firstRoot;
	float secondRoot;
};

struct observer {
	glm::vec3 pos {0,0,0};
	glm::vec3 headForward {0,0,1};
	glm::vec3 headRight {1,0,0};
	glm::vec3 headUp {0,1,0};
	glm::vec3 vel {0,0,0};
};

extern observer camera;
extern float angleX, angleY;
extern glm::mat3x3 rotationMatrix, headRotationMatrix;

template<class T>
struct Addable {
	friend T operator+(T const& a, T const& b) {
		T c(a);
		c += b;
		return c;
	}

	friend T&& operator+(T&& a, T const& b) {
		a += b;
		return std::move(a);
	}

	friend T&& operator+(T const& a, T&& b) {
		b += a;
		return std::move(b);
	}

	friend T&& operator+(T&& a, T&& b) {
		a += b;
		return std::move(a);
	}
};

template<class T>
struct Subabble {
	friend T operator-(T const& a, T const& b) {
		T c(a);
		c -= b;
		return c;
	}

	friend T&& operator-(T&& a, T const& b) {
		a -= b;
		return std::move(a);
	}

	friend T&& operator-(T const& a, T&& b) {
		b -= a;
		return std::move(b);
	}

	friend T&& operator-(T&& a, T&& b) {
		a -= b;
		return std::move(a);
	}
};

ResultQuadraticEquation solveQuadraticEquation(const float& a, const float& b, const float& c);

float randRange(float begin, float end);

void normalizeVector(glm::vec3 const& vec, glm::vec3& resultVec);

glm::vec3 rotateVector(const glm::vec3& vector, const glm::vec3& rotatePoint = camera.pos);

glm::vec3 rotateHead(glm::vec3 vector, glm::vec3 rotatePoint = {0,0,0});

void createRotationMatrix();

void createHeadRotationMatrix();

void updateCameraHeading();
