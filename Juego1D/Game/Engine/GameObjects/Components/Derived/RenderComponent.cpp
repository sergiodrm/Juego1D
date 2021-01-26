#include "RenderComponent.h"
#include "GameObjects/GameObject.h"
#include "TransformComponent.h"
#include "World/World.h"

CRenderComponent::CRenderComponent() : m_cSymbol('X') {}

void CRenderComponent::OnCreation(CGameObject* _pOwner)
{
  Super::OnCreation(_pOwner);
}

void CRenderComponent::Update(float _fDeltaTime)
{
  CWorld::GetInstance().GetScene().UpdateGameObjectInMap(*GetOwner());
}

void CRenderComponent::SetSymbol(char _cSymbol)
{
  m_cSymbol = _cSymbol;
}

char CRenderComponent::GetSymbol() const
{
  return m_cSymbol;
}
