#include "MovementComponent.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Derived/TransformComponent.h"
#include "Input/InputManager.h"

CMovementComponent::CMovementComponent()
  : m_fSpeed(2.f), m_iMovementDirection(0), m_bInputPlayer(true), m_fPosition(0.f) {}

void CMovementComponent::Update(float _fDeltaTime)
{
  // Actualizar la direccion de movimiento segun el player
  if (m_bInputPlayer)
    UpdateInputVector();
  // Actualizar transform con la informacion de la direccion
  UpdateMovement(_fDeltaTime);
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

bool CMovementComponent::IsInputPlayerEnabled() const
{
  return m_bInputPlayer;
}

void CMovementComponent::SetInputPlayerEnabled(bool _bInputPlayer)
{
  m_bInputPlayer = _bInputPlayer;
}

void CMovementComponent::UpdateInputVector()
{
  // Comprobar pulsacion de teclas asociadas al movimiento.
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
  // Obtener el transform del game object.
  CTransformComponent* pTransformComponent = GetOwner()->GetComponent<CTransformComponent>();
  if (pTransformComponent != nullptr)
  {
    // Actualizar posicion exacta para que coincida con la posicion en la que se encuentra el transform.
    if (pTransformComponent->GetPosition() != static_cast<int>(m_fPosition))
    {
      m_fPosition = static_cast<float>(pTransformComponent->GetPosition());
    }
    // Actualizar posicion exacta segun velocidad tiempo y direccion.
    m_fPosition += m_fSpeed * _fDeltaTime * static_cast<float>(m_iMovementDirection);
    // Actualizar la posicion del transform con la parte entera de la posicion exacta.
    pTransformComponent->SetPosition(static_cast<int>(m_fPosition));
    // De esta manera el movimiento se modifica en funcion de la velocidad dada en unidades de espacio / segundo.
    // (Entendiendo como unidades de espacio a cada posicion del string que dibuja la escena).
  }
}
