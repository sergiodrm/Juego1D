#pragma once

#include "Utilities/SingletonBase.h"

class CUIManager : public ISingletonBase<CUIManager>
{
  DECLARE_SINGLETON_CLASS(CUIManager);

public:

  /**
   * Singleton wrapper
   */
  static void Init();
  static CUIManager& GetInstance();
  static void Shutdown();

  /**
   * UI API
   */
  void Render() const;

  void EnemyDead();

private:

  void Init_Internal();
  void Shutdown_Internal();

  int m_iEnemyCounter;
};

