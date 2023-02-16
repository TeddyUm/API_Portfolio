#include "stdafx.h"
#include "enemy.h"


enemy::enemy(){}


enemy::~enemy(){}

HRESULT  enemy::Init(const char * imageName, POINT position, int moveType)
{
	_count = _fireCountBoss1 = _countMove = _fireCountNormal = 0;
	_countMoveType = 0;
	_image = IMAGE_Mgr->FindImage(imageName);
	_rc = RectMakeCenter(position.x, position.y, _image->GetFrameWidth(), _image->GetFrameHeight());
	_moveType = moveType;
	_rndFireTimeN = RND->GetFromIntTo(10, 100); //초기화 필요
	_rndFireTimeB1 = RND->GetFromIntTo(300, 300);
	_rndFireTimeB2 = RND->GetFromIntTo(10, 10);
	return S_OK;
}
void  enemy::Release(void)
{

}
void  enemy::Update(void)
{
}
void  enemy::Render(void)
{
	Draw();
}


void  enemy::Draw(void)
{
	_image->FrameRender(GetMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

bool  enemy::BulletCountFireB1()
{
	_fireCountBoss1++;

	if (_fireCountBoss1%_rndFireTimeB1 == 0)
	{
		_fireCountBoss1 = 0;
		_rndFireTimeB1 = 10;
		return true;
	}
	return false;
}

bool  enemy::BulletCountFireB2()
{
	_fireCountBoss2++;

	if (_fireCountBoss2%_rndFireTimeB2 == 0)
	{
		_fireCountBoss2 = 0;
		_rndFireTimeB2 = 3;
		return true;
	}
	return false;
}

bool  enemy::BulletCountFireN()
{
	_fireCountNormal++;

	if (_fireCountNormal%_rndFireTimeN == 0)
	{
		_fireCountNormal = 0;
		_rndFireTimeN = 40;
		return true;
	}
	return false;
}

void enemy::Move(int moveType)
{
	_countMove++;
	if (_countMove % 35 == 0)
	{
		_countMoveType = 1;
	}
	if (_countMove % 70 == 0)
	{
		aN = RND->GetFromIntTo(1, 2);
		_countMoveType = 0;
		_countMove = 0;
	}

	if (_moveType == 1)
	{
		_rc.top += 2;
		_rc.bottom += 2;
	}

	if (_moveType == 2)
	{

		_rc.top += 2;
		_rc.bottom += 2;
	}
	if (_moveType == 3)// 
	{

		_rc.left += 2;
		_rc.right += 2;
	}

	if (_moveType == 4)// 
	{
		_rc.left -= 2;
		_rc.right -= 2;
	}

	if (_moveType == 5)// 
	{
		if (_countMoveType == 0)
		{
			_rc.left -= 3;
			_rc.right -= 3;
			_rc.top += 4;
			_rc.bottom += 4;
		}

		if (_countMoveType == 1)
		{
			_rc.left += 3;
			_rc.right += 3;
			_rc.top += 4;
			_rc.bottom += 4;
		}
	}

	if (_moveType == 7)// 보스
	{
		if (_rc.top < 200)
		{
			_rc.top += 1;
			_rc.bottom += 1;
		}
	}
}