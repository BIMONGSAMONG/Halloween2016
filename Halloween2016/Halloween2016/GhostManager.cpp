#include "GhostManager.h"
#include "Ghost.h"

HRESULT GhostManager::Init()
{
	vecGhosts.reserve(6);
	for (int i = 0; i < 6; i++)
	{
		vecGhosts.push_back(new Ghost());
		vecGhosts[i]->Init();
	}

	for (int i = 0; i < 6; i++)
	{
		if (i < 3)
		{
			spawn[i] = { 0 , 250 + (i * 200) }; // 왼쪽
		}
		else
		{
			spawn[i] = { WINSIZE_X , 250 + ((i % 3) * 200) }; // 오른쪽
		}
	}
	
	cycleCount = 0;
	tempCycleCount = 0;
	spawnNum[0] = 1;

	indexNum.reserve(vecGhosts.size());
	for (int i = 0; i < vecGhosts.size(); i++)
	{
		indexNum.push_back(i);
	}

	srand(time(NULL));

	for (int i = 1; i < 20; i++)
	{
		spawnNum[i] = rand() % 6 + 1;
	}
	
	patternSize = 0;

	isClear = false;
	isDeadOneCycle = false;

	uniqueGhosts.reserve(1);
	uniqueGhosts.push_back(new Ghost());
	uniqueGhosts[0]->Init();

	for (int i = 0; i < 4; i++)
	{
		if (i < 2) // 하트
		{
			uniSpawn[i] = { (WINSIZE_X * i) + 150 - (i * 300), WINSIZE_Y / 2 };
		}
		else // 번개
		{
			uniSpawn[i] = {WINSIZE_X / 2 - 100 +((i-2) * 200), WINSIZE_Y + 200};
		}
	}

	return S_OK;
}

void GhostManager::Release()
{
	for (itGhosts = vecGhosts.begin(); itGhosts != vecGhosts.end(); itGhosts++)
	{
		(*itGhosts)->Release();
		delete (*itGhosts);
	}
	vecGhosts.clear();
	indexNum.clear();
	uniqueGhosts.clear();
}

void GhostManager::Update()
{
	srand(time(NULL));

	for (int i = 0; i < vecGhosts.size(); i++)
	{
		if ((vecGhosts[i]->GetState() == State::idle) && (vecGhosts[i]->GetAlpha() <= 0))
		{
			patternSize = rand() % 3 + 1;

			for (int j = 0; j < patternSize; j++)
			{
				if (vecGhosts[i]->GetPattern().size() < 4)
				{
					vecGhosts[i]->SetPattern(rand() % 4);
				}
			}
			vecGhosts[i]->SetTempSize(vecGhosts[i]->GetPattern().size());
			vecGhosts[i]->SetPos(spawn[i]);

		}

		vecGhosts[i]->Update();
	}

	if (cycleCount == tempCycleCount)
	{
		tempCycleCount++;

		for (int k = 0; k < vecGhosts.size() - spawnNum[cycleCount]; k++)
		{
			int randomNum = rand() % indexNum.size();
			vecGhosts[indexNum[randomNum]]->SetState(State::Dead);
			indexNum.erase(indexNum.begin() + randomNum);
		}
		indexNum.clear();
		for (int n = 0; n < vecGhosts.size(); n++)
		{
			indexNum.push_back(n);
		}
	}

	if (cycleCount < 20)
	{
		checkDead = 0;
		for (int l = 0; l < vecGhosts.size(); l++)
		{
			if (vecGhosts[l]->GetState() == State::Dead)
			{
				checkDead++;

				if (checkDead == vecGhosts.size())
				{
					for (int m = 0; m < vecGhosts.size(); m++)
					{
						vecGhosts[m]->SetState(State::idle);
					}
					cycleCount++;
					tempCycleCount = cycleCount;
				}
			}			
		}
	}
	else
	{
		checkDead = 0;
		for (int l = 0; l < vecGhosts.size(); l++)
		{
			if (vecGhosts[l]->GetState() == State::Dead)
			{
				checkDead++;

				if (checkDead == vecGhosts.size())
				{
					isClear = true;
				}
			}
		}
	}
	
	if ((cycleCount % 3 == 0) /*&& cycleCount != 0*/)
	{
		for (int i = 0; i < uniqueGhosts.size(); i++)
		{
			if ((uniqueGhosts[i]->GetState() == State::idle) && (uniqueGhosts[i]->GetAlpha() <= 0))
			{
					int randNum = rand() % 2 + 4;
					uniqueGhosts[i]->SetPattern(randNum);
					uniqueGhosts[i]->SetTempSize(uniqueGhosts[i]->GetPattern().size());

					if (randNum == 4)
					{
						uniqueGhosts[i]->SetPos(uniSpawn[rand() % 2 + 2]);
						uniqueGhosts[i]->SetIsCat(false);
					}
					else
					{
						uniqueGhosts[i]->SetPos(uniSpawn[rand() % 2]);
						uniqueGhosts[i]->SetIsCat(true);
					}

			}
			uniqueGhosts[i]->Update();
		}
	}
	else
	{
		for (int i = 0; i < uniqueGhosts.size(); i++)
		{
			/*uniqueGhosts[i]->SetState(State::Dead);
			uniqueGhosts[i]->GetPattern().clear();*/
			uniqueGhosts[i]->SetState(State::idle);
		}
	}
	

}


void GhostManager::Render()
{
	for (itGhosts = vecGhosts.begin(); itGhosts != vecGhosts.end(); itGhosts++)
	{
		(*itGhosts)->Render();
	}
	if ((cycleCount % 3 == 0) /*&& cycleCount != 0*/)
	{
		for (itGhosts = uniqueGhosts.begin(); itGhosts != uniqueGhosts.end(); itGhosts++)
		{
			(*itGhosts)->Render();
		}
	}
	
}
