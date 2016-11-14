#pragma once
#include "GameBase.h"

class GameManager : public GameBase
{

private :

	ID2D1SolidColorBrush* ColorBrushbackbuffer;
	IDWriteFactory* WriteFactory;
	ID2D1Bitmap *backbuffer;

public:
	
	virtual HRESULT Initialize() override;
	virtual void Destory() override;
	virtual void Update() override;
	virtual void Render() override;

	GameManager();
	~GameManager();
};

