#pragma once
#include "GameNode.h"

class Ghost;
class GhostManager : public GameNode
{
private:
	vector<Ghost*> vecGhosts;
	vector<Ghost*>::iterator itGhosts;

	int cycleCount;
	int tempCycleCount;
	int spawnNum[20];
	int patternSize;
	POINT spawn[6];

	vector<int> indexNum;
	int checkDead;

	bool isClear;

	vector<Ghost*> uniqueGhosts;
	POINT uniSpawn[4];

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	vector<Ghost*> GetVecGhosts() { return vecGhosts; }
	bool GetIsClear() { return isClear; }

	vector<Ghost*> GetUniGhosts() { return uniqueGhosts; }

	int GetCycleCount() { return cycleCount; }
};

