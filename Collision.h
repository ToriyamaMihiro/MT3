#pragma once
#include "Grid.h"
#include "Distance.h"
class Collision
{
};

bool IsCollisonSS(const Sphere& s1, const Sphere& s2);

bool IsCollisionSP(const Sphere& sphere, const Plane& plane);