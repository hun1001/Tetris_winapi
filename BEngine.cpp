#include "BEngine.h"

//엔진 전역 처리
BEngine* g_pEngine = nullptr;

BEngine::BEngine() : m_liPrevCount{}, m_liCurcount{}, m_liFrequency{}, m_fDT(0.0f), m_fAcc(0.0f), m_iCallCount(0), m_iFPS(0)
{
	//m_fLastTime =  m_fCurrTime = (float)timeGetTime()

	g_pEngine = this;

	m_SceneManager = new BSceneManager;

	//현재 카운트
	QueryPerformanceCounter(&m_liPrevCount);

	//초당 카운트 횟수
	QueryPerformanceFrequency(&m_liFrequency);
}

BEngine::~BEngine()
{
	if (m_SceneManager)
		delete m_SceneManager;
}

/// <summary>
/// 장치의 초기화
/// </summary>
void BEngine::StartUp()
{
	// 장치의 초기화
	m_InputObject.Init();

	if (m_SceneManager)
		m_SceneManager->Init();

	Init();
}

/// <summary>
/// 게임 프레임 워크 구현
/// </summary>
void BEngine::MainLoop()
{
	QueryPerformanceCounter(&m_liCurcount);
	m_fDT = (float)(m_liCurcount.QuadPart - m_liPrevCount.QuadPart) / (float)(m_liFrequency.QuadPart);

	m_liPrevCount = m_liCurcount;

	m_iCallCount++;

	m_fAcc += m_fDT;

	if (m_fAcc >= 1.0f) {
		m_iFPS = m_iCallCount;
		m_iCallCount = 0;
		m_fAcc = 0.0f;

		_RenderText(m_iFPS, m_fDT);
	}


	_Update(m_fDT);

	HDC hdc = GetDC(m_hWnd);

	_Render(hdc, m_fDT);

	ReleaseDC(m_hWnd, hdc);

	// fps 출력
	//_RenderText(fFrameDelta);
}

/// <summary>
/// 장치의 종료
/// </summary>
void BEngine::CleanUp()
{
	m_InputObject.Release();

	if (m_SceneManager)
		m_SceneManager->Release();

	Release();
}

void BEngine::_Update(float dt)
{
	m_InputObject.Update();

	if (m_SceneManager)
		m_SceneManager->Update(dt);

	Update(dt);
}

void BEngine::_Render(HDC hdc, float dt)
{
	HDC hMemdc;
	RECT windowRect;
	HBITMAP hBitmap;

	GetClientRect(m_hWnd, &windowRect);

	hMemdc = CreateCompatibleDC(hdc);

	hBitmap = CreateCompatibleBitmap(hdc, windowRect.right, windowRect.bottom);

	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemdc, hBitmap);

	FillRect(hMemdc, &windowRect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	if (m_SceneManager)
		m_SceneManager->Render(hMemdc, dt);

	//렌더링
	Render(hMemdc, dt);

	BitBlt(hdc, 0, 0, windowRect.right, windowRect.bottom, hMemdc, 0, 0, SRCCOPY);
	SelectObject(hMemdc, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hMemdc);
}

void BEngine::_RenderText(UINT fps, float dt)
{
	static TCHAR szTemp[256];
	swprintf_s(szTemp, TEXT("게임 속도 FPS: %d, 프레임간 간격: %f"), fps, dt);
	//wsprintf(szTemp, TEXT("게임속도 FPS : %d"), frameCount);
	SetWindowTextW(m_hWnd, szTemp);
}

void BEngine::Init()
{
}

void BEngine::Update(float dt)
{
}

void BEngine::Render(HDC hdc, float dt)
{
}

void BEngine::Release()
{
}
