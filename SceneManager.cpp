#include "SceneManager.h"
using namespace std;
BSceneManager::BSceneManager()
{
	m_ReservedScene = nullptr;
	m_CurrentScene = nullptr;

}

BSceneManager::~BSceneManager()
{
	for (auto it = m_SceneContainer.begin(); it != m_SceneContainer.end(); ++it) {
		it->second->Release();
		delete it->second;
	}
}

void BSceneManager::Init()
{
}

void BSceneManager::Update(float dt)
{
	if (m_ReservedScene) {
		if (m_CurrentScene) {
			m_CurrentScene->Release();
		}
		m_ReservedScene->Init();

		m_CurrentScene = m_ReservedScene;
		m_ReservedScene = nullptr;
	}

	if(m_CurrentScene)
		m_CurrentScene->Update(dt);
}

void BSceneManager::Render(HDC hdc, float dt)
{
	if (m_CurrentScene)
		m_CurrentScene->Render(hdc, dt);
}

void BSceneManager::Release()
{
}

// ¾À µî·Ï
void BSceneManager::RegisterScene(const string& sceneName, BScene* scene)
{
	if (scene == nullptr || sceneName.compare("") == 0) return;

	//scene->Init();

	m_SceneContainer.insert(m_SceneContainer.end(), pair<string, BScene*>(sceneName, scene));
}

// ¿¹¾à ¾À ÀüÈ¯
void BSceneManager::ReserveChangeScene(const string& sceneName)
{
	auto it = m_SceneContainer.find(sceneName);

	if (it != m_SceneContainer.end()) {
		m_ReservedScene = it->second;
	}
	else {
		m_ReservedScene = nullptr;
	}
}

