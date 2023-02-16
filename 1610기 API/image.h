#pragma once


class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//리소스로부터 생성
		LOAD_FILE,			//파일로부터 생성
		LOAD_EMPTY,			//걍 생성
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float x;
		float y;
		int width;
		int height;
		BYTE loadType;

		int currentFrameX;
		int currentFrameY;
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		RECT boundingBox;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0.f;
			y = 0.f;
			width = 0;
			height = 0;
			loadType = LOAD_RESOURCE;

			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			boundingBox = RectMake();
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	//생성과 동시에 멤버이니셜라이즈로 초기화 해주는 변수들
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	CHAR*			_fileName;		//이미지 경로 이름

	BOOL			_trans;			//투명 배경이냐?
	COLORREF		_transColor;	//투명 색상

	BLENDFUNCTION	_blendFunc;
	LPIMAGE_INFO	_blendImage;

public:
	image();
	~image();

	//빈 비트맵 이미지 만든다
	HRESULT Init( int width, int height );

	//리소스로부터 읽어온다
	HRESULT Init( const DWORD resID, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE );

	//이미지 설정(파일로 읽어옴)
	HRESULT Init( const char* fileName, int width, int height,
		BOOL trans, COLORREF transColor );

	HRESULT Init( const char* fileName, float x, float y, int width, int height,
		BOOL trans, COLORREF transColor );

	HRESULT Init( const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, bool trans, COLORREF transColor);

	HRESULT Init( const char* fileName, int width, int height, 
		int frameX, int frameY, bool trans, COLORREF transColor);

	void InitAlpha();

	//삭제
	void Release();

	//투명 키값 설정 == 특정 색상 그리지 않을 거
	void SetTransColor( BOOL trans, COLORREF transColor );

	//그냥 렌더
	void Render( HDC hdc );
	void Render( HDC hdc, int destX, int destY );
	void Render( HDC hdc, int sourX, int sourY, int width, int height );
	void Render( HDC hdc, int destX, int destY, int sourX, int sourY, 
		int width, int height);

	//알파 렌더
	void AlphaRender( HDC hdc, BYTE alpha );
	void AlphaRender( HDC hdc, int destX, int destY, BYTE alpha );
	void AlphaRender( HDC hdc, int destX, int destY, int sourX, int sourY,
		int width, int height, BYTE alpha );

	//프레임 렌더
	void FrameRender( HDC hdc, int destX, int destY );
	void FrameRender( HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY );

	void LoopRender( HDC hdc, const LPRECT drawArea, int offsetX, int offsetY );


	//DC 얻어오기
	inline HDC GetMemDC() { return _imageInfo->hMemDC; }

	//좌표 X
	inline void SetX( float x ) { _imageInfo->x = x; }
	inline float GetX() { return _imageInfo->x; }

	//좌표 Y
	inline void SetY( float y ) { _imageInfo->y = y; }
	inline float GetY() { return _imageInfo->y; }

	//좌표 센터
	inline void SetCenter( float x, float y )
	{
		_imageInfo->x = x - ( _imageInfo->width / 2 );
		_imageInfo->y = y - ( _imageInfo->height / 2 );
	}

	//중점 X
	inline float GetCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + ( _imageInfo->width / 2 ) :
			_imageInfo->x + ( _imageInfo->frameWidth / 2 );
	}

	//중점 Y
	inline float GetCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + ( _imageInfo->height / 2 ) :
			_imageInfo->y + ( _imageInfo->frameHeight / 2 );
	}

	//가로 해상도
	inline int GetWidth() { return _imageInfo->width; }

	//세로 해상도
	inline int GetHeight() { return _imageInfo->height; }

	//바운딩 박스
	inline RECT BoundingBox()
	{
		RECT rc = { 
			(int)_imageInfo->x, 
			(int)_imageInfo->y,
			(int) _imageInfo->x + _imageInfo->frameWidth,
			(int) _imageInfo->y + _imageInfo->frameHeight };

		return rc;
	}

	//프레임
	inline void SetFrameX( int frameX )
	{
		_imageInfo->currentFrameX = frameX;

		if ( frameX > _imageInfo->maxFrameX )
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void SetFrameY( int frameY )
	{
		_imageInfo->currentFrameY = frameY;

		if ( frameY > _imageInfo->maxFrameY )
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int GetMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int GetMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int GetFrameX() { return _imageInfo->currentFrameX; }
	inline int GetFrameY() { return _imageInfo->currentFrameY; }

	inline int GetFrameWidth() { return _imageInfo->frameWidth; }
	inline int GetFrameHeight() { return _imageInfo->frameHeight; }
};

