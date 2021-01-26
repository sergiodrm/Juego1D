
#include "Render/RenderEngine.h"
#include "Logic/LogicManager.h"
#include "Input/InputManager.h"
#include "World/World.h"

int main()
{
  CRenderEngine::Init();
  CInputManager::Init();
  CWorld::Init();

  while (true)
  {
    CWorld::GetInstance().Update();
    CRenderEngine::GetInstance().Render();
  }

  CWorld::Shutdown();
  CInputManager::Shutdown();
  CRenderEngine::Shutdown();
  return 0;
}