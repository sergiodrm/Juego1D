#include "RenderEngine.h"
#include <Windows.h>
#include <cstdlib>
#include "RenderableObject.h"

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
