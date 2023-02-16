#include "stdafx.h"
#include "bullets.h"


bullets::bullets()
{
}


bullets::~bullets()
{
}

HRESULT bullets::Init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bullets::Release()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		if (_viBullet->bulletImage)
		{
			SAFE_REL_DEL(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
			++_viBullet;
	}

	_vBullet.clear();
}

void bullets::Update()
{
	BulletMove();
}

void bullets::Render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->Render(
			GetMemDC(),	_viBullet->rc.left, _viBullet->rc.top);
	}
}

void bullets::BulletFire(float x, float y)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.angle = PI;
	bullet.bulletImage = IMAGE_Mgr->AddImage("bullet", "image/playeBullet.bmp", 14, 16, true, RGB(255, 255, 255));
	bullet.fire = true;
	bullet.fireX = bullet.x = x;
	bullet.fireY = bullet.y = y;
	bullet.speed = 15;
	bullet.rc = RectMakeCenter(x, y,
		bullet.bulletImage->GetFrameWidth(),
		bullet.bulletImage->GetFrameHeight());

	_vBullet.push_back(bullet);
}

void bullets::BulletMove()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->GetFrameWidth(),
			_viBullet->bulletImage->GetFrameHeight());

		if (_range < GetDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y)) {
			_viBullet = _vBullet.erase(_viBullet);
		}
		else {
			_viBullet++;
		}
	}
}

void bullets::RemoveBullet(int arrayNum)
{
	_vBullet.erase(_vBullet.begin() + arrayNum);
}

bulletE::bulletE(){}

bulletE::~bulletE(){}

HRESULT bulletE::Init(const char * imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bulletE::Release(void)
{
}

void bulletE::Update(void)
{
	BulletMove();
}

void bulletE::Render(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->Render(GetMemDC(),
			_viBullet->rc.left, _viBullet->rc.top);
	}
}

void bulletE::BulletFire(float x, float y, float angle)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = IMAGE_Mgr->FindImage("enemyBullet");
	bullet.speed = 5.f;
	bullet.angle = angle;
	bullet.fireX = bullet.x = x;
	bullet.fireY = bullet.y = y;
	bullet.rc = RectMakeCenter(x, y,
		bullet.bulletImage->GetFrameWidth(),
		bullet.bulletImage->GetFrameHeight());

	_vBullet.push_back(bullet);
}

void bulletE::BulletMove(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); )
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		//움직인 만큼 렉트 재조정
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->GetFrameWidth(),
			_viBullet->bulletImage->GetFrameHeight());

		if (_range < MY_UTIL::GetDistance(
			_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void bulletE::RemoveBullet(int arrayNum)
{
	_vBullet.erase(_vBullet.begin() + arrayNum);
}


bulletB1::bulletB1() {}

bulletB1::~bulletB1() {}

HRESULT bulletB1::Init(const char * imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bulletB1::Release(void)
{
}

void bulletB1::Update(void)
{
	BulletMove();
}

void bulletB1::Render(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->Render(GetMemDC(),
			_viBullet->rc.left, _viBullet->rc.top);
	}
}

void bulletB1::BulletFire(float x, float y, float angle, float angleRate, float rapid)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = IMAGE_Mgr->FindImage("enemyBossBullet1");
	bullet.speed = 1.f;
	bullet.angle = angle;
	bullet.rapid = rapid;
	bullet.fireX = bullet.x = x;
	bullet.fireY = bullet.y = y;
	bullet.rc = RectMakeCenter(x, y,
		bullet.bulletImage->GetFrameWidth(),
		bullet.bulletImage->GetFrameHeight());

	_vBullet.push_back(bullet);
}

void bulletB1::BulletMove(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); )
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->angle += 0.018;
		_viBullet->speed += _viBullet->rapid;

		//움직인 만큼 렉트 재조정
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->GetFrameWidth(),
			_viBullet->bulletImage->GetFrameHeight());

		if (_range < MY_UTIL::GetDistance(
			_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void bulletB1::RemoveBullet(int arrayNum)
{
	_vBullet.erase(_vBullet.begin() + arrayNum);

}

bulletB2::bulletB2() {}

bulletB2::~bulletB2() {}

HRESULT bulletB2::Init(const char * imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bulletB2::Release(void)
{
}

void bulletB2::Update(void)
{
	BulletMove();
}

void bulletB2::Render(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->Render(GetMemDC(),
			_viBullet->rc.left, _viBullet->rc.top);
	}
}

void bulletB2::BulletFire(float x, float y, float angle, float angleRate, float rapid)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = IMAGE_Mgr->FindImage("enemyBossBullet2");
	bullet.speed = 5.f;
	bullet.angle = angle;
	bullet.rapid = rapid;
	bullet.fireX = bullet.x = x;
	bullet.fireY = bullet.y = y;
	bullet.rc = RectMakeCenter(x, y,
		bullet.bulletImage->GetFrameWidth(),
		bullet.bulletImage->GetFrameHeight());

	_vBullet.push_back(bullet);
}

void bulletB2::BulletMove(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); )
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->speed += _viBullet->rapid;

		//움직인 만큼 렉트 재조정
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->GetFrameWidth(),
			_viBullet->bulletImage->GetFrameHeight());

		if (_range < MY_UTIL::GetDistance(
			_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

void bulletB2::RemoveBullet(int arrayNum)
{
	_vBullet.erase(_vBullet.begin() + arrayNum);

}
