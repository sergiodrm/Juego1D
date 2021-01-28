#pragma once

#include "GameObjects/Components/Base/Component.h"

/**
 * @brief Componente de movimiento que modifica
 * el Transform del game object al que pertenezca.
 */
class CMovementComponent : public CComponent
{
public:

  CMovementComponent();

  virtual void Update(float _fDeltaTime) override;

  int GetMovementDirection() const;
  float GetSpeed() const;
  void SetSpeed(float _fSpeed);
  void SetMovementDirection(int _iMovementDirection);

  bool IsInputPlayerEnabled() const;
  void SetInputPlayerEnabled(bool _bInputPlayer);

private:
  /**
   * @brief Actualizacion de la direcion de movimiento a partir
   * del input recibido del jugador.
   */
  void UpdateInputVector();
  /**
   * @brief Actualizar el transform del game object en funcion
   * de la direccion de movimiento, el delta time y la velocidad.
   */
  void UpdateMovement(float _fDeltaTime);

  /**
   * @brief Velocidad de movimiento (unidad de espacio/segundo).
   */
  float m_fSpeed;
  /**
   * @brief Contador de posicion entre unidades de espacio.
   */
  float m_fPosition;
  /**
   * @brief Direccion de movimiento. Puede ser izquierda (-1), derecha (1) o quieto (0).
   */
  int m_iMovementDirection;
  /**
   * @brief Direccion de movimiento gobernada por el input del player.
   */
  bool m_bInputPlayer;
};

