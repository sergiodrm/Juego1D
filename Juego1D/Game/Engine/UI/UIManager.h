#pragma once

#include "Utilities/SingletonBase.h"

/**
 * @brief Gestor de la interfaz de usuario.
 */
class CUIManager : public ISingletonBase<CUIManager>
{
  DECLARE_SINGLETON_CLASS(CUIManager);

public:

  /**
   * Metodos del singleton
   */
  static void Init();
  static CUIManager& GetInstance();
  static void Shutdown();

  /**
   * @brief Fase de renderizado de la interfaz.
   */
  void Render() const;
  /**
   * @brief Metodo para informar de que un enemigo ha sido eliminado.
   */
  void EnemyDead();

private:

  void Init_Internal();
  void Shutdown_Internal();

  /**
   * @brief Contador de enemigos eliminados.
   */
  int m_iEnemyCounter;
};

