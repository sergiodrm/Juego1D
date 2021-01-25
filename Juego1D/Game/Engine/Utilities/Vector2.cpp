#include "Vector2.h"

CVector2::CVector2() : m_fX(0), m_fY(0) {}

CVector2::CVector2(float _uX, float _uY) : m_fX(_uX), m_fY(_uY) {}

float CVector2::GetX() const { return m_fX; }
float CVector2::GetY() const { return m_fY; }
void CVector2::SetX(float _uX) { m_fX = _uX; }
void CVector2::SetY(float _uY) { m_fY = _uY; }

CVector2& CVector2::operator+(const CVector2 _other)
{
  m_fX += _other.m_fX;
  m_fY += _other.m_fY;
  return *this;
}

CVector2& CVector2::operator+=(const CVector2 _other)
{
  return *this + _other;
}
