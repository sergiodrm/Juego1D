#include "AttackComponent.h"
#include "Input/InputManager.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Derived/TransformComponent.h"
#include "GameObjects/Components/Derived/RenderComponent.h"
#include "GameObjects/Components/Derived/MovementComponent.h"

CAttackComponent::CAttackComponent() {}

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
  // @TODO spawn bullet depending on the direction

  CGameObject* pBullet = CGameObject::Create();
  CRenderComponent* pRenderComponent = pBullet->AddComponent<CRenderComponent>();
  pRenderComponent->SetSymbol(_iDirection == -1 ? '<' : '>');
  CMovementComponent* pMovementComponent = pBullet->AddComponent<CMovementComponent>();
  pMovementComponent->SetSpeed(20.f);
  pMovementComponent->SetInputPlayerEnable(false);
  pMovementComponent->SetMovementDirection(CVector2(static_cast<float>(_iDirection), 0.f));

  CVector2 currentPosition = GetOwner()->GetComponent<CTransformComponent>()->GetPosition();

  CTransformComponent* pTransformComponent = pBullet->GetComponent<CTransformComponent>();
  pTransformComponent->SetPosition(currentPosition);
}

