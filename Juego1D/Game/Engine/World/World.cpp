#include "World.h"
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
  // Preparar el timer para la actualizacion de la logica.
  CTimeManager::GetInstance().InitTimerToProcess();
  // Loop de logica hasta que el timer haya agotado el tiempo almacenado.
  while (CTimeManager::GetInstance().Update())
  {
    // Logica de spawn de enemigos.
    EnemySpawnerSlot(static_cast<float>(CTimeManager::GetInstance().GetFixedTick()));
    // Actualizacion de game objects.
    UpdateGameObjects(static_cast<float>(CTimeManager::GetInstance().GetFixedTick()));
    // Resolucion de colisiones.
    ResolveCollisions();
    // Resolucion de cambios de estado en los game objects.
    ResolveGameObjectsActivation();
  }
}

void CWorld::DrawWorld()
{
  GetInstance().DrawWorld_Internal();
}

void CWorld::DrawWorld_Internal()
{
  // Renderizacion de escena + ui
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
  // Chequear que se pueda spawnear el game object solicitado
  if (!CheckValidSpawn(_rSpawnInfo))
  {
    return false;
  }
  // Busqueda de un game object inactivo del tipo especificado
  CGameObject* pSpawnedGameObject = FindGameObjectByType(_rSpawnInfo.m_eType, false);
  if (pSpawnedGameObject == nullptr)
  {
    return false;
  }
  // Configuracion del spawn
  pSpawnedGameObject->GetComponent<CTransformComponent>()->SetPosition(_rSpawnInfo.m_iPosition);
  pSpawnedGameObject->GetComponent<CMovementComponent>()->SetMovementDirection(_rSpawnInfo.m_iDirection);
  pSpawnedGameObject->GetComponent<CRenderComponent>()->SetSymbol(_rSpawnInfo.m_cSymbol);
  // Añadir el spawn a los game objects pendientes de activacion.
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
   * Inicializacion de variables.
   */
  m_iNumberOfBullets = 10;
  m_iNumberOfEnemies = 10;
  m_fTimeUntilNextSpawn = 0.f;
  m_fEnemySpawnProb = 0.4f;
  m_fTimeBetweenEnemySpawn = 2.f;

  /**
   * Inicializacion del game object del jugador.
   */
  {
    CGameObject* pPlayer = CGameObject::Create();
    pPlayer->SetType(CGameObject::EGameObjectTypes::Player);
    pPlayer->GetComponent<CTransformComponent>()->SetPosition(static_cast<int>(GetScene().GetSize()) / 2);
    CRenderComponent* pRenderComponent = pPlayer->AddComponent<CRenderComponent>();
    pRenderComponent->SetSymbol('X');
    CMovementComponent* pMovementComponent = pPlayer->AddComponent<CMovementComponent>();
    pMovementComponent->SetInputPlayerEnabled(true);
    CCollisionComponent* pCollisionComponent = pPlayer->AddComponent<CCollisionComponent>();
    pCollisionComponent->SetTypeToIgnore(CGameObject::EGameObjectTypes::Bullet);
    pPlayer->AddComponent<CAttackComponent>();
    ActiveGameObject(*pPlayer);
  }

  /**
   * Inicializacion de las balas.
   */
  {
    for (int iIndex = 0; iIndex < m_iNumberOfBullets; ++iIndex)
    {
      CGameObject* pBullet = CGameObject::Create();
      pBullet->SetType(CGameObject::EGameObjectTypes::Bullet);
      pBullet->AddComponent<CRenderComponent>();
      CMovementComponent* pMovementComponent = pBullet->AddComponent<CMovementComponent>();
      pMovementComponent->SetInputPlayerEnabled(false);
      pMovementComponent->SetSpeed(5.f);
      CCollisionComponent* pCollisionComponent = pBullet->AddComponent<CCollisionComponent>();
      pCollisionComponent->SetTypeToIgnore(CGameObject::EGameObjectTypes::Player);
      DeactiveGameObject(*pBullet);
    }
  }

  /**
   * Inicializacion de enemigos.
   */
  {
    for (int iIndex = 0; iIndex < m_iNumberOfEnemies; ++iIndex)
    {
      CGameObject* pEnemy = CGameObject::Create();
      pEnemy->SetType(CGameObject::EGameObjectTypes::Enemy);
      CRenderComponent* pRenderComponent = pEnemy->AddComponent<CRenderComponent>();
      pRenderComponent->SetSymbol('*');
      CMovementComponent* pMovementComponent = pEnemy->AddComponent<CMovementComponent>();
      pMovementComponent->SetInputPlayerEnabled(false);
      CCollisionComponent* pCollisionComponent = pEnemy->AddComponent<CCollisionComponent>();
      pCollisionComponent->SetTypeToIgnore(CGameObject::EGameObjectTypes::Enemy);
      DeactiveGameObject(*pEnemy);
    }
  }

  /**
   * Enlazar el metodo de renderizado del mundo con el render engine.
   */
  CRenderEngine::GetInstance().SetDrawWorldFunction(&CWorld::DrawWorld);

  /**
   * Iniciar el timer.
   */
  CTimeManager::Init();

  /**
   * Iniciar el gestor de interfaz de usuario.
   */
  CUIManager::Init();

  /**
   * Activar los game objects pendientes antes de iniciar el mundo.
   */
  ResolveGameObjectsActivation();
}

