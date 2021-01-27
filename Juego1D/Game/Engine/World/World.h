#pragma once

#include "Utilities/SingletonBase.h"
#include "GameObjects/GameObject.h"
#include "Scene.h"
#include <vector>
#include <queue>

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

  /**
   *    Methods
   */
public:

  /**
   * Singleton wrapper
   */
  static void Init();
  static CWorld& GetInstance();
  static void Shutdown();

  /**
   * World API
   */
  void Update();
  static void DrawWorld();

  void InsertGameObject(CGameObject& _rGameObject);
  bool SpawnGameObject(SSpawnInfo& _rSpawnInfo);
  void ActiveGameObject(CGameObject& _rGameObject);
  void DeactiveGameObject(CGameObject& _rGameObject);
  CScene& GetScene();
  bool GameOver() const;

  /**
   * Private methods
   */
private:

  void Init_Internal();
  void EnemySpawnerSlot(float _fDeltaTime);
  void UpdateGameObjects(float _fDeltaTime);
  void ResolveGameObjectsActivation();
  void ResolveCollisions();
  void Shutdown_Internal();
  CGameObject* FindGameObjectByType(CGameObject::EGameObjectTypes _eType, bool _bIsActive = false) const;
  bool CheckValidSpawn(SSpawnInfo& _rSpawnInfo) const;
  void DrawWorld_Internal();

  /**
   * Properties
   */

  int m_iNumberOfBullets;
  int m_iNumberOfEnemies;

  /**
   * @brief Array of game objects whose update method will be call in Update logic manager method
   */
  std::vector<CGameObject*> m_tGameObjects;
  std::queue<CGameObject*> m_gameObjectsToActive;
  std::queue<CGameObject*> m_gameObjectsToDeactive;

  CScene m_scene;
  float m_fTimeBetweenEnemySpawn;
  float m_fTimeUntilNextSpawn;
  float m_fEnemySpawnProb;
};

