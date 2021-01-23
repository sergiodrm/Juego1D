#include "RenderableObject.h"
#include <Windows.h>
#include <consoleapi2.h>
#include <cstdio>

CRenderableObject::CRenderableObject(char _cSymbol)
  : m_cSymbol(_cSymbol), m_uPositionX(0u), m_uPositionY(0u) {}

void CRenderableObject::operator=(char _cSymbol)
{
  m_cSymbol = _cSymbol;
}

void CRenderableObject::GetPosition(size_t& uPosX_, size_t& uPosY_) const
{
  uPosX_ = m_uPositionX;
  uPosY_ = m_uPositionY;
}

void CRenderableObject::SetPosition(size_t _uPosX, size_t _uPosY)
{
  m_uPositionX = _uPosX;
  m_uPositionY = _uPosY;
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
  COORD currentPosition;
  currentPosition.X = static_cast<SHORT>(m_uPositionX);
  currentPosition.Y = static_cast<SHORT>(m_uPositionY);
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentPosition);
  printf("%c", m_cSymbol);
}
