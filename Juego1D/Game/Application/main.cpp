
#include "Render/RenderEngine.h"
#include "Input/InputManager.h"
#include "World/World.h"

int main()
{
  CRenderEngine::Init();
  CInputManager::Init();
  CWorld::Init();

  while (!CWorld::GetInstance().GameOver())
  {
    CWorld::GetInstance().Update();
    CRenderEngine::GetInstance().Render();
  }

  CWorld::Shutdown();
  CInputManager::Shutdown();
  CRenderEngine::Shutdown();
  return 0;
}