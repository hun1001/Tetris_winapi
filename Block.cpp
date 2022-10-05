#include "Block.h"
#include "ObjectManager.h"

Block::Block()
	:Object(TAG::BLOCK)
	, m_Center{}
	, m_Color(PIECE_COLOR::NONE)
	, m_Type(TETRIS_TYPE::I)
	, m_State(BLOCK_STATE::FROZEN)
	, m_StartTime(GetTickCount64())
	, m_DelayTime(DELAYTIME)
{
}

Block::Block(TETRIS_TYPE type, BLOCK_STATE state)
	:Object(TAG::BLOCK)
	, m_Center{}
	, m_Color(PIECE_COLOR::NONE)
	, m_Type(type)
	, m_State(state)
	, m_StartTime(GetTickCount64())
	, m_DelayTime(DELAYTIME)
{

	if (m_State == BLOCK_STATE::HANDLENOW)
	{
		m_Center.x = HANDLE_POSX;
		m_Center.y = HANDLE_POSY;
	}
	else if (m_State == BLOCK_STATE::PREVIEW)
	{
		m_Center.x = PREVIEW_POSX;
		m_Center.y = PREVIEW_POSY;
	}

	InitBlock(type);

	memset(&m_InputState, 0, sizeof(TInputState));
}

Block::~Block()
{
}

void Block::Init()
{
}

void Block::Update(float dt)
{
	if (m_State == BLOCK_STATE::HANDLENOW)
	{
		int currentTime = GetTickCount64();
		if (currentTime - m_StartTime >= m_DelayTime)
		{
			m_StartTime = currentTime;
			POINT temp{ m_Center.x, m_Center.y+1 };
			if (!ReachTheGround(m_Center) && !ObjectManager::GetSingleton()->CheckOverlapWithPiece(temp, m_Point))
			{
				++m_Center.y;
			}
		}

		g_pEngine->m_InputObject.KeyCheck(VK_UP, m_InputState.dwKeyUp);
		g_pEngine->m_InputObject.KeyCheck(VK_DOWN, m_InputState.dwKeyDown);
		g_pEngine->m_InputObject.KeyCheck(VK_LEFT, m_InputState.dwKeyLeft);
		g_pEngine->m_InputObject.KeyCheck(VK_RIGHT, m_InputState.dwKeyRight);
		g_pEngine->m_InputObject.KeyCheck(VK_SPACE, m_InputState.dwKeySpace);

		// 위쪽 키 눌렀을 때, (회전)
		if (m_InputState.dwKeyUp == KEY_PUSH)
		{
			if (m_Type != TETRIS_TYPE::O)
			{
				POINT point[POINTNUM];
				memcpy(point, m_Point, sizeof(point));
				if (!ReachTheGround(m_Center)
					&& !ObjectManager::GetSingleton()->CheckOverlapWithPiece(m_Center, m_Point))
				{
					RightRotateBlock();
				}
			}
		}

		// 아래키 눌렀을 때,
		if (m_InputState.dwKeyDown == KEY_PUSH)
		{
			POINT temp{ m_Center.x, m_Center.y + 1 };
			if (!ReachTheGround(m_Center) && !ObjectManager::GetSingleton()->CheckOverlapWithPiece(temp, m_Point))
			{
				++m_Center.y;
			}
		}

		// 왼쪽 키 눌렀을 때,
		if (m_InputState.dwKeyLeft == KEY_PUSH)
		{
			POINT temp{ m_Center.x - 1, m_Center.y };
			if (!CheckOutOfRange(temp, m_Point) && !ObjectManager::GetSingleton()->CheckOverlapWithPiece(temp, m_Point))
			{
				--m_Center.x;
			}
		}

		// 오른쪽 키 눌렀을 때,
		if (m_InputState.dwKeyRight == KEY_PUSH)
		{
			POINT temp{ m_Center.x + 1 , m_Center.y };
			if (!CheckOutOfRange(temp, m_Point) && !ObjectManager::GetSingleton()->CheckOverlapWithPiece(temp, m_Point))
			{
				++m_Center.x;
			}
		}

		// 한번에 내리기
		if (m_InputState.dwKeySpace == KEY_UP)
		{
			POINT temp{ m_Center.x , m_Center.y+1 };
			while (!ReachTheGround(m_Center) && !ObjectManager::GetSingleton()->CheckOverlapWithPiece(temp, m_Point))
			{
				++m_Center.y;
				temp.y = m_Center.y + 1;
			}
		}

		POINT temp{ m_Center.x , m_Center.y + 1 };
		if (ReachTheGround(m_Center) || ObjectManager::GetSingleton()->CheckOverlapWithPiece(temp, m_Point))
		{
			ULONGLONG currentTime = GetTickCount64();
			if (currentTime - m_StartTime >= 500)
			{
				m_StartTime = currentTime;
				RemoveBlockMakePiece();
			}
		}
	}
}

