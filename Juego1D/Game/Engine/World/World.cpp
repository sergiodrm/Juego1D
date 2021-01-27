#include "World.h"
#include "Logic/LogicManager.h"
#include "Render/RenderEngine.h"
#include "UI/UIManager.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Derived/TransformComponent.h"
#include "GameObjects/Components/Derived/MovementComponent.h"
#include "GameObjects/Components/Derived/AttackComponent.h"
#include "GameObjects/Components/Derived/RenderComponent.h"
#include "GameObjects/Components/Derived/CollisionComponent.h"
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
    EnemySpawnerSlot(static_cast<float>(CTimeManager::GetInstance().GetFixedTick()));
    UpdateGameObjects(static_cast<float>(CTimeManager::GetInstance().GetFixedTick()));
    ResolveCollisions();
    ResolveGameObjectsActivation();
  }
}

void CWorld::DrawWorld()
{
  GetInstance().DrawWorld_Internal();
}

void CWorld::DrawWorld_Internal()
{
  m_scene.Render();
  CUIManager::GetInstance().Render();
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
  if (!CheckValidSpawn(_rSpawnInfo))
  {
    return false;
  }
  CGameObject* pSpawnedGameObject = FindGameObjectByType(_rSpawnInfo.m_eType, false);
  if (pSpawnedGameObject == nullptr)
  {
    return false;
  }
  pSpawnedGameObject->GetComponent<CTransformComponent>()->SetPosition(_rSpawnInfo.m_iPosition);
  pSpawnedGameObject->GetComponent<CMovementComponent>()->SetMovementDirection(_rSpawnInfo.m_iDirection);
  pSpawnedGameObject->GetComponent<CRenderComponent>()->SetSymbol(_rSpawnInfo.m_cSymbol);
  ActiveGameObject(*pSpawnedGameObject);
  return true;
}

void CWorld::ActiveGameObject(CGameObject& _rGameObject)
{
  m_gameObjectsToActive.push(&_rGameObject);
}
void CWorld::DeactiveGameObject(CGameObject& _rGameObject)
{
  m_gameObjectsToDeactive.push(&_rGameObject);
}

CScene& CWorld::GetScene()
{
  return m_scene;
}

bool CWorld::GameOver() const
{
  CGameObject* pPlayer = FindGameObjectByType(CGameObject::EGameObjectTypes::Player, true);
  return pPlayer == nullptr;
}

void CWorld::Init_Internal()
{
  /**
   * Init vars
   */
  m_iNumberOfBullets = 10;
  m_iNumberOfEnemies = 10;
  m_fTimeUntilNextSpawn = 0.f;
  m_fEnemySpawnProb = 0.4f;
  m_fTimeBetweenEnemySpawn = 2.f;

  /**
   * Init player
   */
  {
    CGameObject* pPlayer = CGameObject::Create();
    pPlayer->SetType(CGameObject::EGameObjectTypes::Player);
    pPlayer->GetComponent<CTransformComponent>()->SetPosition(static_cast<int>(GetScene().GetSize()) / 2);
    CRenderComponent* pRenderComponent = pPlayer->AddComponent<CRenderComponent>();
    pRenderComponent->SetSymbol('X');
    CMovementComponent* pMovementComponent = pPlayer->AddComponent<CMovementComponent>();
    pMovementComponent->SetInputPlayerEnable(true);
    CCollisionComponent* pCollisionComponent = pPlayer->AddComponent<CCollisionComponent>();
    pCollisionComponent->SetTypeToIgnore(CGameObject::EGameObjectTypes::Bullet);
    pPlayer->AddComponent<CAttackComponent>();
    ActiveGameObject(*pPlayer);
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
      pMovementComponent->SetSpeed(5.f);
      CCollisionComponent* pCollisionComponent = pBullet->AddComponent<CCollisionComponent>();
      pCollisionComponent->SetTypeToIgnore(CGameObject::EGameObjectTypes::Player);
      DeactiveGameObject(*pBullet);
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
      CCollisionComponent* pCollisionComponent = pEnemy->AddComponent<CCollisionComponent>();
      pCollisionComponent->SetTypeToIgnore(CGameObject::EGameObjectTypes::Enemy);
      DeactiveGameObject(*pEnemy);
    }
  }

  /**
   * Bind raw draw callback to render engine to draw the scene
   */
  CRenderEngine::GetInstance().SetDrawWorldFunction(&CWorld::DrawWorld);

  /**
   * Init timer
   */
  CTimeManager::Init();

  /**
   * Init ui manager
   */
  CUIManager::Init();

  ResolveGameObjectsActivation();
}

