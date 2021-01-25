#include "MovementComponent.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Derived/TransformComponent.h"
#include "Input/InputManager.h"

CMovementComponent::CMovementComponent()
  : m_fSpeed(10.f), m_vMovementDirection(0, 0),
m_bInputPlayer(true) {}

void CMovementComponent::Update(float _fDeltaTime)
{
  if (m_bInputPlayer)
    UpdateInputVector();
  UpdateMovement(_fDeltaTime);
}

CVector2 CMovementComponent::GetMovementDirection() const
{
  return m_vMovementDirection;
}

float CMovementComponent::GetSpeed() const
{
  return m_fSpeed;
}

void CMovementComponent::SetSpeed(float _fSpeed)
{
  m_fSpeed = _fSpeed;
}

void CMovementComponent::SetMovementDirection(const CVector2& _vMovementDirection)
{
  m_vMovementDirection = _vMovementDirection;
}

bool CMovementComponent::IsInputPlayerEnable() const
{
  return m_bInputPlayer;
}

void CMovementComponent::SetInputPlayerEnable(bool _bInputPlayer)
{
  m_bInputPlayer = _bInputPlayer;
}

void CMovementComponent::UpdateInputVector()
{
  if (CInputManager::GetInstance().IsKeyPressed(KEYBOARD_A))
  {
    m_vMovementDirection.SetX(-1.f);
  } else if (CInputManager::GetInstance().IsKeyPressed(KEYBOARD_D))
  {
    m_vMovementDirection.SetX(1.f);
  } else
  {
    m_vMovementDirection.SetX(0.f);
  }
}

void CMovementComponent::UpdateMovement(float _fDeltaTime) const
{
  CTransformComponent* pTransformComponent = GetOwner()->GetComponent<CTransformComponent>();
  if (pTransformComponent != nullptr)
  {
    CVector2 vOffset;
    vOffset.SetX(m_vMovementDirection.GetX() * m_fSpeed * _fDeltaTime);
    vOffset.SetY(m_vMovementDirection.GetY() * m_fSpeed * _fDeltaTime);
    pTransformComponent->AddPosition(vOffset);
  }
}
