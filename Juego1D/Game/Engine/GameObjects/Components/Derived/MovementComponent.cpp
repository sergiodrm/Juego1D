#include "MovementComponent.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Derived/TransformComponent.h"
#include "Input/InputManager.h"

CMovementComponent::CMovementComponent()
  : m_fSpeed(2.f), m_iMovementDirection(0), m_bInputPlayer(true), m_fPosition(0.f) {}

void CMovementComponent::Update(float _fDeltaTime)
{
  if (m_bInputPlayer)
    UpdateInputVector();
  UpdateMovement(_fDeltaTime);
}

void CMovementComponent::Active()
{
  Super::Active();
  CTransformComponent* pTransformComponent = GetOwner()->GetComponent<CTransformComponent>();
  m_fPosition = static_cast<float>(pTransformComponent->GetPosition());
}

int CMovementComponent::GetMovementDirection() const
{
  return m_iMovementDirection;
}

float CMovementComponent::GetSpeed() const
{
  return m_fSpeed;
}

void CMovementComponent::SetSpeed(float _fSpeed)
{
  m_fSpeed = _fSpeed;
}

void CMovementComponent::SetMovementDirection(int _iMovementDirection)
{
  m_iMovementDirection = _iMovementDirection;
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
    m_iMovementDirection = -1;
  } else if (CInputManager::GetInstance().IsKeyPressed(KEYBOARD_D))
  {
    m_iMovementDirection = 1;
  } else
  {
    m_iMovementDirection = 0;
  }
}

void CMovementComponent::UpdateMovement(float _fDeltaTime)
{
  CTransformComponent* pTransformComponent = GetOwner()->GetComponent<CTransformComponent>();
  if (pTransformComponent != nullptr)
  {
    if (pTransformComponent->GetPosition() != static_cast<int>(m_fPosition))
    {
      m_fPosition = static_cast<float>(pTransformComponent->GetPosition());
    }
    m_fPosition += m_fSpeed * _fDeltaTime * static_cast<float>(m_iMovementDirection);
    pTransformComponent->SetPosition(static_cast<int>(m_fPosition));
  }
}
