#ifndef PIECE_H
#define PIECE_H

#include "Object.h"

class Piece : public Object
{

private:
	POINT m_Pos;
	PIECE_COLOR m_Color;

public:
	Piece();
	Piece(POINT pos, PIECE_COLOR color);
	~Piece();

public:
	POINT GetPos()const {
		return m_Pos;
	}
	void SetPos(POINT pos) {
		m_Pos = pos;
	}

public:
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};




#endif // !PIECE_H
