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
	int spawnNum[3];
	int patternSize;
	POINT spawn[6];

	vector<int> indexNum;
	int checkDead;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	vector<Ghost*> GetVecGhosts() { return vecGhosts; }
	//POINT *GetSpawn() { return spawn; }
};

