#pragma once

#include "singletonBase.h"
#include <string>
#include <vector>

class txtData : public singletonBase<txtData>
{
public:
	txtData();
	~txtData();

	HRESULT Init();
	void Release();
	
	//세이브
	void TxtSave( const char* saveFileName, std::vector<std::string> vStr );
	char* VectorArrayCombine( std::vector<std::string> vArray );

	//로드
	std::vector<std::string> TxtLoad( const char* loadFileName );
	std::vector<std::string> CharArraySeparation( char charArray[] );

};

