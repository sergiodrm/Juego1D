#pragma once

#include "Utilities/SingletonBase.h"
#include <vector>

// Forward declaration
class CRenderableObject;

class CRenderEngine : public ISingletonBase<CRenderEngine>
{
  DECLARE_SINGLETON_CLASS(CRenderEngine);

public:

  /**
   *    Singleton wrapper
   */
  static void Init();
  static CRenderEngine& GetInstance();
  static void Shutdown();

  /**
   *    Render API
   */
  void Render();

private:

  void Init_Internal();
  void Shutdown_Internal();
  static void ClearScreen();


  /**
   *    Properties
   */
private:

  std::vector<CRenderableObject*> m_tRenderableObjects;

};