void CWorld::EnemySpawnerSlot(float _fDeltaTime)
{
  // Lambda para devolver un numero aleatorio entre 0 y 1.
  auto RandLambda = []() -> float
  {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  };
  // Si el temporizador del spawn esta a cero, se puede spawnear un enemigo.
  if (m_fTimeUntilNextSpawn == 0.f)
  {
    // Tirar el dado para decidir si hay spawn o no.
    float fDice = RandLambda();
    if (fDice <= m_fEnemySpawnProb)
    {
      // En caso de spawnear, decidir en que lado de la escena se spawnea el enemigo.
      float fRandomSpawnSide = RandLambda();
      int iDirection = 1;
      if (fRandomSpawnSide < 0.5f)
      {
        iDirection = -1;
      }
      // Rellenar la informacion de spawn.
      SSpawnInfo enemySpawnInfo;
      enemySpawnInfo.m_cSymbol = '*';
      enemySpawnInfo.m_eType = CGameObject::EGameObjectTypes::Enemy;
      enemySpawnInfo.m_iDirection = iDirection;
      enemySpawnInfo.m_iPosition = iDirection == 1 ? 0 : static_cast<int>(GetScene().GetSize()) - 1;
      SpawnGameObject(enemySpawnInfo);
      // Iniciar la cuenta atras de spawn de enemigo.
      m_fTimeUntilNextSpawn = m_fTimeBetweenEnemySpawn;
    }
  }
  else
  {
    // Cuenta atras.
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
  // Resolver game objects pendientes de activacion.
  while (!m_gameObjectsToActive.empty())
  {
    m_gameObjectsToActive.front()->Active();
    m_gameObjectsToActive.pop();
  }
  // Resolver game objects pendientes de desactivacion.
  while (!m_gameObjectsToDeactive.empty())
  {
    m_gameObjectsToDeactive.front()->Deactive();
    m_gameObjectsToDeactive.pop();
  }
}

void CWorld::ResolveCollisions()
{
  // Recorrer los game objects para buscar colisiones entre ellos.
  typedef std::vector<CGameObject*>::iterator GameObjectIterator;
  for (GameObjectIterator currentGameObject = m_tGameObjects.begin(); currentGameObject != m_tGameObjects.end(); ++currentGameObject)
  {
    // Chequear el game object si esta activado.
    if ((*currentGameObject)->IsActive())
    {
      // Se empieza a comprobar la colision con el siguiente game object del vector.
      CCollisionComponent* pCollisionComponent = (*currentGameObject)->GetComponent<CCollisionComponent>();
      GameObjectIterator collidingGameObject = currentGameObject + 1;
      bool bHasCollided = false;
      while (!bHasCollided && collidingGameObject != m_tGameObjects.end())
      {
        if ((*collidingGameObject)->IsActive() && pCollisionComponent->Collides(**collidingGameObject))
        {
          // Comprobar si alguno de los game objects colisionados es un enemigo para informar al gestor de UI.
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
   * Borrar todos los game objects almacenados.
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
  /**
   * Chequear si se puede spawnear una bala segun el criterio de que solo
   * pueden haber 5 balas a cada lado del player.
   */
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

