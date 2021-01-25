#include "Map.h"
#include <Windows.h>
#include <consoleapi2.h>
#include <cstdio>

CMap::CMap()
{
  m_sMap = "--------------------------------------------------------------";
  m_vSize = CVector2(m_vPosition.GetX() + m_sMap.size(), 0.f);
}

void CMap::Render() const
{
  COORD currentPosition;
  currentPosition.X = static_cast<SHORT>(m_vPosition.GetX());
  currentPosition.Y = static_cast<SHORT>(m_vPosition.GetY());
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentPosition);
  printf("%s", m_sMap.c_str());
}

CVector2 CMap::GetLeftLimit() const { return m_vPosition; }
CVector2 CMap::GetRightLimit() const { return m_vPosition + m_vSize; }
