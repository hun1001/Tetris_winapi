#include "BEngine.h"

//���� ���� ó��
BEngine* g_pEngine = nullptr;

BEngine::BEngine() : m_liPrevCount{}, m_liCurcount{}, m_liFrequency{}, m_fDT(0.0f), m_fAcc(0.0f), m_iCallCount(0), m_iFPS(0)
{
	//m_fLastTime =  m_fCurrTime = (float)timeGetTime()

	g_pEngine = this;

	m_SceneManager = new BSceneManager;

	//���� ī��Ʈ
	QueryPerformanceCounter(&m_liPrevCount);

	//�ʴ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_liFrequency);
}

BEngine::~BEngine()
{
	if (m_SceneManager)
		delete m_SceneManager;
}

/// <summary>
/// ��ġ�� �ʱ�ȭ
/// </summary>
void BEngine::StartUp()
{
	// ��ġ�� �ʱ�ȭ
	m_InputObject.Init();

	if (m_SceneManager)
		m_SceneManager->Init();

	Init();
}

/// <summary>
/// ���� ������ ��ũ ����
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

	// fps ���
	//_RenderText(fFrameDelta);
}

/// <summary>
/// ��ġ�� ����
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

	//������
	Render(hMemdc, dt);

	BitBlt(hdc, 0, 0, windowRect.right, windowRect.bottom, hMemdc, 0, 0, SRCCOPY);
	SelectObject(hMemdc, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hMemdc);
}

void BEngine::_RenderText(UINT fps, float dt)
{
	static TCHAR szTemp[256];
	swprintf_s(szTemp, TEXT("���� �ӵ� FPS: %d, �����Ӱ� ����: %f"), fps, dt);
	//wsprintf(szTemp, TEXT("���Ӽӵ� FPS : %d"), frameCount);
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
