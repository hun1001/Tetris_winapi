#ifndef BINPUT_H

#define BINPUT_H

#include "BasicStd.h"

enum KEYSTATE {
	KEY_FREE = 0,
	KEY_PUSH,
	KEY_UP,
	KEY_DOWN,
	KEY_HOLD
};

struct TInputState {
	DWORD dwKeyUp;
	DWORD dwKeyDown;
	DWORD dwKeyLeft;
	DWORD dwKeyRight;

	DWORD dwKeySpace;
	DWORD dwKeyReturn;

	DWORD dwMouseLB;
};

class BInput
{
public:
	BInput();
	~BInput();
public:
	void		Init();
	void		Update();
	void		Release();

	void		KeyCheck(DWORD dwCheckKey, DWORD& dwStateKey);
	int			ScanToASCII(DWORD scanCode, WORD* result);

};
#endif // !BINPUT_H

