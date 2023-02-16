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

	_offsetX = _offsetY = 0;	// 배경 이동
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
	//DC를 입력한 영역만큼 단색으로 칠해준다. 
	PatBlt( GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS );
	//======================================================== 여기 사이에서 뭔갈 그리자
	
	HFONT hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
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
	//백버퍼에 있는 내용을 hdc 에 그린다
	this->GetBackBuffer()->Render( GetHDC(), 0, 0 );
}