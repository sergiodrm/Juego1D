#include "TransformComponent.h"

CTransformComponent::CTransformComponent()
  : m_uPosition(0u)
{}

size_t CTransformComponent::GetPosition() const
{
  return m_uPosition;
}

void CTransformComponent::SetPosition(size_t _uPosition)
{
  m_uPosition = _uPosition;
}

void CTransformComponent::AddPosition(size_t _uOffset)
{
  m_uPosition += _uOffset;
}
