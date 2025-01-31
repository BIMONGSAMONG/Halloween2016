#pragma once
#include "pch.h"
#include "Singleton.h"

class GameNode;
class SceneManager : public Singleton<SceneManager>
{
private:
	map<string, GameNode*>	mapSceneData;
	map<string, GameNode*>	mapLoadingSceneData;

public:
	static GameNode* currScene;		// ���� ��� ���� ��
	static GameNode* loadingScene;	// ���� �� �غ� �߿� ��µ� ��
	static GameNode* readyScene;	// �غ� ���� ��

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render();

	// �� �߰�
	GameNode* AddScene(string key, GameNode* scene);
	GameNode* AddLoadingScene(string key, GameNode* scene);

	// �� ü����
	HRESULT ChangeScene(string sceneName);
	HRESULT ChangeScene(string sceneName, string loadingSceneName);

	virtual ~SceneManager() {};
};

