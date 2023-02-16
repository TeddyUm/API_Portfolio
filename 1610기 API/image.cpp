#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")


image::image()
	: _imageInfo( NULL )
	, _fileName( NULL )
	, _trans( FALSE )
	, _transColor( RGB( 0, 0, 0 ) )
	, _blendImage(NULL)
{
}


image::~image()
{
}

//빈 비트맵 이미지 만든다
HRESULT image::Init( int width, int height )
{
	//초기화가 다시 되는 것을 방지
	if ( _imageInfo != NULL ) Release();

	//DC 얻어 오기
	HDC hdc = GetDC( _hWnd );

	//이미지 정보 생성
	_imageInfo = new IMAGE_INFO;//생성자에서 초기화 해주지만 명시적으로 다시 한 번
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC( hdc );
	_imageInfo->hBit = (HBITMAP) CreateCompatibleBitmap( hdc, width, height );
	_imageInfo->hOBit = (HBITMAP) SelectObject( _imageInfo->hMemDC, _imageInfo->hBit );
	_imageInfo->width = width;
	_imageInfo->height = height;

	_imageInfo->x = 0.f;
	_imageInfo->y = 0.f;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->boundingBox = BoundingBox();



	_fileName = NULL;

	//투명 컬러 셋팅
	_trans = FALSE;
	_transColor = RGB( 0, 0, 0 );

	//알파블렌드 속성값
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//얻은 DC 해제
	ReleaseDC( _hWnd, hdc );

	//리소스 얻어오기 실패시 처리
	if ( _imageInfo->hBit == 0 )
	{
		Release();

		return E_FAIL;
	}

	return S_OK;
}

//리소스로부터 읽어온다
HRESULT image::Init( const DWORD resID, int width, int height,
	BOOL trans /*= FALSE*/, COLORREF transColor /*= FALSE*/ )
{
	//초기화가 다시 되는 것을 방지
	if ( _imageInfo != NULL ) Release();

	//DC 얻어 오기
	HDC hdc = GetDC( _hWnd );

	//이미지 정보 생성
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC( hdc );
	_imageInfo->hBit = (HBITMAP) LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP) SelectObject( _imageInfo->hMemDC, _imageInfo->hBit );
	_imageInfo->width = width;
	_imageInfo->height = height;

	_imageInfo->x = 0.f;
	_imageInfo->y = 0.f;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->boundingBox = BoundingBox();

	_fileName = NULL;

	//투명 컬러 셋팅
	_trans = trans;
	_transColor = transColor;

	//알파블렌드 속성값
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;


	//얻은 DC 해제
	ReleaseDC( _hWnd, hdc );

	//리소스 얻어오기 실패시 처리
	if ( _imageInfo->hBit == 0 )
	{
		Release();

		return E_FAIL;
	}

	return S_OK;
}

//이미지 설정(파일로 읽어옴)
HRESULT image::Init( const char* fileName, int width, int height,
	BOOL trans, COLORREF transColor )
{
	//초기화가 다시 되는 것을 방지
	if ( _imageInfo != NULL ) Release();

	//DC 얻어 오기
	HDC hdc = GetDC( _hWnd );

	//이미지 정보 생성
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC( hdc );
	_imageInfo->hBit = (HBITMAP) LoadImage( _hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE );
	_imageInfo->hOBit = (HBITMAP) SelectObject( _imageInfo->hMemDC, _imageInfo->hBit );
	_imageInfo->width = width;
	_imageInfo->height = height;

	_imageInfo->x = 0.f;
	_imageInfo->y = 0.f;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->boundingBox = BoundingBox();
	
	//깊은 복사 해야 됨. fileName 매개변수가 const기 때문.
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy_s( _fileName, len + 1, fileName );

	//투명 컬러 셋팅
	_trans = trans;
	_transColor = transColor;

	//알파블렌드 속성값
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//얻은 DC 해제
	ReleaseDC( _hWnd, hdc );

	//리소스 얻어오기 실패시 처리
	if ( _imageInfo->hBit == 0 )
	{
		Release();

		return E_FAIL;
	}

	return S_OK;
}

