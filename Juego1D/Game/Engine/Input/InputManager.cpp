
#include "InputManager.h"
#include <Windows.h>

void CInputManager::Init()
{
  CreateSingleton();
}

CInputManager& CInputManager::GetInstance()
{
  return GetSingleton();
}

void CInputManager::Shutdown()
{
  DestroySingleton();
}

bool CInputManager::IsKeyPressed(Key _key)
{
  // Comprobar el msb con una mascara.
  return GetAsyncKeyState(_key) & 0x8000;
}
