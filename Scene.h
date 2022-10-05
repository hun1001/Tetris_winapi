#ifndef SCENE_H

#define SCENE_H

#include "BasicStd.h"

class BScene
{
public:
	BScene() = default;
	~BScene() = default;

public:
	virtual		void Init() = 0;
	virtual		void Update(float dt) = 0;
	virtual		void Render(HDC hdc, float dt) = 0;
	virtual		void Release() = 0;
};

#endif // !SCENE_H

