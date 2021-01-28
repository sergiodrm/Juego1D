#pragma once

#include "GameObjects/Components/Base/Component.h"

/**
 * @brief Componente de render encargado de la parte grafica del game object.
 */
class CRenderComponent : public CComponent
{
public:

  CRenderComponent();
  virtual void Update(float _fDeltaTime) override;

  void SetSymbol(char _cSymbol);
  char GetSymbol() const;

private:
  /**
   * @brief Caracter que se imprimira en pantalla a la hora de representar el game object.
   */
  char m_cSymbol;
};
