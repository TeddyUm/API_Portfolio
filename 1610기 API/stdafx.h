// stdafx.h : 자주 사용하지만 자주 변경되지는 않는 
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다. 
// 


#pragma once 


//====================================================== 
// ## 헤더파일 써준다 ## 
//====================================================== 


#include "targetver.h" 


#define WIN32_LEAN_AND_MEAN //MFC가 아닌 응용 프로그램의 경우에는 
//WIN32_LEAN_AND_MEAN를 선언해 commdlg.h등등 
//필요없는 헤더파일을 인클루드 하지 않게 해준다. 

#include <windows.h>    //윈도우 헤더파일 인클루드 
#include <stdio.h>      //스탠다드 입출력 헤더 인클루드~ (printf, scanf 등등..) 
#include <tchar.h>      //윈도우에서 사용할 문자열 출력 헤더 인클루드~ 
						//MBCS (Multi Byte Character Set) 
						//-> 기존에 사용한던 멀티바이트 형태의 문자열~ 
						//WBCS (Wide Byte Character Set) 
						//-> 모든 문자를 2바이트로 처리~~, 유니코드 기반...

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "utils.h"
#include "imageManager.h"
#include "timeManager.h"


using namespace MY_UTIL;

//====================================================== 
// ## 디파인문 써준다 ## 
//====================================================== 
#define WINNAME ( LPTSTR)(TEXT ("APIWindow")) 
#define WINSTARTX 600 
#define WINSTARTY 0 
#define WINSIZEX 768
#define WINSIZEY 1000
#define CENTERX (WINSIZEX / 2)
#define CENTERY (WINSIZEY / 2)
#define WINSTYLE WS_CAPTION | WS_SYSMENU 


#define SAFE_DELETE(p)			{ if(p) { delete (p);     (p)= NULL; } } 
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete [] (p);  (p)= NULL; } } 
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p)= NULL; } } 
#define SAFE_REL_DEL(p)			{ if(p) { (p)->Release(); delete(p); (p) = NULL;}}

//====================================================== 
// ## 싱글톤 매크로 써준다 ## 
//====================================================== 
#define RND randomFunction::GetSingleton()
#define KEY keyManager::GetSingleton()
#define IMAGE_Mgr imageManager::GetSingleton()
#define TIMEMGR timeManager::GetSingleton()

//====================================================== 
// ## 전역변수 써준다 ## 
//====================================================== 
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;