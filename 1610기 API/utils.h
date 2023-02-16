#pragma once

#include <cmath>

#define PI 3.1415926543f
#define PI2 (PI * 2)

#define DEG_TO_RAD(deg) PI / 180 * (deg)
#define RAD_TO_DEG(rad) 180 / PI * (rad)
#define ONE_RAD 0.01745329f

#define EPSILON 0.0001f //�ε��Ҽ��� ������ �Ͼ �� �ִ� ������
#define EQUAL(x, y) (fabsf((x) - (y)) < EPSILON)

#define FLOAT_TO_INT(f) static_cast<int>((f) + EPSILON)


namespace MY_UTIL
{
	//�Ÿ� �������� �Լ�
	float GetDistance( float startX, float startY, float endX, float endY );

	//�ޱ� �������� �Լ�
	float GetAngle( float originX, float originY, float dirX, float dirY );
}