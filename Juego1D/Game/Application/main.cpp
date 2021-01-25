
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Derived/RenderComponent.h"
#include "GameObjects/Components/Derived/TransformComponent.h"
#include "GameObjects/Components/Derived/MovementComponent.h"
#include "GameObjects/Components/Derived/AttackComponent.h"
#include "Render/RenderEngine.h"
#include "Logic/LogicManager.h"
#include "Input/InputManager.h"

int main()
{
  CRenderEngine::Init();
  CLogicManager::Init();
  CInputManager::Init();

  

  while (true)
  {
    
    CLogicManager::GetInstance().Update(0.1f);
    CRenderEngine::GetInstance().Render();
  }

  CInputManager::Shutdown();
  CLogicManager::Shutdown();
  CRenderEngine::Shutdown();
  return 0;
}