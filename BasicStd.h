#ifndef BasicStd
#define BasicStd


// --------------------------------------
// Name : BasicStd
// Desc : 기본적으로 사용되는 헤더, 디파인
//---------------------------------------

#include <Windows.h>
#include <math.h>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <ctime>
#include <algorithm>

#define PI			3.1415926535

#define BOARDSIZEX	300
#define BOARDSIZEY	600
#define MARGINROW	30		// 행 여백
#define MARGINCOLUM	180		// 열 여백
#define RATIO		30		// 그릴 배율
#define GAP			1		// 판 내부 조정 값

#define WINSIZEX	(BOARDSIZEX + MARGINCOLUM * 2 )
#define WINSIZEY	(BOARDSIZEY + MARGINROW * 2 + 32)

#pragma comment(lib, "winmm.lib")

using namespace std;

enum class TAG {
	NOT,
	PIECE,
	BLOCK,
};

enum class PIECE_COLOR
{
	NONE = 0,
	BLUE = 102,
	GRAY,
	GREEN,
	GUIDE,
	ORANGE,
	PURPLE,
	RED,
	WHITE,
	YELLOW,
};

enum class TETRIS_TYPE
{
	I,	//긴 작대기
	O,	//네모
	Z,	//왼쪽 ㄹ
	S,	//오른쪽 ㄹ
	J,	//왼쪽 ㄴ
	L,	//오른쪽 ㄴ
	T,	//ㅗ
	
};

enum class BLOCK_STATE
{
	PREVIEW,
	HANDLENOW,
	FROZEN
};

#endif // !BasicStd
