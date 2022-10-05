#include "Piece.h"
#include "BasicSys.h"

Piece::Piece()
	: Object(TAG::PIECE)
	, m_Pos{}
	, m_Color(PIECE_COLOR::NONE)
{
}

Piece::~Piece()
{
}

Piece::Piece(POINT pos, PIECE_COLOR color)
	: Object(TAG::PIECE)
	, m_Pos(pos)
	, m_Color(color)
{
}

void Piece::Init()
{
}

void Piece::Update(float dt)
{
}

void Piece::Render(HDC hdc)
{
	HDC MemDC;
	HBITMAP MyBitmap, OldBitmap;
	MemDC = CreateCompatibleDC(hdc);

	MyBitmap = LoadBitmap(g_pEngine->GetInstanceHandle(), MAKEINTRESOURCE(m_Color));
	OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);

	BitBlt(hdc, m_Pos.x * RATIO + GAP, m_Pos.y * RATIO + GAP, RATIO - GAP, RATIO - GAP, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteObject(MyBitmap);
	DeleteDC(MemDC);
}

void Piece::Release()
{
}
