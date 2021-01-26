#pragma once

#include "Utilities/SingletonBase.h"
#include "Scene.h"
#include <vector>
#include "Utilities/Vector2.h"
#include "GameObjects/GameObject.h"

// Forward declaration
class CGameObject;

/**
 * Spawn data struct
 */
struct SSpawnInfo
{
  CGameObject::EGameObjectTypes m_eType;
  int m_iPosition;
  int m_iDirection;
  char m_cSymbol;
};

class CWorld : public ISingletonBase<CWorld>
{
  DECLARE_SINGLETON_CLASS(CWorld);
public:

  static void Init();
  static CWorld& GetInstance();
  static void Shutdown();

  void Update();
  static void DrawWorld();

  void InsertGameObject(CGameObject& _rGameObject);
  bool SpawnGameObject(SSpawnInfo& _rSpawnInfo);
  CScene& GetScene();

private:

  void Init_Internal();
  void UpdateGameObjects(float _fDeltaTime);
  void Shutdown_Internal();
  CGameObject* FindGameObjectByType(CGameObject::EGameObjectTypes _eType, bool _bIsActive = false);
  void DrawWorld_Internal();

  int m_iNumberOfBullets;
  int m_iNumberOfEnemies;

  /**
   * @brief Array of game objects whose update method will be call in Update logic manager method
   */
  std::vector<CGameObject*> m_tGameObjects;

  CScene m_scene;
};

