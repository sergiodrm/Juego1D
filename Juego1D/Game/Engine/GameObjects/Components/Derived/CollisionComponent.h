#pragma once

#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Base/Component.h"

/**
 * @brief Componente de colision para controlar las colisiones entre entidades
 * o con los limites de la escena.
 */
class CCollisionComponent : public CComponent
{
public:

  CCollisionComponent();

  void Update(float _fDeltaTime) override;

  /**
   * @brief Comprobar la colision con otro game object.
   */
  bool Collides(CGameObject& _rOther) const;

  /**
   * @brief Devolver el tipo de game object que se ignora durante el chequeo de colisiones.
   */
  CGameObject::EGameObjectTypes GetTypeToIgnore() const;
  /**
   * @brief Cambiar el tipo de game object que se ignora durante el chequeo de colisiones.
   */
  void SetTypeToIgnore(CGameObject::EGameObjectTypes _eType);

private:

  /**
   * @brief Tipo de game object que se ignora durante el chequeo de colisiones.
   */
  CGameObject::EGameObjectTypes m_eTypeToIgnore;

};

