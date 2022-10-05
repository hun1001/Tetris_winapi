#ifndef OBJECT_H
#define OBJECT_H

#include "BasicStd.h"

class Object
{
public:
	Object()
		: id(-1)
		, tag(TAG::NOT)
	{}
	Object(TAG _tag)
		:id(-1)
		, tag(_tag)
	{

	}
	~Object()
	{}
	
public:
	void Setid(const int _id) { id = _id; }
	int Getid() { return id; }

	void Settag(TAG _tag) { tag = _tag; }
	TAG Gettag() { return tag; }

public:
	virtual void Init() {}
	virtual void Update(float dt) {}
	virtual void Render(HDC hdc) {}
	virtual void Release() {} 
private:
	int id;
	TAG tag;
};



#endif // !OBJECT_H
