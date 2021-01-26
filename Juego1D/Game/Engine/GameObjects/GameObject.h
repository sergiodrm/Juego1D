#pragma once

#include <vector>

// Forward declaration
class CComponent;

class CGameObject
{

public:

  enum EGameObjectTypes : int
  {
    Invalid = -1,
    Player, Enemy, Bullet
  };

  /**
  *     Methods
  */
public:

  ~CGameObject();

  void Init();
  void OnCreation();
  void Update(float _fDeltaTime);
  void OnDestroy();

  void Active();
  void Deactive();
  bool IsActive() const;

  EGameObjectTypes GetType() const;
  bool IsType(EGameObjectTypes _eType) const;
  void SetType(EGameObjectTypes _eType);

  template <typename T>
  T* AddComponent();

  template <typename T>
  T* GetComponent();

  /**
  *     Static methods
  */
  static CGameObject* Create();
  static void Destroy(CGameObject* _pGameObject);

protected:
  /**
  * Protected component so that game objects only can be created from Create() method
  */
  CGameObject();

private:

  std::vector<CComponent*> m_tComponents;
  bool m_bActive;
  EGameObjectTypes m_eType;

};

/**
*     Templates definition
*/
template <typename T>
T* CGameObject::AddComponent()
{
  T* pNewComponent = CComponent::Create<T>(this);
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