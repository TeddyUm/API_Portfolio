#pragma once

#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* bulletImage;		//�Ѿ� �̹���
	RECT rc;				//�Ѿ� ��Ʈ
	float x, y;				//�Ѿ� ��ǥ(���� ��ǥ)
	float fireX, fireY;		//�Ѿ� �߻���ǥ(���� ��ǥ)
	float speed;			//�Ѿ� ���ǵ�
	float angle;			//�ٶ󺸴� ����
	float angleRate;		//���� ����
	float radius;			//������
	float range;			//�Ѿ� ��Ÿ�
	float rapid;			//ź ����
	bool fire;				//�߻� ����
	int count;				//������ �̹��� ī����
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