#ifndef BLOCK_H
#define BLOCK_H

#include "Object.h"
#include "BasicSys.h"

#define POINTNUM 4
#define DELAYTIME 1000

#define HANDLE_POSX		10
#define HANDLE_POSY		2
#define PREVIEW_POSX	18
#define PREVIEW_POSY	2

class Block : public Object
{
public:
	Block();
	Block(TETRIS_TYPE type, BLOCK_STATE state);
	~Block();

public:
	// Object을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

public:
	void SetState(BLOCK_STATE state)
	{
		m_State = state;
	}

	BLOCK_STATE GetState()
	{
		return m_State;
	}

	void SetType(TETRIS_TYPE type)
	{
		m_Type = type;
	}

	TETRIS_TYPE GetType()
	{
		return m_Type;
	}

	void SetCenter(POINT point)
	{
		m_Center = point;
	}

	void SetCenterX(const int x)
	{
		m_Center.x = x;
	}

	void SetCenterY(const int y)
	{
		m_Center.y = y;
	}

	int GetGlobalX(const int x)const;
	int GetGlobalY(const int y)const;

	void InitBlock(TETRIS_TYPE type);

	// 90도 회전
	void RightRotatePiece(LONG& x, LONG& y);
	void LeftRotatePiece(LONG& x, LONG& y);
	void RightRotateBlock();
	void LeftRotateBlock();

	bool IsRightRotateBlock(POINT pt[]);

	// 좌우 충돌 체크
	bool CheckOutOfLeft(const POINT center, const POINT pt[]);
	bool CheckOutOfRight(const POINT center, const POINT pt[]);

	// 충돌 체크
	bool ReachTheGround(const POINT center) const;
	bool CheckOutOfRange(const POINT center, const POINT pt[]) const;

	// 새로 그리기
	void RemoveBlockMakePiece();

private:
	POINT			m_Point[POINTNUM];  // 블록 상대 위치 좌표
	POINT			m_Center;			// 블록 중심 좌표
	PIECE_COLOR		m_Color;			// 블록 색상
	TETRIS_TYPE		m_Type;				// 블록 타입
	BLOCK_STATE		m_State;			// 블록 상태
	int				m_StartTime;
	int				m_DelayTime;

	TInputState		m_InputState;		// 블록 입력 처리
};


#endif // !BLOCK_H
