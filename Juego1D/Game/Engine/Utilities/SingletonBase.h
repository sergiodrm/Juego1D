#pragma once

/**
 * @brief Macro para declarar el constructor de la clase privado y
 * eliminar el constructor copia y el operador de asignacion.
 */
#define DECLARE_SINGLETON_CLASS(_CLASS)   \
private:                                  \
  friend ISingletonBase<_CLASS>;          \
  _CLASS() {}                             \
  _CLASS(const _CLASS&) = delete;         \
  void operator=(const _CLASS&) = delete

/**
 * @brief Base de un diseño singleton implementado con templates para
 * que se pueda adaptar a cualquier clase.
 */
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
*     Definicion de los metodos
*/
template <typename T>
T* ISingletonBase<T>::m_pInstance = nullptr;

template <typename T>
void ISingletonBase<T>::CreateSingleton()
{
  if (m_pInstance == nullptr)
  {
    m_pInstance = new T();
  }
}

template <typename T>
T& ISingletonBase<T>::GetSingleton()
{
  return *m_pInstance;
}

template <typename T>
void ISingletonBase<T>::DestroySingleton()
{
  if (m_pInstance != nullptr)
  {
    delete m_pInstance;
    m_pInstance = nullptr;
  }
}
