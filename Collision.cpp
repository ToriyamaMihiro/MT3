#include "Collision.h"

bool IsCollisonSS(const Sphere& s1, const Sphere& s2)
{
	Vector3 s3;
	s3 = { (s2.center.x - s1.center.x),(s2.center.y - s1.center.y) ,(s2.center.z - s1.center.z) };
	float distance = Length2(s3);
	if (distance <= s1.radius + s2.radius) {
		return true;
	}
	return false;
}

bool IsCollisionSP(const Sphere& sphere, const Plane& plane)
{
	float k, product;
	product = (plane.normal.x * sphere.center.x + plane.normal.y * sphere.center.y + plane.normal.z * sphere.center.z);
	k = abs(product - plane.distance);
	if (k <= sphere.radius) {
		return true;
	}
	return false;
}
