#include "GameScene.h"
#include "ObjectManager.h"

GameScene::GameScene()
	//:piece(nullptr)
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	m_BackGround = LoadBitmap(g_pEngine->GetInstanceHandle(), MAKEINTRESOURCE(101));

	m_BGRect.left = MARGINCOLUM + GAP;
	m_BGRect.right = m_BGRect.left + BOARDSIZEX - GAP;
	m_BGRect.top = MARGINROW + GAP;
	m_BGRect.bottom = m_BGRect.top + BOARDSIZEY - GAP;

	m_PrevRect.left = MARGINCOLUM + BOARDSIZEX + RATIO;
	m_PrevRect.right = m_PrevRect.left + RATIO * 4;
	m_PrevRect.top = MARGINROW;
	m_PrevRect.bottom = m_PrevRect.top + RATIO * 4;

	m_GameStart = false;
	memset(&m_InputState, 0, sizeof(TInputState));

	ObjectManager::GetSingleton()->Init();
}

void GameScene::Update(float dt)
{
	if (ObjectManager::GetSingleton()->GetGameOver())
	{
		TCHAR str[128];
		wsprintf(str, TEXT("획득점수: %d"), ObjectManager::GetSingleton()->GetScore());
		
		if (MessageBox(g_pEngine->GetWndHandle(), TEXT("gameover"), TEXT("game"), MB_OK))
		{
			SendMessage(g_pEngine->GetWndHandle(), WM_DESTROY, 0, 0);
		}
		return;
	}

	g_pEngine->m_InputObject.KeyCheck(VK_RETURN, m_InputState.dwKeyReturn);

	if (m_InputState.dwKeyReturn == KEY_UP)
	{
		if (m_GameStart == false)
		{
			m_GameStart = true;
			ObjectManager::GetSingleton()->CreatePrevBlock();
			ObjectManager::GetSingleton()->CreateInGameBlock();
		}
	}	

	ObjectManager::GetSingleton()->Update(dt);

	// PIECE 삭제
	vector<Object*> gameObj = ObjectManager::GetSingleton()->GetGameObjectList();
	map<int, vector<Object*>> pieceInYaxis;
	
	for (size_t i = 0; i < gameObj.size(); ++i)
	{
		if (gameObj[i]->Gettag() == TAG::PIECE)
		{
			pieceInYaxis[dynamic_cast<Piece*>(gameObj[i])->GetPos().y].push_back(gameObj[i]);
		}
	}

	int fallYaxis = 0;
	for (auto it = pieceInYaxis.rbegin(); it != pieceInYaxis.rend(); ++it)
	{
		if ((*it).second.size() == (BOARDSIZEX / RATIO))
		{
			int score = ObjectManager::GetSingleton()->GetScore() + 10;
			ObjectManager::GetSingleton()->SetScore(score);

			for (auto piece : (*it).second)
			{
				fallYaxis = (*it).first;
				ObjectManager::GetSingleton()->RemoveObject(piece->Getid());
			}
			break;
		}
	}

	for (auto piece : pieceInYaxis)
	{
		if (piece.first < fallYaxis)
		{
			for (auto p : piece.second)
			{
				POINT pos = dynamic_cast<Piece*>(p)->GetPos();
				++pos.y;
				dynamic_cast<Piece*>(p)->SetPos(pos);
			}
		}
	}
}

void GameScene::Render(HDC hdc, float dt)
{
	HDC MemDC = CreateCompatibleDC(hdc);
	HBITMAP OldBitmap = (HBITMAP)SelectObject(MemDC, m_BackGround);
	BitBlt(hdc, 0, 0, WINSIZEX, WINSIZEY, MemDC, 0, 0, SRCCOPY);
	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);

	HBRUSH myBrush, oldBrush;
	myBrush = CreateSolidBrush(RGB(22, 23, 67));
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	Rectangle(hdc, m_BGRect.left, m_BGRect.top, m_BGRect.right, m_BGRect.bottom);

	Rectangle(hdc, m_PrevRect.left, m_PrevRect.top, m_PrevRect.right, m_PrevRect.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);

	HPEN myPen, oldPen;
	myPen = CreatePen(PS_SOLID, 1, RGB(41, 26, 109));
	oldPen = (HPEN)SelectObject(hdc, myPen);

	// 세로 선
	for (UINT i = 0; i <= 10; ++i)
	{
		MoveToEx(hdc, MARGINCOLUM + (RATIO * i), MARGINROW, nullptr);
		LineTo(hdc, MARGINCOLUM + (RATIO * i), MARGINROW + BOARDSIZEY);
	}

	for (UINT i = 0; i <= 20; ++i)
	{
		MoveToEx(hdc, MARGINCOLUM, MARGINROW + (RATIO*i), nullptr);
		LineTo(hdc, MARGINCOLUM+BOARDSIZEX, MARGINROW + (RATIO * i));
	}

	SelectObject(hdc, oldPen);
	DeleteObject(myPen);

	if (m_GameStart == false)
	{
		TextOut(hdc, 240, 300, TEXT("ENTER키를 누르면 시작합니다!"), 18);
	}

	WCHAR str[128];
	wsprintf(str, TEXT("score : %d"), ObjectManager::GetSingleton()->GetScore());
	TextOut(hdc, 90, 70, str, lstrlen(str));
	
	ObjectManager::GetSingleton()->Render(hdc);
}

void GameScene::Release()
{
	DeleteObject(m_BackGround);
	ObjectManager::GetSingleton()->Release();
}
