#include "AttackComponent.h"
#include "Input/InputManager.h"
#include "World/World.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Derived/TransformComponent.h"

CAttackComponent::CAttackComponent() = default;

void CAttackComponent::Update(float _fDeltaTime)
{
  int iDirection = 0;
  if (CInputManager::GetInstance().IsKeyPressed(KEYBOARD_J))
  {
    iDirection = -1;
  }
  else if (CInputManager::GetInstance().IsKeyPressed(KEYBOARD_L))
  {
    iDirection = 1;
  }

  if (iDirection != 0)
  {
    SpawnBullet(iDirection);
  }
}

void CAttackComponent::SpawnBullet(int _iDirection) const
{
  SSpawnInfo spawnInfo;
  spawnInfo.m_eType = CGameObject::EGameObjectTypes::Bullet;
  spawnInfo.m_iDirection = _iDirection;
  spawnInfo.m_iPosition = GetOwner()->GetComponent<CTransformComponent>()->GetPosition();
  spawnInfo.m_cSymbol = _iDirection == -1 ? '<' : '>';
  CWorld::GetInstance().SpawnGameObject(spawnInfo);
}

