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
	// Object��(��) ���� ��ӵ�
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

	// 90�� ȸ��
	void RightRotatePiece(LONG& x, LONG& y);
	void LeftRotatePiece(LONG& x, LONG& y);
	void RightRotateBlock();
	void LeftRotateBlock();

	bool IsRightRotateBlock(POINT pt[]);

	// �¿� �浹 üũ
	bool CheckOutOfLeft(const POINT center, const POINT pt[]);
	bool CheckOutOfRight(const POINT center, const POINT pt[]);

	// �浹 üũ
	bool ReachTheGround(const POINT center) const;
	bool CheckOutOfRange(const POINT center, const POINT pt[]) const;

	// ���� �׸���
	void RemoveBlockMakePiece();

private:
	POINT			m_Point[POINTNUM];  // ��� ��� ��ġ ��ǥ
	POINT			m_Center;			// ��� �߽� ��ǥ
	PIECE_COLOR		m_Color;			// ��� ����
	TETRIS_TYPE		m_Type;				// ��� Ÿ��
	BLOCK_STATE		m_State;			// ��� ����
	int				m_StartTime;
	int				m_DelayTime;

	TInputState		m_InputState;		// ��� �Է� ó��
};


#endif // !BLOCK_H
