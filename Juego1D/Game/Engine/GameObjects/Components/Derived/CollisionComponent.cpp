#include "CollisionComponent.h"
#include "TransformComponent.h"
#include "GameObjects/GameObject.h"
#include "World/World.h"

CCollisionComponent::CCollisionComponent()
  : m_eTypeToIgnore(CGameObject::EGameObjectTypes::Invalid) {}

void CCollisionComponent::Update(float _fDeltaTime)
{
  if (GetOwner()->IsType(CGameObject::EGameObjectTypes::Bullet))
  {
    CTransformComponent* pTransformComponent = GetOwner()->GetComponent<CTransformComponent>();
    if (pTransformComponent->GetPosition() <= 0 || pTransformComponent->GetPosition() >= static_cast<int>(CWorld::GetInstance().GetScene().GetSize()))
    {
      GetOwner()->Deactive();
    }
  }
}

bool CCollisionComponent::Collides(CGameObject& _rOther) const
{
  if (_rOther.IsType(m_eTypeToIgnore))
    return false;

  CTransformComponent* pMyTransform = GetOwner()->GetComponent<CTransformComponent>();
  CTransformComponent* pOtherTransform = _rOther.GetComponent<CTransformComponent>();

  return pMyTransform->GetPosition() == pOtherTransform->GetPosition();
}

CGameObject::EGameObjectTypes CCollisionComponent::GetTypeToIgnore() const
{
  return m_eTypeToIgnore;
}

void CCollisionComponent::SetTypeToIgnore(CGameObject::EGameObjectTypes _eType)
{
  m_eTypeToIgnore = _eType;
}
