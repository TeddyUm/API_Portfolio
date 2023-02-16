#pragma once
#include "gameNode.h"
#include <vector>
#include "minion.h"
#include "bullets.h"
#include "progresBar.h"

class player;//��ȣ������ ���� ���漱��

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;


	vEnemy _vMinion; //Ŭ���������� �����Ҵ� ������ �̴Ͼ� ����
	viEnemy _viMinion;//�ݺ��� �̴Ͼ� ����

	enemy* _Boss;// ����
	image* _end;
	bulletE* _bulletE;	 // �Ϲ� �� źȯ ���� �Ҵ�
	bulletB1* _bulletB1; // ���� �⺻ źȯ ���� �Ҵ�
	bulletB2* _bulletB2; // ���� ���� źȯ ���� �Ҵ�
	progresBar* _hpBar;	 // ���� HP��

	player* _player; //��ȣ������ ���� �����Ҵ�(�Ҵ縸 ����)

	int _maxHP;			// �ִ� HP
	int _currentHP;		// ���� HP
	int _spawnCount;	// ���� ���� ī��Ʈ
	int _count;
	int _hitCount;
	float _angleCount;	// ���� ī��Ʈ
	bool _bossLive;		// ���� ���� ���� ī��Ʈ
	bool _hit;
	TCHAR _text[128];

public:

	HRESULT Init();
	void Release();
	void Update();
	void Render();

	void SetMinion(int setType); // �� ���� ����
	void SetBoss(void);			 // ���� ����

	void BulletFire(void);	// �⺻ �� źȯ
	void BulletFire1(void);	// ���� �⺻ źȯ
	void BulletFire2(void);	// ���� ���� źȯ

	vector<enemy*> GetVMinion(void) { return _vMinion; }
	vector<enemy*>::iterator GetVIMinion(void) { return _viMinion; }

	void RemoveMinion(int arrNum);	//�� ���� �Լ�
	void Collision(void);			//�� �浹üũ �Լ�

	inline progresBar* GetHPBar() { return _hpBar; } // ���α׷��� �� ��ȯ��

	inline int GetHP() { return _currentHP; }		// ���α׷��� HP ���Լ�
	inline void SetHP(int hp) { _currentHP = hp; }	// ���α׷��� HP ���Լ�
	inline int GetBossLive() { return _bossLive; }	// ���� ���忩�� ���Լ�
	void setplayerMemoryAddressLink(player* player) { _player = player; } //��ȣ ������ ���� ����( ���ΰ����Լ����� ����)

	enemyManager();
	~enemyManager();
};

