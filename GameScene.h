#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Piece.h"
#include "Block.h"

class GameScene : public BScene
{
public:
	GameScene();
	~GameScene();

public:
	//BScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(HDC hdc, float dt) override;
	virtual void Release() override;

private:
	bool		m_GameStart;
	TInputState	m_InputState;

private:
	HBITMAP m_BackGround;
	RECT	m_BGRect;
	RECT	m_PrevRect;

};

#endif // !GAMESCENE_H