void CWorld::EnemySpawnerSlot(float _fDeltaTime)
{
  // Lambda to get a random number between 0.f and 1.f
  auto RandLambda = []() -> float
  {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  };

  if (m_fTimeUntilNextSpawn == 0.f)
  {
    // Roll dice
    float fDice = RandLambda();
    if (fDice <= m_fEnemySpawnProb)
    {
      float fRandomSpawnSide = RandLambda();
      int iDirection = 1;
      if (fRandomSpawnSide < 0.5f)
      {
        iDirection = -1;
      }
      SSpawnInfo enemySpawnInfo;
      enemySpawnInfo.m_cSymbol = '*';
      enemySpawnInfo.m_eType = CGameObject::EGameObjectTypes::Enemy;
      enemySpawnInfo.m_iDirection = iDirection;
      enemySpawnInfo.m_iPosition = iDirection == 1 ? 0 : static_cast<int>(GetScene().GetSize()) - 1;
      SpawnGameObject(enemySpawnInfo);
      m_fTimeUntilNextSpawn = m_fTimeBetweenEnemySpawn;
    }
  }
  else
  {
    m_fTimeUntilNextSpawn -= _fDeltaTime;
    if (m_fTimeUntilNextSpawn < 0.f)
      m_fTimeUntilNextSpawn = 0.f;
  }
}

void CWorld::UpdateGameObjects(float _fDeltaTime)
{
  for (CGameObject* pIterator : m_tGameObjects)
  {
    pIterator->Update(_fDeltaTime);
  }
}

void CWorld::ResolveGameObjectsActivation()
{
  while (!m_gameObjectsToActive.empty())
  {
    m_gameObjectsToActive.front()->Active();
    m_gameObjectsToActive.pop();
  }
  while (!m_gameObjectsToDeactive.empty())
  {
    m_gameObjectsToDeactive.front()->Deactive();
    m_gameObjectsToDeactive.pop();
  }
}

void CWorld::ResolveCollisions()
{
  typedef std::vector<CGameObject*>::iterator GameObjectIterator;
  for (GameObjectIterator currentGameObject = m_tGameObjects.begin(); currentGameObject != m_tGameObjects.end(); ++currentGameObject)
  {
    if ((*currentGameObject)->IsActive())
    {
      CCollisionComponent* pCollisionComponent = (*currentGameObject)->GetComponent<CCollisionComponent>();
      GameObjectIterator collidingGameObject = currentGameObject + 1;
      bool bHasCollided = false;
      while (!bHasCollided && collidingGameObject != m_tGameObjects.end())
      {
        if ((*collidingGameObject)->IsActive() && pCollisionComponent->Collides(**collidingGameObject))
        {
          // Check types to update UI
          if ((*currentGameObject)->IsType(CGameObject::EGameObjectTypes::Enemy) || (*collidingGameObject)->IsType(CGameObject::EGameObjectTypes::Enemy))
          {
            CUIManager::GetInstance().EnemyDead();
          }
          DeactiveGameObject(**currentGameObject);
          DeactiveGameObject(**collidingGameObject);
          bHasCollided = true;
        }
        else ++collidingGameObject;
      }
    }
  }
}

void CWorld::Shutdown_Internal()
{
  CUIManager::GetInstance().Shutdown();
  CTimeManager::Shutdown();

  /**
   * Destroy all game objects
   */
  for (CGameObject* pIterator : m_tGameObjects)
  {
    CGameObject::Destroy(pIterator);
  }
}

CGameObject* CWorld::FindGameObjectByType(CGameObject::EGameObjectTypes _eType, bool _bIsActive) const
{
  for (CGameObject* pIterator : m_tGameObjects)
  {
    if (pIterator->IsActive() == _bIsActive && pIterator->IsType(_eType))
      return pIterator;
  }
  return nullptr;
}

bool CWorld::CheckValidSpawn(SSpawnInfo& _rSpawnInfo) const
{
  if (_rSpawnInfo.m_eType == CGameObject::EGameObjectTypes::Bullet)
  {
    int iCounter = 0;
    for (CGameObject* pIterator : m_tGameObjects)
    {
      if (pIterator->IsActive() && pIterator->IsType(_rSpawnInfo.m_eType))
      {
        CMovementComponent* pMovementComponent = pIterator->GetComponent<CMovementComponent>();
        if (pMovementComponent->GetMovementDirection() == _rSpawnInfo.m_iDirection)
        {
          ++iCounter;
        }
      }
    }
    return iCounter < 5;
  }
  return true;
}

