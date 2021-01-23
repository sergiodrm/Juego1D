#pragma once

#include "../Utilities/MacroUtility.h"
#include <vector>

// Forward declaration
class CComponent;

class CGameObject
{
  /**
  *     Methods
  */
public:

  ~CGameObject();

  void Init();
  void OnCreation();
  void Update(float _fDeltaTime);
  void Destroy();

  void Active();
  void Deactive();
  bool IsActive() const;

  template <typename T>
  T* AddComponent();

  template <typename T>
  T* GetComponent();

  /**
  *     Static methods
  */
  static CGameObject* Create();

protected:
  /**
  * Protected component so that game objects only can be created from Create() method
  */
  CGameObject();

private:

  std::vector<CComponent*> m_tComponents;
  bool m_bActive;

};

/**
*     Templates definition
*/
template <typename T>
T* CGameObject::AddComponent()
{
  T* pNewComponent = new T();
  ensure_msg(pNewComponent != nullptr, "Failed creating new component");
  m_tComponents.push_back(pNewComponent);
  return pNewComponent;
}

template <typename T>
T* CGameObject::GetComponent()
{
  for (CComponent* pIterator : m_tComponents)
  {
    T* pDesiredComponent = dynamic_cast<T*>(pIterator);
    if (pDesiredComponent != nullptr)
    {
      return pDesiredComponent;
    }
  }
  return nullptr;
}