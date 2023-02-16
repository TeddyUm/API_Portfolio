#include "stdafx.h"
#include "gameStudy.h"

gameStudy::gameStudy()
{
}


gameStudy::~gameStudy()
{
}

HRESULT gameStudy::Init()
{
	gameNode::Init(true);

	_player = new player;
	_player->Init();

	_em = new enemyManager;
	_em->Init();

	_background = IMAGE_Mgr->AddImage("background", "image/back.bmp", WINSIZEX, WINSIZEY, false, false);
	_intro = IMAGE_Mgr->AddImage("intro", "image/opening.bmp", WINSIZEX, WINSIZEY, false, false);

	_offsetX = _offsetY = 0;	// ��� �̵�
	_gameStart = false;

	_player->setEmMemoryAddressLink(_em);
	_em->setplayerMemoryAddressLink(_player);


	if (_gameStart == false)
	{
		PlaySound("opening.wav", NULL, SND_ASYNC | SND_NODEFAULT | SND_LOOP);
	}


	return S_OK;
}

void gameStudy::Release()
{
	gameNode::Release();
}

void gameStudy::Update()
{
	if (_gameStart == true)
	{
		_offsetY--;
		gameNode::Update();
		_player->Update();
		_em->Update();
	}

	if (KEY->IsStayKeyDown(VK_SPACE) && _gameStart == false)
	{
		_gameStart = true;
		PlaySound("play.wav", NULL, SND_ASYNC | SND_NODEFAULT | SND_LOOP);
	}
}

void gameStudy::Render( void )
{
	//DC�� �Է��� ������ŭ �ܻ����� ĥ���ش�. 
	PatBlt( GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS );
	//======================================================== ���� ���̿��� ���� �׸���
	
	HFONT hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("�ü�"));
	HFONT OldFont = (HFONT)SelectObject(GetMemDC(), hFont);
	SetTextColor(GetMemDC(), RGB(250, 250, 50));
	SetBkMode(GetMemDC(), TRANSPARENT);

	if (_gameStart == true)
	{
		_background->LoopRender(GetMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _offsetX, _offsetY);
		_em->Render();
		_player->Render();
	}
	else if (_gameStart == false)
	{
		_intro->Render(GetMemDC());
		TextOut(GetMemDC(), CENTERX - 100, CENTERY + 200, "Press Space to Start", lstrlen("Press Space to Start"));
	}

	//========================================================
	//����ۿ� �ִ� ������ hdc �� �׸���
	this->GetBackBuffer()->Render( GetHDC(), 0, 0 );
}