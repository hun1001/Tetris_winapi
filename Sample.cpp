#include "Sample.h"
#include "GameScene.h"

Sample::Sample()
{
    srand((UINT)time(nullptr));
}

Sample::~Sample()
{
}

void Sample::Init()
{

    if (m_SceneManager) {
        m_SceneManager->RegisterScene("gamescene", new GameScene);

        m_SceneManager->ReserveChangeScene("gamescene");
    }
    
}

void Sample::Update(float dt)
{

    
}

void Sample::Render(HDC hdc, float dt)
{
}

void Sample::Release()
{
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    Sample sampleEngine;

    sampleEngine.Run(hInstance, lpCmdLine, nCmdShow);

    return 0;
}
