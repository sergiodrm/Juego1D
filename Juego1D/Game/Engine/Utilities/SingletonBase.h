#pragma once

#define DECLARE_SINGLETON_CLASS(_CLASS)   \
private:                                  \
  friend ISingletonBase<_CLASS>;          \
  _CLASS() {}                             \
  _CLASS(const _CLASS&) = delete;         \
  void operator=(const _CLASS&) = delete


template <typename T>
class ISingletonBase
{
protected:

  static void CreateSingleton();
  static T& GetSingleton();
  static void DestroySingleton();

private:

  static T* m_pInstance;

};

/**
*     Template definition
*/
template <typename T>
T* ISingletonBase<T>::m_pInstance = nullptr;

template <typename T>
void ISingletonBase::CreateSingleton()
{
  if (m_pInstance == nullptr)
  {
    m_pInstance = new T();
  }
}

template <typename T>
T& ISingletonBase::GetSingleton()
{
  return *m_pInstance;
}

template <typename T>
void ISingletonBase::DestroySingleton()
{
  if (m_pInstance != nullptr)
  {
    delete m_pInstance;
    m_pInstance = nullptr;
  }
}
