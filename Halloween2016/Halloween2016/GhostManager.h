#pragma once
#include "GameNode.h"

class Ghost;
class GhostManager : public GameNode
{
private:
	vector<Ghost*> vecGhosts;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