void Block::Render(HDC hdc)
{
	HDC MemDC;
	HBITMAP MyBitmap, OldBitmap;
	MemDC = CreateCompatibleDC(hdc);
	MyBitmap = LoadBitmap(g_pEngine->GetInstanceHandle(), MAKEINTRESOURCE(m_Color));
	OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);

	for (UINT i = 0; i < POINTNUM; ++i)
	{
		BitBlt(hdc, GetGlobalX(m_Point[i].x) * RATIO + GAP, GetGlobalY(m_Point[i].y) * RATIO + GAP, RATIO - GAP, RATIO - GAP,
			MemDC, 0, 0, SRCCOPY);
	}

	SelectObject(MemDC, OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);
}

void Block::Release()
{
}

int Block::GetGlobalX(const int x) const
{
	return m_Center.x + x;
}

int Block::GetGlobalY(const int y) const
{
	return m_Center.y + y;
}

void Block::InitBlock(TETRIS_TYPE type)
{
	switch (type)
	{
	case TETRIS_TYPE::I:
		m_Point[0].x = 0; m_Point[0].y = -1;
		m_Point[1].x = 0; m_Point[1].y =  1;
		m_Point[2].x = 0; m_Point[2].y =  2;
		m_Point[3].x = 0; m_Point[3].y =  0;
		m_Color = PIECE_COLOR::BLUE;
		break;
	case TETRIS_TYPE::O:
		m_Point[0].x =	0; m_Point[0].y = 1;
		m_Point[1].x = -1; m_Point[1].y = 1;
		m_Point[2].x = -1; m_Point[2].y = 0;
		m_Point[3].x =	0; m_Point[3].y = 0;
		m_Color = PIECE_COLOR::YELLOW;
		break;
	case TETRIS_TYPE::Z:
		m_Point[0].x = 1; m_Point[0].y = -1;
		m_Point[1].x = 1; m_Point[1].y =  0;
		m_Point[2].x = 0; m_Point[2].y =  1;
		m_Point[3].x = 0; m_Point[3].y =  0;
		m_Color = PIECE_COLOR::GREEN;
		break;
	case TETRIS_TYPE::S:
		m_Point[0].x = 0; m_Point[0].y = -1;
		m_Point[1].x = 1; m_Point[1].y =  0;
		m_Point[2].x = 1; m_Point[2].y =  1;
		m_Point[3].x = 0; m_Point[3].y =  0;
		m_Color = PIECE_COLOR::RED;
		break;
	case TETRIS_TYPE::J:
		m_Point[0].x = -1; m_Point[0].y = -1;
		m_Point[1].x = -1; m_Point[1].y =  0;
		m_Point[2].x =  1; m_Point[2].y =  0;
		m_Point[3].x =  0; m_Point[3].y =  0;
		m_Color = PIECE_COLOR::ORANGE;
		break;
	case TETRIS_TYPE::L:
		m_Point[0].x =  1; m_Point[0].y = -1;
		m_Point[1].x = -1; m_Point[1].y =  0;
		m_Point[2].x =  1; m_Point[2].y =  0;
		m_Point[3].x =  0; m_Point[3].y =  0;
		m_Color = PIECE_COLOR::WHITE;
		break;
	case TETRIS_TYPE::T:
		m_Point[0].x = -1; m_Point[0].y = 0;
		m_Point[1].x =  1; m_Point[1].y = 0;
		m_Point[2].x =  0; m_Point[2].y = 1;
		m_Point[3].x =  0; m_Point[3].y = 0;
		m_Color = PIECE_COLOR::PURPLE;
		break;
	default:
		break;
	}
}

