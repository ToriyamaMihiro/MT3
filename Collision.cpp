#include "Collision.h"

bool IsCollison(const Sphere& s1, const Sphere& s2)
{

	Vector3 s3;
	s3 = { (s2.center.x - s1.center.x),(s2.center.y - s1.center.y) ,(s2.center.z - s1.center.z) };
	float distance = Length2(s3);
	if (distance <= s1.radius + s2.radius) {
		return true;
	}
	return false;


}
