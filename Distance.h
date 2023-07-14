#pragma once
#include"Vector3.h"
#include"Segment.h"
#include "Grid.h"


Vector3 Project(const Vector3& v1, const Vector3& v2);

Vector3 ClosetPoint(const Vector3& point, const Segment& segment);



