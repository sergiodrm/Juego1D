#pragma once
#pragma warning(disable : 4100)

#include "Utilities/MacroUtility.h"

// Forward declaration
class CGameObject;

/**
 * @brief Clase base "Component" la cual contiente los metodos de
 * creacion y destruccion de componentes y otr
 */
class CComponent
{
  BASE_CLASS(CComponent);

public:

  virtual ~CComponent();

  /**
   * @brief Evento llamado en la creacion del componente.
   */
  virtual void OnCreation(CGameObject* _pOwner);
  /**
   * @brief Evento llamado en la destruccion del componente.
   */
  virtual void OnDestroy();

  /**
   * @brief Metodo de actualizacion del componente llamado durante la fase de actualizacion de la logica.
   */
  virtual void Update(float _fDeltaTime);

  /**
   * @brief Devolver el game object al cual pertenece el componente.
   */
  CGameObject* GetOwner() const;

  /**
   * Metodos de activacion del componente durante el tiempo de juego.
   */
  virtual void Active();
  virtual void Deactive();
  bool IsActive() const;

  /**
   * @brief Metodo estatico encargado de la creacion de componentes.
   * Se crea el componente deseado a partir de la plantilla y se llaman al evento
   * OnCreate() y otros metodos por defecto. Se debe especificar el game object
   * al que se va a ligar el componente instanciado.
   */
  template <typename T>
  static T* Create(CGameObject* _pOwner);
  /**
   * @brief Metodo estatico encargado de la destruccion de componentes.
   * Antes de la destruccion se llama al evento OnDestroy().
   */
  static void Destroy(CComponent* _pComponent);

protected:

  /**
   * Constructor protegido para evitar crear componentes fuera de la clase.
   * El encargado de instanciar componentes es el metodo Create.
   */
  CComponent()
    : m_pOwner(nullptr), m_bActive(false)
  {}

private:

  /**
   * @brief Game object al que pertenece el componente instanciado.
   */
  CGameObject* m_pOwner;

  /**
   * @brief Componente activo o no activo.
   */
  bool m_bActive;

};




/**
 *  -----------------------
 *  Definicion de templates
 *  -----------------------
 */

template <typename T>
T* CComponent::Create(CGameObject* _pOwner)
{
  ensure(_pOwner != nullptr);
  T* pNewComponent = new T();
  ensure_msg(pNewComponent != nullptr, "Failed creating new component.");
  pNewComponent->OnCreation(_pOwner);
  return pNewComponent;
}