void Block::RightRotatePiece(LONG& x, LONG& y)
{
	LONG temp = x;
	x = -y;
	y = temp;
}

void Block::LeftRotatePiece(LONG& x, LONG& y)
{
	LONG temp = x;
	x = y;
	y = -temp;
}

void Block::RightRotateBlock()
{
	for (UINT i = 0; i < POINTNUM; ++i)
	{
		RightRotatePiece(m_Point[i].x, m_Point[i].y);
	}
	
	while (CheckOutOfLeft(m_Center, m_Point))
	{
		++m_Center.x;
	}
	
	while (CheckOutOfRight(m_Center, m_Point))
	{
		--m_Center.x;
	}
}

void Block::LeftRotateBlock()
{
	for (UINT i = 0; i < POINTNUM; ++i)
	{
		LeftRotatePiece(m_Point[i].x, m_Point[i].y);
	}
}

bool Block::IsRightRotateBlock(POINT pt[])
{
	for (UINT i = 0; i < POINTNUM; ++i)
	{
		RightRotatePiece(pt[i].x, pt[i].y);
	}

	if (!CheckOutOfRange(m_Center, pt))
		return true;

	return false;
}

bool Block::CheckOutOfLeft(const POINT center, const POINT pt[])
{
	for (UINT i = 0; i < POINTNUM; ++i)
	{
		if (center.x + pt[i].x < (MARGINCOLUM/RATIO))
		{
			return true;
		}
	}
	return false;
}

bool Block::CheckOutOfRight(const POINT center, const POINT pt[])
{
	for (UINT i = 0; i < POINTNUM; ++i)
	{
		if (center.x + pt[i].x >= ((MARGINCOLUM + BOARDSIZEX) / RATIO))
		{
			return true;
		}
	}
	return false;
}

bool Block::ReachTheGround(const POINT center) const
{
	for (UINT i = 0; i < POINTNUM; ++i)
	{
		if (center.y + m_Point[i].y >= (MARGINROW + BOARDSIZEY) / RATIO - 1)
			return true;
	}
	return false;
}

bool Block::CheckOutOfRange(const POINT center, const POINT pt[]) const
{
	for (UINT i = 0; i < POINTNUM; ++i)
	{
		if (center.x + pt[i].x < MARGINCOLUM / RATIO || center.x + pt[i].x >= (MARGINCOLUM + BOARDSIZEX) / RATIO)
			return true;
	}
	return false;
}

void Block::RemoveBlockMakePiece()
{
	m_State = BLOCK_STATE::FROZEN;
	for (UINT i = 0; i < POINTNUM; ++i)
	{
		ObjectManager::GetSingleton()->RegisterObject(
			new Piece(POINT{ GetGlobalX(m_Point[i].x), GetGlobalY(m_Point[i].y) }, m_Color));
	}
	ObjectManager::GetSingleton()->RemoveObject(this->Getid());

	vector<Object*> gameObject = ObjectManager::GetSingleton()->GetGameObjectList();
	for (size_t i = 0; i < gameObject.size(); ++i)
	{
		if (gameObject[i]->Gettag() == TAG::BLOCK)
		{
			if (dynamic_cast<Block*>(gameObject[i])->GetState() == BLOCK_STATE::PREVIEW)
			{
				POINT pos{ HANDLE_POSX, HANDLE_POSY };
				
				if (ObjectManager::GetSingleton()->CheckOverlapWithPiece(pos, m_Point) == true)
				{
					ObjectManager::GetSingleton()->SetGameOver(true);
					return;
				}
				
				dynamic_cast<Block*>(gameObject[i])->SetState(BLOCK_STATE::HANDLENOW);
				dynamic_cast<Block*>(gameObject[i])->SetCenter(pos);
			}
		}
	}

	ObjectManager::GetSingleton()->CreatePrevBlock();
}
