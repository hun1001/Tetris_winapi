#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	m_Score = 0;
	m_IsGameOver = false;
	m_Instance_ID = 0;
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Init()
{
	for (size_t i = 0; i < m_ObjectList.size(); ++i)
		m_ObjectList[i]->Init();
}

void ObjectManager::Update(float dt)
{
	for (size_t i = 0; i < m_ObjectList.size(); ++i)
		m_ObjectList[i]->Update(dt);
}

void ObjectManager::Render(HDC hdc)
{
	for (size_t i = 0; i < m_ObjectList.size(); ++i)
		m_ObjectList[i]->Render(hdc);
}

void ObjectManager::Release()
{
	for (size_t i = 0; i < m_ObjectList.size(); ++i)
		m_ObjectList[i]->Release();
}

void ObjectManager::RegisterObject(Object* object)
{
	object->Setid(m_Instance_ID++);
	m_ObjectList.push_back(object);
}

void ObjectManager::RemoveObject(int id)
{
	for (size_t i = 0; i < m_ObjectList.size(); ++i)
	{
		if (m_ObjectList[i]->Getid() == id)
		{
			m_ObjectList.erase(m_ObjectList.begin() + i);
			break;
		}
	}
}

void ObjectManager::CreatePrevBlock()
{
	TETRIS_TYPE random = static_cast<TETRIS_TYPE>(rand() % 7);
	Block* block = new Block(random, BLOCK_STATE::PREVIEW);

	RegisterObject(block);
}

void ObjectManager::CreateInGameBlock()
{
	TETRIS_TYPE random = static_cast<TETRIS_TYPE>(rand() % 7);
	Block* block = new Block(random, BLOCK_STATE::HANDLENOW);

	RegisterObject(block);
}

bool ObjectManager::CheckOverlapWithPiece(const POINT center, const POINT pt[]) const
{
	vector<Object*> pieces;
	for (size_t i = 0; i < m_ObjectList.size(); ++i)
	{
		if (m_ObjectList[i]->Gettag() == TAG::PIECE)
		{
			pieces.push_back(m_ObjectList[i]);
		}
	}
	
	for (size_t i = 0; i < pieces.size(); ++i)
	{
		for (int j = 0; j < POINTNUM; ++j)
		{
			if (dynamic_cast<Piece*>(pieces[i])->GetPos().x == (center.x + pt[j].x) &&
				dynamic_cast<Piece*>(pieces[i])->GetPos().y == (center.y + pt[j].y))
				return true;
		}
	}
	return false;
}
