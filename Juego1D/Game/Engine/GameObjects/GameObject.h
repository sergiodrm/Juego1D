#pragma once

#include <vector>

// Forward declaration
class CComponent;

/**
 * @brief Game object base para todas las entidades que se deseen introducir en la escena.
 */
class CGameObject
{

public:

  /**
   * @brief Tipos de game objects posibles.
   */
  enum EGameObjectTypes : int
  {
    Invalid = -1,
    Player, Enemy, Bullet
  };

  /**
  *     Metodos
  */
public:

  ~CGameObject();

  /**
   * @brief Evento llamado en la creacion del game object. Aqui se construye el game object
   * con el componente Transform por defecto.
   */
  void OnCreation();
  /**
   * @brief Evento llamado en la destruccion del game object.
   */
  void OnDestroy();
  /**
   * @brief Actualizacion del game object donde se llamara a la actualizacion de los componentes
   * que lo formen.
   */
  void Update(float _fDeltaTime);

  /**
   * Metodos de activacion del game object.
   */
  void Active();
  void Deactive();
  bool IsActive() const;

  /**
   * Metodos de identificacion del game object.
   */
  EGameObjectTypes GetType() const;
  bool IsType(EGameObjectTypes _eType) const;
  void SetType(EGameObjectTypes _eType);

  /**
   * @brief Metodo plantilla para añadir un componente nuevo al game object.
   */
  template <typename T>
  T* AddComponent();

  /**
   * @brief Metodo plantilla para buscar y devolver el componente especificado por el tipo en la llamada.
   */
  template <typename T>
  T* GetComponent();

  /**
   * @brief Metodo de creacion de entidades donde se llama al evento OnCreate por defecto para construir la instancia debidamente
   * y añadirla a la lista de game objects del gestor de entidades World.
   */
  static CGameObject* Create();
  /**
   * @brief Metodo de destruccion de entidades donde se llama al evento OnDestroy por defecto.
   */
  static void Destroy(CGameObject* _pGameObject);

protected:
  /**
  * Constructor protegido para evitar crear instancias fuera de la clase. Para crear instancias usar Create().
  */
  CGameObject();

private:

  /**
   * @brief Vector de componentes que forman el game object
   */
  std::vector<CComponent*> m_tComponents;
  /**
   * @brief Estado del game object.
   */
  bool m_bActive;
  /**
   * @brief Tipo de game object.
   */
  EGameObjectTypes m_eType;

};

/**
 *  -----------------------
 *  Definicion de templates
 *  -----------------------
 */

template <typename T>
T* CGameObject::AddComponent()
{
  // Crear el componente pasando el puntero a la instancia para ligarlo con el game object actual.
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