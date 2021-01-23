
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Derived/RenderComponent.h"
#include "GameObjects/Components/Derived/TransformComponent.h"
#include "Render/RenderEngine.h"
#include "Logic/LogicManager.h"

int main()
{
  CRenderEngine::Init();
  CLogicManager::Init();

  CGameObject* player = CGameObject::Create();
  CRenderComponent* pRenderComponent = player->AddComponent<CRenderComponent>();
  pRenderComponent->SetSymbol('X');
  player->GetComponent<CTransformComponent>()->SetPosition(10, 10);

  while (true)
  {
    CLogicManager::GetInstance().Update(0.1f);
    CRenderEngine::GetInstance().Render();
  }

  CLogicManager::Shutdown();
  CRenderEngine::Shutdown();
  return 0;
}