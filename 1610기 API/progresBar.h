#pragma once

#include "gameNode.h"

class progresBar : public gameNode
{
private:
	RECT _rcProgress;
	int _x, _y;
	float _width;

	image* _progressBarFront;
	image* _progressBarBack;
public:
	progresBar();
	~progresBar();

	HRESULT Init(int x, int y, int width, int height);
	void Release();
	void Update();
	void Render();

	void SetGauge(float currentGauge, float maxGauge);

	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }
};

