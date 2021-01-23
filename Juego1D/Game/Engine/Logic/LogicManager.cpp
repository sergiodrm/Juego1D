#include "LogicManager.h"
#include "GameObjects/GameObject.h"

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
  for (CGameObject* pIterator : m_tGameObjects)
  {
    if (pIterator->IsActive())
      pIterator->Update(_fDeltaTime);
  }
}

void CLogicManager::AddGameObject(CGameObject& _rGameObject)
{
  m_tGameObjects.push_back(&_rGameObject);
}
