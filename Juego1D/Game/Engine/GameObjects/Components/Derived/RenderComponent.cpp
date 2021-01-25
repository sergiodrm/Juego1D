#include "RenderComponent.h"
#include "Render/RenderableObject.h"
#include "Render/RenderEngine.h"
#include "GameObjects/GameObject.h"
#include "TransformComponent.h"
#include "Utilities/Vector2.h"

CRenderComponent::CRenderComponent() : m_renderableObject() {}

void CRenderComponent::OnCreation(CGameObject* _pOwner)
{
  Super::OnCreation(_pOwner);
  CRenderEngine::GetInstance().AddRenderableObject(m_renderableObject);
}

void CRenderComponent::Update(float _fDeltaTime)
{
  CTransformComponent* pTransformComponent = GetOwner()->GetComponent<CTransformComponent>();
  if (pTransformComponent != nullptr)
  {
    CVector2 vPosition = pTransformComponent->GetPosition();
    m_renderableObject.SetPosition(vPosition);
  }
}

void CRenderComponent::SetSymbol(char _cSymbol)
{
  m_renderableObject.SetSymbol(_cSymbol);
}
