#include "World.h"
#include "Logic/LogicManager.h"
#include "Render/RenderEngine.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Derived/TransformComponent.h"
#include "GameObjects/Components/Derived/MovementComponent.h"
#include "GameObjects/Components/Derived/AttackComponent.h"
#include "GameObjects/Components/Derived/RenderComponent.h"
#include "Timer/TimeManager.h"

void CWorld::Init()
{
  CreateSingleton();
  GetSingleton().Init_Internal();
}

CWorld& CWorld::GetInstance()
{
  return GetSingleton();
}


void CWorld::Update()
{
  CTimeManager::GetInstance().InitTimerToProcess();
  while (CTimeManager::GetInstance().Update())
  {
    UpdateGameObjects(static_cast<float>(CTimeManager::GetInstance().GetFixedTick()));
  }
}

void CWorld::DrawWorld()
{
  GetInstance().DrawWorld_Internal();
}

void CWorld::DrawWorld_Internal()
{
  m_scene.Render();
}

void CWorld::Shutdown()
{
  GetSingleton().Shutdown_Internal();
  DestroySingleton();
}

void CWorld::InsertGameObject(CGameObject& _rGameObject)
{
  m_tGameObjects.emplace_back(&_rGameObject);
}

bool CWorld::SpawnGameObject(SSpawnInfo& _rSpawnInfo)
{
  CGameObject* pSpawnedGameObject = FindGameObjectByType(_rSpawnInfo.m_eType, false);
  if (pSpawnedGameObject == nullptr)
    return false;
  // @TODO
  pSpawnedGameObject->GetComponent<CTransformComponent>()->SetPosition(_rSpawnInfo.m_iPosition);
  pSpawnedGameObject->GetComponent<CMovementComponent>()->SetMovementDirection(_rSpawnInfo.m_iDirection);
  pSpawnedGameObject->GetComponent<CRenderComponent>()->SetSymbol(_rSpawnInfo.m_cSymbol);
  pSpawnedGameObject->Active();
  return true;
}

CScene& CWorld::GetScene()
{
  return m_scene;
}

void CWorld::Init_Internal()
{
  /**
   * Init vars
   */
  m_iNumberOfBullets = 5;
  m_iNumberOfEnemies = 10;

  /**
   * Init player
   */
  {
    CGameObject* pPlayer = CGameObject::Create();
    pPlayer->SetType(CGameObject::EGameObjectTypes::Player);
    CRenderComponent* pRenderComponent = pPlayer->AddComponent<CRenderComponent>();
    pRenderComponent->SetSymbol('X');
    CMovementComponent* pMovementComponent = pPlayer->AddComponent<CMovementComponent>();
    pMovementComponent->SetInputPlayerEnable(true);
    pPlayer->AddComponent<CAttackComponent>();
    pPlayer->Active();
  }

  /**
   * Init bullets
   */
  {
    for (int iIndex = 0; iIndex < m_iNumberOfBullets; ++iIndex)
    {
      CGameObject* pBullet = CGameObject::Create();
      pBullet->SetType(CGameObject::EGameObjectTypes::Bullet);
      pBullet->AddComponent<CRenderComponent>();
      CMovementComponent* pMovementComponent = pBullet->AddComponent<CMovementComponent>();
      pMovementComponent->SetInputPlayerEnable(false);
      pBullet->Deactive();
    }
  }

  /**
   * Init enemies
   */
  {
    for (int iIndex = 0; iIndex < m_iNumberOfEnemies; ++iIndex)
    {
      CGameObject* pEnemy = CGameObject::Create();
      pEnemy->SetType(CGameObject::EGameObjectTypes::Enemy);
      CRenderComponent* pRenderComponent = pEnemy->AddComponent<CRenderComponent>();
      pRenderComponent->SetSymbol('*');
      CMovementComponent* pMovementComponent = pEnemy->AddComponent<CMovementComponent>();
      pMovementComponent->SetInputPlayerEnable(false);
      pEnemy->Deactive();
    }
  }

  /**
   * Init map
   */
  
  /**
   * Bind raw draw callback to render engine to draw the scene
   */
  CRenderEngine::GetInstance().SetDrawWorldFunction(&CWorld::DrawWorld);

  /**
   * Init timer
   */
  CTimeManager::Init();

  /**
   * @TODO: Implement a complete active/deactive logic in game objects (including components and derived).
   * @TODO: Garbage collector to avoid memory leaks.
   * @TODO: Spawn bullets logic from Scene and handle without change game object vector.
   * @TODO: Include time manager in game.
   * @TODO: Collision component.
   * @TODO: Life component.
   */
}

void CWorld::UpdateGameObjects(float _fDeltaTime)
{
  for (CGameObject* pIterator : m_tGameObjects)
  {
    pIterator->Update(_fDeltaTime);
  }
}

void CWorld::Shutdown_Internal()
{
  CTimeManager::Shutdown();

  /**
   * Destroy all game objects
   */
  for (CGameObject* pIterator : m_tGameObjects)
  {
    CGameObject::Destroy(pIterator);
  }
}

CGameObject* CWorld::FindGameObjectByType(CGameObject::EGameObjectTypes _eType, bool _bIsActive)
{
  for (CGameObject* pIterator : m_tGameObjects)
  {
    if (pIterator->IsActive() == _bIsActive && pIterator->IsType(_eType))
      return pIterator;
  }
  return nullptr;
}

