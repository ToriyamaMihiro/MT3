#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include <cmath>
#include"Calc.h"
#include <Novice.h>
#include<numbers>

struct Sphere
{
	Vector3 center; //中心点
	float radius;   //半径
};

struct Plane {
	Vector3 normal;//法線
	float distance;//距離
};

struct Segment {
	Vector3 origin;//始点
	Vector3 diff;//終点ベクトル
};

struct Line {
	Vector3 origin;//始点
	Vector3 diff;//終点ベクトル
};

struct Triangle {
	Vector3 vertices[3];
};

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void DrawTriangle(const Triangle&triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);