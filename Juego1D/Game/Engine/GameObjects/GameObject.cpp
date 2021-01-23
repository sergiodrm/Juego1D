#include "GameObject.h"

CGameObject::~CGameObject()
{}

void CGameObject::Init()
{
}

void CGameObject::OnCreation()
{
}

void CGameObject::Update(float _fDeltaTime)
{
}

void CGameObject::Destroy()
{
}

void CGameObject::Active()
{
}

void CGameObject::Deactive()
{
}

bool CGameObject::IsActive() const
{
    return false;
}

CGameObject* CGameObject::Create()
{
  CGameObject* pNewGameObject = new CGameObject();
  ensure_msg(pNewGameObject != nullptr, "Failed creating new game object.");
  pNewGameObject->OnCreation();
  return pNewGameObject;
}

CGameObject::CGameObject()
{
  m_tComponents.reserve(3u);
}
