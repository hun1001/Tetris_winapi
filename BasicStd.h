#ifndef BasicStd
#define BasicStd


// --------------------------------------
// Name : BasicStd
// Desc : �⺻������ ���Ǵ� ���, ������
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
#define MARGINROW	30		// �� ����
#define MARGINCOLUM	180		// �� ����
#define RATIO		30		// �׸� ����
#define GAP			1		// �� ���� ���� ��

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
	I,	//�� �۴��
	O,	//�׸�
	Z,	//���� ��
	S,	//������ ��
	J,	//���� ��
	L,	//������ ��
	T,	//��
	
};

enum class BLOCK_STATE
{
	PREVIEW,
	HANDLENOW,
	FROZEN
};

#endif // !BasicStd
