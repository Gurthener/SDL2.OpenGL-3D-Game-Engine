#include "UtilityFunctions.h"



observer camera;

float angleX, angleY;
glm::mat3x3 rotationMatrix, headRotationMatrix;

ResultQuadraticEquation solveQuadraticEquation(const float& a,
											   const float& b,
											   const float& c) {

	float d = b * b - 4 * a * c;
	if (d > 0) [[likely]] {
		return {2,
			(-b + sqrt(d)) / 2 / a,
			(-b - sqrt(d)) / 2 / a};
	} else if (d == 0) {
		return {1, -b / 2 / a};
	} else {
		return {0};
	}
}

float randRange(float begin, float end) {
	static std::random_device randomDevice;
	static std::mt19937_64 mersenneTwister(randomDevice());
	return std::uniform_real_distribution(begin, end)(mersenneTwister);
}

void normalizeVector(glm::vec3 const& vec, glm::vec3& resultVec) {
	if (glm::length(vec))
		resultVec = glm::normalize(vec);
}

glm::vec3 rotateVector(const glm::vec3& vector, const glm::vec3& rotatePoint) {
	return rotationMatrix * (vector - rotatePoint);
}

glm::vec3 rotateHead(glm::vec3 vector, glm::vec3 rotatePoint) {
	return headRotationMatrix * (vector - rotatePoint);
}



void createRotationMatrix() {
	glm::mat3x3 xMatrix(1, 0, 0,
						0, cos(angleX), -sin(angleX),
						0, sin(angleX), cos(angleX));

	glm::mat3x3 yMatrix(cos(angleY), 0, sin(angleY),
						0, 1, 0,
						-sin(angleY), 0, cos(angleY));

	rotationMatrix = xMatrix * yMatrix;
}

void createHeadRotationMatrix() {


	glm::mat3x3 xMatrix(1, 0, 0,
						0, cos(angleX), -sin(angleX),
						0, sin(angleX), cos(angleX));

	glm::mat3x3 yMatrix(cos(angleY), 0, sin(angleY),
						0, 1, 0,
						-sin(angleY), 0, cos(angleY));

	headRotationMatrix = yMatrix * xMatrix;
}

void updateCameraHeading() {
	camera.headForward = rotateHead({0,0,-1});
	camera.headUp = rotateHead({0,1,0});
	camera.headRight = rotateHead({1,0,0});
}