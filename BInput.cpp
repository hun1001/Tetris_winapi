#include "BInput.h"

BInput::BInput()
{

}

BInput::~BInput()
{
}

void BInput::Init()
{
}

void BInput::Update()
{
}

void BInput::Release()
{
}

void BInput::KeyCheck(DWORD dwCheckKey, DWORD& dwStateKey)
{
	if (GetAsyncKeyState(dwCheckKey) & 0x8000) {
		if (dwStateKey == KEY_FREE)
			dwStateKey = KEY_PUSH;
		else
			dwStateKey = KEY_DOWN;
	}
	else {
		if (dwStateKey == KEY_PUSH || dwStateKey == KEY_DOWN)
			dwStateKey = KEY_UP;
		else
			dwStateKey = KEY_FREE;
	}
}

int BInput::ScanToASCII(DWORD scanCode, WORD* result)
{
	static HKL layout = GetKeyboardLayout(0);
	static BYTE State[256];

	if(GetKeyboardState(State) == FALSE)
		return 0;

	UINT vk = MapVirtualKeyEx(scanCode, 1, layout);
	return ToAsciiEx(vk, scanCode, State, result, 0, layout);
}

//WORD usValue;
// int iKey = ScanToASCII(VK_LBUTTON, &usValue);
