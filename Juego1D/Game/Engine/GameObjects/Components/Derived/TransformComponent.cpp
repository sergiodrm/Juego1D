#include "TransformComponent.h"

CTransformComponent::CTransformComponent()
  : m_iPosition(0) {}

int CTransformComponent::GetPosition() const
{
  return m_iPosition;
}

void CTransformComponent::SetPosition(int _iPosition)
{
  m_iPosition = _iPosition;
}

void CTransformComponent::AddPosition(int _iPosition)
{
  m_iPosition += _iPosition;
}
