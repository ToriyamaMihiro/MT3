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

bool IsCollisionSpP(const Sphere& sphere, const Plane& plane)
{
	float k, product;
	product = (plane.normal.x * sphere.center.x + plane.normal.y * sphere.center.y + plane.normal.z * sphere.center.z);
	k = abs(product - plane.distance);
	if (k <= sphere.radius) {
		return true;
	}
	return false;
}

bool IsCollisionSeP(const Segment& segment, const Plane& plane)
{
	float dot = Dot(plane.normal, segment.diff);
	if (dot == 0.0f) {//垂直＝平行なら衝突していない
		return false;
	}
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;//t=(d-o・n)/(b・n)


	if (t >= 0 && t <= 1) {
		return true;
	}
	else {
		return false;
	}
}

bool IsCollisionTS(const Triangle& triangle, const Segment& segment)
{
	Vector3 v1 = Subtract(triangle.vertices[1], triangle.vertices[0]);
	Vector3 v2 = Subtract(triangle.vertices[2], triangle.vertices[1]);//a,b,cの三点が今回は三角形の頂点
	Vector3 normal = Cross(v1, v2);//法線を求める
	normal = Normalize(normal);

	float dot = Dot(normal, segment.diff);
	
	Plane plane;
	plane.distance = Dot(triangle.vertices[0], normal);

	float t = (plane.distance - Dot(segment.origin, normal)) / dot;//t=(d-o・n)/(b・n)
	Vector3 p = Add(segment.origin, Scaler(t, segment.diff));//p=o+tb

	Vector3 cross01 = Cross(Subtract(triangle.vertices[1], triangle.vertices[0]), Subtract(p, triangle.vertices[1]));
	Vector3 cross12 = Cross(Subtract(triangle.vertices[2], triangle.vertices[1]), Subtract(p, triangle.vertices[2]));
	Vector3 cross20 = Cross(Subtract(triangle.vertices[0], triangle.vertices[2]), Subtract(p, triangle.vertices[0]));

	if (Dot(cross01, normal) >= 0.0f && Dot(cross12, normal) >= 0.0f && Dot(cross20, normal) >= 0.0f) {
		return true;
	}
	else {
		return false;
	}
}
