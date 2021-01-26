#include "GameObject.h"
#include "Components/Derived/TransformComponent.h"
#include "Logic/LogicManager.h"
#include "World/World.h"

CGameObject::CGameObject() :
  m_bActive(false), m_eType(EGameObjectTypes::Invalid) {}

CGameObject::~CGameObject() = default;

void CGameObject::Init() {}

void CGameObject::OnCreation()
{
  m_tComponents.reserve(4u);
  AddComponent<CTransformComponent>();
}

void CGameObject::Update(float _fDeltaTime)
{
  if (m_bActive)
  {
    for (CComponent* pIterator : m_tComponents)
    {
      pIterator->Update(_fDeltaTime);
    }
  }
}

void CGameObject::OnDestroy()
{
  for (CComponent* pIterator : m_tComponents)
  {
    CComponent::Destroy(pIterator);
  }
  m_tComponents.clear();
}

void CGameObject::Active()
{
  m_bActive = true;
  for (CComponent* pIterator : m_tComponents)
  {
    pIterator->Active();
  }
}

void CGameObject::Deactive()
{
  m_bActive = false;
  for (CComponent* pIterator : m_tComponents)
  {
    pIterator->Deactive();
  }
}

bool CGameObject::IsActive() const
{
  return m_bActive;
}

CGameObject::EGameObjectTypes CGameObject::GetType() const
{
  return m_eType;
}

bool CGameObject::IsType(EGameObjectTypes _eType) const
{
  return m_eType == _eType;
}

void CGameObject::SetType(EGameObjectTypes _eType)
{
  m_eType = _eType;
}

CGameObject* CGameObject::Create()
{
  CGameObject* pNewGameObject = new CGameObject();
  ensure_msg(pNewGameObject != nullptr, "Failed creating new game object.");
  pNewGameObject->OnCreation();
  CWorld::GetInstance().InsertGameObject(*pNewGameObject);
  return pNewGameObject;
}

void CGameObject::Destroy(CGameObject* _pGameObject)
{
  ensure(_pGameObject != nullptr);
  _pGameObject->OnDestroy();
  delete _pGameObject;
}


