#pragma once

#include "Utilities/SingletonBase.h"
#include <vector>

// Forward declaration
class CGameObject;

class CLogicManager : public ISingletonBase<CLogicManager>
{
  DECLARE_SINGLETON_CLASS(CLogicManager);

public:

  /**
   *    Singleton wrapper
   */
  static void Init();
  static CLogicManager& GetInstance();
  static void Shutdown();

  /**
   *    Logic manager API
   */
  void Update(float _fDeltaTime);
};

