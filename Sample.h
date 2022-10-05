#include "BEngine.h"

class Sample : public BEngine
{
public:
	Sample();
	~Sample();
	
public:
	virtual void		Init() override;
	virtual void		Update(float dt) override;
	virtual void		Render(HDC hdc, float dt) override;
	virtual void		Release() override;

//private:
//	BImage				m_BitmapFile;
//	TInputState			m_InputState;
//
//private:
//	float					m_posX;
//	float					m_posY;
//	float				m_moveSpeed;
};

