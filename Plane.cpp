#include "Plane.h"

Plane::Plane(float const& x1, float const& y1, float const& z1,
			 float const& x2, float const& y2, float const& z2,
			 float const& x3, float const& y3, float const& z3) {
	float const
		a1 = x2 - x1,
		b1 = y2 - y1,
		c1 = z2 - z1,
		a2 = x3 - x1,
		b2 = y3 - y1,
		c2 = z3 - z1;

	a = b1 * c2 - b2 * c1;
	b = a2 * c1 - a1 * c2;
	c = a1 * b2 - b1 * a2;
	d = -a * x1 - b * y1 - c * z1;
}

Plane::Plane(glm::vec3 const& A,
			 glm::vec3 const& B,
			 glm::vec3 const& C) : Plane(A.x, A.y, A.z,
										 B.x, B.y, B.z,
										 C.x, C.y, C.z) {}

float Plane::checkRelativity(glm::vec3 const& point) {
	return a * point.x + b * point.y + c * point.z + d;
}