HRESULT image::Init( const char * fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor )
{
	//초기화가 다시 되는 것을 방지
	if ( _imageInfo != NULL ) Release();

	//DC 얻어 오기
	HDC hdc = GetDC( _hWnd );

	//이미지 정보 생성
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC( hdc );
	_imageInfo->hBit = (HBITMAP) LoadImage( _hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE );
	_imageInfo->hOBit = (HBITMAP) SelectObject( _imageInfo->hMemDC, _imageInfo->hBit );
	_imageInfo->width = width;
	_imageInfo->height = height;

	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_imageInfo->boundingBox = BoundingBox();

	//깊은 복사 해야 됨. fileName 매개변수가 const기 때문.
	int len = strlen( fileName );
	_fileName = new char[len + 1];
	strcpy_s( _fileName, len + 1, fileName );

	//투명 컬러 셋팅
	_trans = trans;
	_transColor = transColor;

	//알파블렌드 속성값
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//얻은 DC 해제
	ReleaseDC( _hWnd, hdc );

	//리소스 얻어오기 실패시 처리
	if ( _imageInfo->hBit == 0 )
	{
		Release();

		return E_FAIL;
	}

	return S_OK;
}

HRESULT image::Init( const char * fileName, float x, float y, int width, int height, 
	int frameX, int frameY, bool trans, COLORREF transColor )
{
	//초기화가 다시 되는 것을 방지
	if ( _imageInfo != NULL ) Release();

	//DC 얻어 오기
	HDC hdc = GetDC( _hWnd );

	//이미지 정보 생성
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC( hdc );
	_imageInfo->hBit = (HBITMAP) LoadImage( _hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE );
	_imageInfo->hOBit = (HBITMAP) SelectObject( _imageInfo->hMemDC, _imageInfo->hBit );
	_imageInfo->width = width;
	_imageInfo->height = height;

	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->boundingBox = BoundingBox();

	//깊은 복사 해야 됨. fileName 매개변수가 const기 때문.
	int len = strlen( fileName );
	_fileName = new char[len + 1];
	strcpy_s( _fileName, len + 1, fileName );

	//투명 컬러 셋팅
	_trans = trans;
	_transColor = transColor;

	//알파블렌드 속성값
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//얻은 DC 해제
	ReleaseDC( _hWnd, hdc );

	//리소스 얻어오기 실패시 처리
	if ( _imageInfo->hBit == 0 )
	{
		Release();

		return E_FAIL;
	}

	return S_OK;
}

HRESULT image::Init( const char * fileName, int width, int height, 
	int frameX, int frameY, bool trans, COLORREF transColor )
{
	//초기화가 다시 되는 것을 방지
	if ( _imageInfo != NULL ) Release();

	//DC 얻어 오기
	HDC hdc = GetDC( _hWnd );

	//이미지 정보 생성
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC( hdc );
	_imageInfo->hBit = (HBITMAP) LoadImage( _hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE );
	_imageInfo->hOBit = (HBITMAP) SelectObject( _imageInfo->hMemDC, _imageInfo->hBit );
	_imageInfo->width = width;
	_imageInfo->height = height;

	_imageInfo->x = 0.f;
	_imageInfo->y = 0.f;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->boundingBox = BoundingBox();

	//깊은 복사 해야 됨. fileName 매개변수가 const기 때문.
	int len = strlen( fileName );
	_fileName = new char[len + 1];
	strcpy_s( _fileName, len + 1, fileName );

	//투명 컬러 셋팅
	_trans = trans;
	_transColor = transColor;

	//알파블렌드 속성값
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//얻은 DC 해제
	ReleaseDC( _hWnd, hdc );

	//리소스 얻어오기 실패시 처리
	if ( _imageInfo->hBit == 0 )
	{
		Release();

		return E_FAIL;
	}

	return S_OK;
}

