#include "Component.h"

void CComponent::OnCreation(CGameObject* _pOwner)
{
  m_pOwner = _pOwner;
}

void CComponent::Init()
{}

void CComponent::Update(float _fDeltaTime)
{}

void CComponent::OnDestroy()
{}

CGameObject* CComponent::GetOwner() const
{
  return m_pOwner;
}

void CComponent::Destroy(CComponent* _pComponent)
{
  ensure(_pComponent != nullptr);
  _pComponent->OnDestroy();
  delete _pComponent;
}
