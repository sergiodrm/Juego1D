
#include "Render/RenderEngine.h"
#include "Input/InputManager.h"
#include "World/World.h"

int main()
{
  // Inicializar managers.
  CRenderEngine::Init();
  CInputManager::Init();
  CWorld::Init();

  // Loop game.
  while (!CWorld::GetInstance().GameOver())
  {
    CWorld::GetInstance().Update();
    CRenderEngine::GetInstance().Render();
  }
  // Terminar managers en orden inverso a la inicializacion.
  CWorld::Shutdown();
  CInputManager::Shutdown();
  CRenderEngine::Shutdown();
  return 0;
}