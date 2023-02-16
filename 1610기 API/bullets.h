#pragma once

#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* bulletImage;		//총알 이미지
	RECT rc;				//총알 렉트
	float x, y;				//총알 좌표(현재 좌표)
	float fireX, fireY;		//총알 발사좌표(시작 좌표)
	float speed;			//총알 스피드
	float angle;			//바라보는 각도
	float angleRate;		//각도 변경
	float radius;			//반지름
	float range;			//총알 사거리
	float rapid;			//탄 간격
	bool fire;				//발사 유무
	int count;				//프레임 이미지 카운터
};

class bullets : public gameNode
{
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	int _bulletMax;
	float _range;

public:
	bullets();
	~bullets();

	HRESULT Init( int bulletMax, float range);
	void Release();
	void Update();
	void Render();
	void BulletFire(float x, float y);
	void BulletMove();

	void RemoveBullet(int arrayNum);

	vector<tagBullet> GetVBullet() { return _vBullet; }
	vector<tagBullet>::iterator GetVIBullet() { return _viBullet; }
};

class bulletE : public gameNode
{
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	bulletE();
	~bulletE();

	HRESULT Init(const char* imageName, int bulletMax, float range);
	void Release();
	void Update();
	void Render();

	void BulletFire(float x, float y, float angle);
	void BulletMove();

	void RemoveBullet(int arrayNum);

	vector<tagBullet> GetVBullet() { return _vBullet; }
};

class bulletB1 : public gameNode
{
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	bulletB1();
	~bulletB1();

	HRESULT Init(const char* imageName, int bulletMax, float range);
	void Release();
	void Update();
	void Render();

	void BulletFire(float x, float y, float angle, float angleRate, float rapid);
	void BulletMove();

	void RemoveBullet(int arrayNum);

	vector<tagBullet> GetVBullet() { return _vBullet; }
};

class bulletB2 : public gameNode
{
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	bulletB2();
	~bulletB2();

	HRESULT Init(const char* imageName, int bulletMax, float range);
	void Release();
	void Update();
	void Render();

	void BulletFire(float x, float y, float angle, float angleRate, float rapid);
	void BulletMove();

	void RemoveBullet(int arrayNum);

	vector<tagBullet> GetVBullet() { return _vBullet; }
};