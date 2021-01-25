#include "RenderableObject.h"
#include <Windows.h>
#include <consoleapi2.h>
#include <cstdio>

CRenderableObject::CRenderableObject(char _cSymbol)
  : m_cSymbol(_cSymbol), m_vPosition(0.f, 0.f) {}

CVector2 CRenderableObject::GetPosition() const
{
  return m_vPosition;
}

void CRenderableObject::SetPosition(const CVector2& _vPosition)
{
  m_vPosition = _vPosition;
}

char CRenderableObject::GetSymbol() const
{
  return m_cSymbol;
}
void CRenderableObject::SetSymbol(char _cSymbol)
{
  m_cSymbol = _cSymbol;
}

void CRenderableObject::Render() const
{
  if (m_bActive)
  {
    COORD currentPosition;
    currentPosition.X = static_cast<SHORT>(m_vPosition.GetX());
    currentPosition.Y = static_cast<SHORT>(m_vPosition.GetY());
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentPosition);
    printf("%c", m_cSymbol);
  }
}

bool CRenderableObject::IsActive() const
{
  return m_bActive;
}

void CRenderableObject::Active()
{
  m_bActive = true;
}

void CRenderableObject::Deactive()
{
  m_bActive = false;
}
