#ifndef BENGINE_H
#define BENGINE_H

#include "BWindow.h"
#include "BImage.h"
#include "BInput.h"
#include "SceneManager.h"

class BEngine : public BWindow
{
public:
	BEngine();
	~BEngine();

public:
	virtual void		StartUp() override;
	virtual void		MainLoop() override;
	virtual void		CleanUp() override;

private:
	void				_Update(float dt);
	void				_Render(HDC hdc, float dt);
	void				_RenderText(UINT fps, float dt);

public:
	virtual void		Init();
	virtual void		Update(float dt);
	virtual void		Render(HDC hdc, float dt);
	virtual void		Release();

private:
	LARGE_INTEGER		m_liPrevCount;
	LARGE_INTEGER		m_liCurcount;
	LARGE_INTEGER		m_liFrequency;

	float				m_fDT;			//프레임간 시간값(FrameDeltaTime)
	float				m_fAcc;			//1초 체크를 위한 누적 시간
	UINT				m_iCallCount;	//함수 호출 횟수 체크
	UINT				m_iFPS;
public:
	BInput				m_InputObject;
	BSceneManager*		m_SceneManager;
};

#endif // !BENGINE_H



