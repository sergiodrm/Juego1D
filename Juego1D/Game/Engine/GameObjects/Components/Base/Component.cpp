#include "Component.h"

CComponent::~CComponent() = default;

void CComponent::OnCreation(CGameObject* _pOwner)
{
  m_pOwner = _pOwner;
}

void CComponent::Init() {}
void CComponent::Update(float _fDeltaTime) {}
void CComponent::OnDestroy() {}

CGameObject* CComponent::GetOwner() const
{
  return m_pOwner;
}

void CComponent::Active()
{
  m_bActive = true;
}

void CComponent::Deactive()
{
  m_bActive = false;
}

bool CComponent::IsActive() const
{
  return m_bActive;
}

void CComponent::Destroy(CComponent* _pComponent)
{
  ensure(_pComponent != nullptr);
  _pComponent->OnDestroy();
  delete _pComponent;
}
