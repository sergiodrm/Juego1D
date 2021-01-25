
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

  CGameObject* player = CGameObject::Create();
  CRenderComponent* pRenderComponent = player->AddComponent<CRenderComponent>();
  pRenderComponent->SetSymbol('X');
  CMovementComponent* pMovementComponent = player->AddComponent<CMovementComponent>();
  pMovementComponent->SetInputPlayerEnable(true);
  CAttackComponent* pAttackComponent = player->AddComponent<CAttackComponent>();

  

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