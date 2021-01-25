#include "TransformComponent.h"

CTransformComponent::CTransformComponent()
  : m_vPosition(0.f, 0.f)
{}

CVector2 CTransformComponent::GetPosition() const
{
  return m_vPosition;
}

void CTransformComponent::SetPosition(const CVector2& _vPosition)
{
  m_vPosition = _vPosition;
}

void CTransformComponent::AddPosition(const CVector2& _vPosition)
{
  m_vPosition += _vPosition;
}
