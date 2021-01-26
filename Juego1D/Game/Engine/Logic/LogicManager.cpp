#include "LogicManager.h"
#include "GameObjects/GameObject.h"
#include "World/World.h"

void CLogicManager::Init()
{
  CreateSingleton();
}

CLogicManager& CLogicManager::GetInstance()
{
  return GetSingleton();
}

void CLogicManager::Shutdown()
{
  DestroySingleton();
}

void CLogicManager::Update(float _fDeltaTime)
{
  /*for (size_t uIndex = 0; uIndex < CWorld::GetInstance().GetNumOfGameObjects(); ++uIndex)
  {
    CGameObject* pCurrentGameObject = CWorld::GetInstance().GetGameObjectByIndex(uIndex);
    pCurrentGameObject->Update(_fDeltaTime);
  }*/
}
