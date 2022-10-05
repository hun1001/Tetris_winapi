#ifndef BWINDOW_H
#define BWINDOW_H

#include "BasicStd.h"

class BWindow
{
public:
	BWindow();
	~BWindow();

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	// 윈도우 시작점
	int					Run(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);

private:

	void				registerWndClass();
	void				createWindow();
	void				showWindow(int nCmdShow);
	int					messageLoop();


public:
	virtual void		StartUp() = 0;
	virtual void		MainLoop() = 0;
	virtual void		CleanUp() = 0;

protected:
	HWND				m_hWnd;
	HINSTANCE			m_hInstance;

public:
	HWND				GetWndHandle();
	HINSTANCE			GetInstanceHandle();

};

#endif //!BWINDOW_H

