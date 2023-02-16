#include "stdafx.h"
#include "utils.h"


namespace MY_UTIL
{
	//거리 가져오는 함수
	float GetDistance( float startX, float startY, float endX, float endY )
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf( x*x + y*y );
	}

	//앵글 가져오는 함수
	float GetAngle( float originX, float originY, float dirX, float dirY )
	{
		float x = dirX - originX;
		float y = dirY - originY;

		// ####### atan2 #######
		return -atan2( y, x );

		/*
		// ####### acosf #######
		float distance = sqrtf( x*x + y*y );
		float angle = acosf( x / distance );

		if ( y > 0 )
			angle = PI2 - angle;

		return angle;
		*/
	}
}