void image::InitAlpha()
{
	HDC hdc = GetDC( _hWnd );

	//알파 블렌드 사용을 위한 이미지 설정
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC( hdc );
	_blendImage->hBit = (HBITMAP) CreateCompatibleBitmap( hdc, _imageInfo->width, _imageInfo->height );
	_blendImage->hOBit = (HBITMAP) SelectObject( _blendImage->hMemDC, _blendImage->hBit );
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	ReleaseDC( _hWnd, hdc );
}

//삭제
void image::Release()
{
	if ( _imageInfo )
	{
		//이미지 삭제
		SelectObject( _imageInfo->hMemDC, _imageInfo->hOBit );
		DeleteObject( _imageInfo->hBit );
		DeleteDC( _imageInfo->hMemDC );

		//포인터도 삭제
		SAFE_DELETE( _imageInfo );
		SAFE_DELETE( _fileName );

		//투명 컬러 초기화
		_trans = FALSE;
		_transColor = RGB(0, 0, 0);
	}

	if ( _blendImage )
	{
		//이미지 삭제
		SelectObject( _blendImage->hMemDC, _blendImage->hOBit );
		DeleteObject( _blendImage->hBit );
		DeleteDC( _blendImage->hMemDC );

		SAFE_DELETE( _blendImage );
	}
}

//투명 키값 설정 == 특정 색상 그리지 않을 거
void image::SetTransColor( BOOL trans, COLORREF transColor )
{
	_trans = trans;
	_transColor = transColor;
}

void image::Render( HDC hdc )
{
	if ( _trans )
	{
		GdiTransparentBlt( hdc, (int)_imageInfo->x, (int)_imageInfo->y, 
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_transColor );
	}
	else
	{
		BitBlt( hdc, (int) _imageInfo->x, (int) _imageInfo->y,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY );
	}
}

//렌더
void image::Render( HDC hdc, int destX, int destY )
{
	if ( _trans )
	{
		GdiTransparentBlt( hdc, //복사 될 DC
			destX,				//복사 될 위치 X
			destY,				//복사 될 위치 Y
			_imageInfo->width,	//복사 될 가로 사이즈
			_imageInfo->height,	//복사 될 세로 사이즈
			_imageInfo->hMemDC,	//복사 할 이미지 DC
			0, 0,				//복사 시작지점 X, Y
			_imageInfo->width,	//복사 할 width
			_imageInfo->height,	//복사 할 height
			_transColor );		//제외시킬 색상
	}
	else
	{
		//BitBlt 는 DC 간의 고속 복사 해주는 녀석
		BitBlt(hdc,					//복사 될 DC
			destX,					//복사 될 위치 X
			destY,					//복사 될 위치 Y
			_imageInfo->width,		//복사 될 가로 사이즈
			_imageInfo->height,		//복사 될 세로 사이즈
			_imageInfo->hMemDC,		//복사 할 이미지 DC
			0, 0,					//복사 시작지점 X, Y
			SRCCOPY );				//복사 속성 지정
	}
}

void image::Render( HDC hdc, int destX, int destY, int sourWidth, int sourHeight )
{
	if ( _trans )
	{
		GdiTransparentBlt( hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, 0, 0, sourWidth, sourHeight, _transColor );
	}
	else
	{
		BitBlt( hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, 0, 0, SRCCOPY );
	}
}

void image::Render( HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight )
{
	if ( _trans )
	{
		GdiTransparentBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor );
	}
	else
	{
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY );
	}
}

void image::AlphaRender( HDC hdc, BYTE alpha )
{
	if ( _blendImage == NULL ) InitAlpha();

	_blendFunc.SourceConstantAlpha = alpha;

	if ( _trans )
	{
		//출력해야 될 Dc에 그려져있는 내용을 blend에 그려준다
		BitBlt( _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y, SRCCOPY );

		//출력해야 될 이미지를 blend에 그려준다
		GdiTransparentBlt( _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _transColor );

		//blendDC를 출력해야 될 DC에 그린다
		AlphaBlend( hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc );
	}
	else
	{
		AlphaBlend( hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc );
	}
}

