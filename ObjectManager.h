#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "Singleton.h"
#include "Piece.h"
#include "Block.h"

class ObjectManager : public Singleton<ObjectManager>
{
private:
	int					m_Score;
	bool				m_IsGameOver;
	int					m_Instance_ID;
	vector<Object*>		m_ObjectList;

public:
	ObjectManager();
	~ObjectManager();

public:
	void Init();
	void Update(float dt);
	void Render(HDC hdc);
	void Release();

public:
	int GetObejctSize()
	{
		return (int)m_ObjectList.size();
	}

	int GetScore()
	{
		return m_Score;
	}

	void SetScore(int score)
	{
		m_Score = score;
	}

	bool GetGameOver()
	{
		return m_IsGameOver;
	}

	void SetGameOver(bool gameOver)
	{
		m_IsGameOver = gameOver;
	}

	vector<Object*> GetGameObjectList()
	{
		return m_ObjectList;
	}

public:
	void RegisterObject(Object* object);
	void RemoveObject(int id);

	void CreatePrevBlock();
	void CreateInGameBlock();

	bool CheckOverlapWithPiece(const POINT center, const POINT pt[]) const;
};

#endif // OBJECTMANAGER_H

