#pragma once

#include "Utilities/MacroUtility.h"

// Forward declaration
class CGameObject;

class CComponent
{
public:

  void OnCreation(CGameObject* _pOwner);
  virtual void Init();
  virtual void Update(float _fDeltaTime);
  virtual void OnDestroy();

  CGameObject* GetOwner() const;

  template <typename T>
  static T* Create(CGameObject* _pOwner);
  static void Destroy(CComponent* _pComponent);

protected:

  CComponent() : m_pOwner(nullptr) {}

private:

  CGameObject* m_pOwner;

};


template <typename T>
T* CComponent::Create(CGameObject* _pOwner)
{
  ensure(_pOwner != nullptr);
  T* pNewComponent = new T();
  ensure_msg(pNewComponent != nullptr, "Failed creating new component.");
  pNewComponent->OnCreation(_pOwner);
  return pNewComponent;
}
