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

void CRenderEngine::Render()
{
  ClearScreen();
  for (CRenderableObject* pIterator : m_tRenderableObjects)
  {
    pIterator->Render();
  }
}

void CRenderEngine::Init_Internal()
{
  m_tRenderableObjects.reserve(30);
}

void CRenderEngine::Shutdown_Internal()
{
  m_tRenderableObjects.clear();
}

void CRenderEngine::ClearScreen()
{
  system("cls");
}
