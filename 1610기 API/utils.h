#pragma once

#include <cmath>

#define PI 3.1415926543f
#define PI2 (PI * 2)

#define DEG_TO_RAD(deg) PI / 180 * (deg)
#define RAD_TO_DEG(rad) 180 / PI * (rad)
#define ONE_RAD 0.01745329f

#define EPSILON 0.0001f //부동소수점 오류가 일어날 수 있는 범위값
#define EQUAL(x, y) (fabsf((x) - (y)) < EPSILON)

#define FLOAT_TO_INT(f) static_cast<int>((f) + EPSILON)


namespace MY_UTIL
{
	//거리 가져오는 함수
	float GetDistance( float startX, float startY, float endX, float endY );

	//앵글 가져오는 함수
	float GetAngle( float originX, float originY, float dirX, float dirY );
}