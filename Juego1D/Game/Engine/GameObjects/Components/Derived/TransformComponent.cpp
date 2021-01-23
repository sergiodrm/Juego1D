#include "TransformComponent.h"

CTransformComponent::CTransformComponent()
  : m_uPositionX(0u), m_uPositionY(0u)
{}

void CTransformComponent::GetPosition(size_t& uPosX_, size_t& uPosY_) const
{
  uPosX_ = m_uPositionX;
  uPosY_ = m_uPositionY;
}

void CTransformComponent::SetPosition(size_t _uPosX, size_t _uPosY)
{
  m_uPositionX = _uPosX;
  m_uPositionY = _uPosY;
}

void CTransformComponent::AddPosition(size_t _uPosX, size_t _uPosY)
{
  m_uPositionX += _uPosX;
  m_uPositionY += _uPosY;
}
