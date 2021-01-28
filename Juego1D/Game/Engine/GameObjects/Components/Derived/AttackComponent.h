#pragma once
#include "GameObjects/Components/Base/Component.h"

/**
 * @brief Componente de ataque encargado de spawnear las balas en funcion del input del jugador.
 */
class CAttackComponent : public CComponent
{
  /**
   *    Metodos
   */
public:

  CAttackComponent();
  virtual void Update(float _fDeltaTime) override;

private:

  void SpawnBullet(int _iDirection) const;


  /**
   *    Atributos
   */

  /**
   * @brief Tiempo entre disparo y disparo.
   */
  float m_fTimeBetweenAttacks;

  /**
   * @brief Variable para hacer la cuenta atras entre disparo y disparo.
   */
  float m_fTimeUntilNextAttack;

};

