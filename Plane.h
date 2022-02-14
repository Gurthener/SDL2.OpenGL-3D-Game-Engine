#pragma once
#include <glm.hpp>

class Plane {
private:
	float a, b, c, d;

public:
	Plane(float const& x1, float const& y1, float const& z1,
		  float const& x2, float const& y2, float const& z2,
		  float const& x3, float const& y3, float const& z3);

	Plane(glm::vec3 const& A,
		  glm::vec3 const& B,
		  glm::vec3 const& C);

	float checkRelativity(glm::vec3 const& point);
};

