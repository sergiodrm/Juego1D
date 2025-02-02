#include "RenderEngine.h"
#include "Utilities/MacroUtility.h"
#include <Windows.h>
#include <cstdio>
#include <consoleapi2.h>

void CRenderEngine::Init()
{
  CreateSingleton();
  GetSingleton().Init_Internal();
}

CRenderEngine& CRenderEngine::GetInstance()
{
  return GetSingleton();
}

void CRenderEngine::Shutdown()
{
  GetInstance().Shutdown_Internal();
  DestroySingleton();
}

void CRenderEngine::Render() const
{
  ClearScreen();
  if (m_pDrawWorldFunction != nullptr)
    m_pDrawWorldFunction();
}

void CRenderEngine::SetDrawWorldFunction(DrawWorldFunction _pDrawFunction)
{
  m_pDrawWorldFunction = _pDrawFunction;
}

void CRenderEngine::Print(const char* _sStringToPrint, int _iPosX, int _iPosY)
{
  ensure(_sStringToPrint != nullptr);
  // Cambiar la posicion del cursor
  COORD currentPosition;
  currentPosition.X = static_cast<SHORT>(_iPosX);
  currentPosition.Y = static_cast<SHORT>(_iPosY);
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentPosition);
  // Printear la cadena especificada.
  printf("%s", _sStringToPrint);
}

void CRenderEngine::Init_Internal()
{
  m_pDrawWorldFunction = nullptr;
}

void CRenderEngine::Shutdown_Internal()
{
  m_pDrawWorldFunction = nullptr;
}

void CRenderEngine::ClearScreen()
{
  system("cls");
}
