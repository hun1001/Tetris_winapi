#ifndef SCENEMANAGER_H
#define SCENEMANANGER_H

#include "Scene.h"

class BSceneManager
{
public:
	BSceneManager();
	~BSceneManager();

public:
	void		Init();
	void		Update(float dt);
	void		Render(HDC hdc, float dt);
	void		Release();

public:
	void		RegisterScene(const std::string& sceneName, BScene* scene);
	void		ReserveChangeScene(const std::string& sceneName);

private:
	std::map<std::string, BScene*> m_SceneContainer;

	BScene* m_ReservedScene;
	BScene* m_CurrentScene;
};

#endif // !SCENEMANAGER_H


