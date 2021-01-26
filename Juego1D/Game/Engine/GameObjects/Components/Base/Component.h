#pragma once
#pragma warning(disable : 4100)

#include "Utilities/MacroUtility.h"

// Forward declaration
class CGameObject;

class CComponent
{
  BASE_CLASS(CComponent);
public:

  virtual ~CComponent();

  virtual void OnCreation(CGameObject* _pOwner);
  virtual void Init();
  virtual void Update(float _fDeltaTime);
  virtual void OnDestroy();

  CGameObject* GetOwner() const;

  virtual void Active();
  virtual void Deactive();
  bool IsActive() const;

  template <typename T>
  static T* Create(CGameObject* _pOwner);
  static void Destroy(CComponent* _pComponent);

protected:

  CComponent()
    : m_pOwner(nullptr), m_bActive(false)
  {}

private:

  CGameObject* m_pOwner;
  bool m_bActive;

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
