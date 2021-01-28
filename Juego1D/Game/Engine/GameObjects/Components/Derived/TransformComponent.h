#pragma once

#include "GameObjects/Components/Base/Component.h"

/**
 * @brief Componente transform para indicar la posicion del game object en el mundo.
 */
class CTransformComponent : public CComponent
{
public:

  CTransformComponent();

  int GetPosition() const;
  void SetPosition(int _iPosition);
  void AddPosition(int _iPosition);

private:
  /**
   * @brief Posicion del game object representado como un indice dentro del array de la escena.
   */
  int m_iPosition;

};
