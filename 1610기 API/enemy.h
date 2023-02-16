#pragma once
#include "gameNode.h"

class enemy : public gameNode
{
protected:
	image* _image;
	RECT _rc;

	int _currentFrameX;			//���ʹ� ���� ������X   
	int _currentFrameY;			//���ʹ� ���� ������Y

	int _count;					//�߻� �����̸� ���� ī��Ʈ   
	int _fireCountNormal;		//�߻� �ð��� ���� ī��Ʈ   
	int _fireCountBoss1;		//�߻� �ð��� ���� ī��Ʈ  
	int _fireCountBoss2;		//�߻� �ð��� ���� ī��Ʈ
	int _rndFireTimeN;			//�����ϰ� �߻�ð��� ������ ī��Ʈ
	int _rndFireTimeB1;			//�����ϰ� �߻�ð��� ������ ī��Ʈ
	int _rndFireTimeB2;			//�����ϰ� �߻�ð��� ������ ī��Ʈ
	int _countMove;				//�������� ������ �ٲ� ���� ī��Ʈ
	int _countMoveType;			//ī���� �� �̵� ü����(ūŸ�Ծȿ��� ī������ ����Ǵ� Ÿ��)
	int _moveType;              //���ʹ��� ������ Ÿ��(ūŸ��)
	int _bulletTyep;			//���ʹ��� �Ѿ� Ÿ��

	float aX;
	float aN;

public:
	HRESULT Init(const char* imageName, POINT position, int moveType);
	void Release(void);
	void Update(void);
	void Render(void);

	void Move(int moveType);		//�� ������ �Լ�
	void Draw(void);				//���� �Լ�
	bool BulletCountFireN();		// �Ϲ� ź �߻� ī��Ʈ �Լ�
	bool BulletCountFireB1();		// ���� ź �߻� ī��Ʈ �Լ�
	bool BulletCountFireB2();		// ���� 2�� ź �߻� ī��Ʈ �Լ�

	RECT GetRect() { return _rc; }				// ��Ʈ �� �Լ�
	int GetMoveType() { return _moveType; }		// ����Ÿ�� �� �Լ�
	int GetBulletType() { return _bulletTyep; } // �Ѿ�Ÿ�� �� �Լ�
	image* GetImage() { return _image; }		// �̹��� �� �Լ�

	enemy();
	~enemy();
};

