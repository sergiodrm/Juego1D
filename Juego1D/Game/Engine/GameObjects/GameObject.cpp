#include "GameObject.h"
#include "Components/Derived/TransformComponent.h"

CGameObject::~CGameObject()
{}

void CGameObject::Init()
{
}

void CGameObject::OnCreation()
{
  m_tComponents.reserve(3u);
  AddComponent<CTransformComponent>();
}

void CGameObject::Update(float _fDeltaTime)
{
  for (CComponent* pIterator : m_tComponents)
  {
    pIterator->Update(_fDeltaTime);
  }
}

void CGameObject::OnDestroy()
{
  for (CComponent* pIterator : m_tComponents)
  {
    CComponent::Destroy(pIterator);
  }
  m_tComponents.shrink_to_fit();
}

void CGameObject::Active()
{
}

void CGameObject::Deactive()
{
}

bool CGameObject::IsActive() const
{
  return m_bActive;
}

CGameObject* CGameObject::Create()
{
  CGameObject* pNewGameObject = new CGameObject();
  ensure_msg(pNewGameObject != nullptr, "Failed creating new game object.");
  pNewGameObject->OnCreation();
  return pNewGameObject;
}

void CGameObject::Destroy(CGameObject* _pGameObject)
{
  ensure(_pGameObject != nullptr);
  _pGameObject->OnDestroy();
  delete _pGameObject;
}

