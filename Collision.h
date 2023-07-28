#pragma once
#include "Grid.h"
#include "Distance.h"
class Collision
{
};

bool IsCollisonSS(const Sphere& s1, const Sphere& s2);

bool IsCollisionSpP(const Sphere& sphere, const Plane& plane);

bool IsCollisionSeP(const Segment& segment, const Plane& plane);

bool IsCollisionTS(const Triangle& triangle, const Segment& segment);