void image::AlphaRender( HDC hdc, int destX, int destY, BYTE alpha )
{
	if ( _blendImage == NULL ) InitAlpha();
	_blendFunc.SourceConstantAlpha = alpha;

	if ( _trans )
	{
		//출력해야 될 Dc에 그려져있는 내용을 blend에 그려준다
		BitBlt( _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY );

		//출력해야 될 이미지를 blend에 그려준다
		GdiTransparentBlt( _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _transColor );

		//blendDC를 출력해야 될 DC에 그린다
		AlphaBlend( hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc );
	}
	else
	{
		AlphaBlend( hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc );
	}
}

void image::AlphaRender( HDC hdc, int destX, int destY, int sourX, int sourY, int width, int height, BYTE alpha )
{
	if ( _blendImage == NULL ) InitAlpha();
	_blendFunc.SourceConstantAlpha = alpha;

	if ( _trans )
	{
		//출력해야 될 Dc에 그려져있는 내용을 blend에 그려준다
		BitBlt( _blendImage->hMemDC, 0, 0, width, height,
			hdc, destX, destY, SRCCOPY );

		//출력해야 될 이미지를 blend에 그려준다
		GdiTransparentBlt( _blendImage->hMemDC, 0, 0, width, height,
			_imageInfo->hMemDC, sourX, sourY,
			width, height, _transColor );

		//blendDC를 출력해야 될 DC에 그린다
		AlphaBlend( hdc, destX, destY, width, height,
			_blendImage->hMemDC, 0, 0, width, height, _blendFunc );
	}
	else
	{
		AlphaBlend( hdc, destX, destY, width, height,
			_imageInfo->hMemDC, 0, 0, width, height, _blendFunc );
	}
}

void image::FrameRender( HDC hdc, int destX, int destY )
{
	if ( _trans )
	{
		GdiTransparentBlt( hdc, destX, destY, 
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,	
			_imageInfo->currentFrameX * _imageInfo->frameWidth, 
			_imageInfo->currentFrameY * _imageInfo->frameHeight, 
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_transColor );	
	}
	else
	{
		//BitBlt 는 DC 간의 고속 복사 해주는 녀석
		BitBlt( hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,	
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY );
	}
}

void image::FrameRender( HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY )
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if ( currentFrameX > _imageInfo->maxFrameX ) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	if ( currentFrameY > _imageInfo->maxFrameY ) _imageInfo->currentFrameY = _imageInfo->maxFrameY;

	if ( _trans )
	{
		GdiTransparentBlt( hdc, destX, destY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_transColor );
	}
	else
	{
		//BitBlt 는 DC 간의 고속 복사 해주는 녀석
		BitBlt( hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY );
	}

}

void image::LoopRender( HDC hdc, const LPRECT drawArea, int offsetX, int offsetY )
{
	//offset 값이 음수인 경우에 보정
	if ( offsetX < 0 ) offsetX = _imageInfo->width + ( offsetX % _imageInfo->width );
	if ( offsetY < 0 ) offsetY = _imageInfo->height + ( offsetY % _imageInfo->height );

	//그려지는 소스 영역 셋팅할 변수 만들자
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 영역 DC
	RECT rcDest;

	//그려야할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프 셋팅
	for ( int y = 0; y < drawAreaH; y += sourHeight )
	{
		//소스 영역의 높이 계산
		rcSour.top = ( y + offsetY ) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스의 영역이 그리기 화면을 넘어갔다면 (화면 밖으로 이미지가 나갔을 때)
		if ( y + sourHeight > drawAreaH )
		{
			//넘어간 그림의 값만큼 바텀 값을 올려주자
			rcSour.bottom -= ( y + sourHeight ) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프 셋팅
		for ( int x = 0; x < drawAreaW; x += sourWidth )
		{
			//소스의 영역 가로 계산
			rcSour.left = ( x + offsetX ) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if ( x + sourWidth > drawAreaW )
			{
				//넘어간 만큼 right 값을 왼쪽으로 처리
				rcSour.right -= ( x + sourWidth ) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자 (부분 출력 함수)
			Render( hdc, rcDest.left, rcDest.top, 
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top );
		}
	}
}

