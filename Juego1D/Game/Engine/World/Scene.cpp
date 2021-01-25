#include "Scene.h"
#include "Logic/LogicManager.h"
#include "Render/RenderEngine.h"
#include "Map.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Derived/TransformComponent.h"
#include "GameObjects/Components/Derived/MovementComponent.h"
#include "GameObjects/Components/Derived/AttackComponent.h"
#include "GameObjects/Components/Derived/RenderComponent.h"

CScene::CScene(int _iNumBullets, int _iNumEnemies)
  : m_iNumberOfBullets(_iNumBullets), m_iNumberOfEnemies(_iNumEnemies) {}

void CScene::Init()
{
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
    CAttackComponent* pAttackComponent = pPlayer->AddComponent<CAttackComponent>();
  }

  /**
   * Init bullets
   */
  {
    for (int iIndex = 0; iIndex < m_iNumberOfBullets; ++iIndex)
    {
      CGameObject* pBullet = CGameObject::Create();
      pBullet->SetType(CGameObject::EGameObjectTypes::Bullet);
      CRenderComponent* pRenderComponent = pBullet->AddComponent<CRenderComponent>();
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
   * @TODO: Implement a complete active/deactive logic in game objects (including components and derived).
   * @TODO: Garbage collector to avoid memory leaks.
   * @TODO: Spawn bullets logic from Scene and handle without change game object vector.
   * @TODO: Include time manager in game.
   * @TODO: Collision component.
   * @TODO: Life component.
   */
}

void CScene::Shutdown() {}
