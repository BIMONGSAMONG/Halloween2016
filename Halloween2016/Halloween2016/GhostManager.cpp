#include "GhostManager.h"
#include "Ghost.h"

HRESULT GhostManager::Init()
{
	vecGhosts.reserve(8);
	for (int i = 0; i < 8; i++)
	{
		vecGhosts.push_back(new Ghost);
		vecGhosts[i]->Init();
	}
	return S_OK;
}

void GhostManager::Release()
{
}

void GhostManager::Update()
{
}

void GhostManager::Render()
{
}
