#pragma once
#include "enemy.h"

class minion : public enemy
{
public: minion(); ~minion();
};

class boss : public enemy
{
public:
	boss(); 
	~boss();
};


