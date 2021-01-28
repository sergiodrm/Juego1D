#pragma once

#include "Utilities/SingletonBase.h"
#include "GameObjects/GameObject.h"
#include "Scene.h"
#include <vector>
#include <queue>

// Forward declaration
class CGameObject;

/**
 * @brief Estructura de datos para informacion del spawn
 */
struct SSpawnInfo
{
  CGameObject::EGameObjectTypes m_eType;
  int m_iPosition;
  int m_iDirection;
  char m_cSymbol;
};

/**
 * @brief Gestor de game object y de control del loop game de logica.
 */
class CWorld : public ISingletonBase<CWorld>
{
  DECLARE_SINGLETON_CLASS(CWorld);

  /**
   * Metodos
   */
public:

  /**
   * Metodos del singleton.
   */
  static void Init();
  static CWorld& GetInstance();
  static void Shutdown();

  /**
   * @brief Actualizacion del mundo.
   */
  void Update();
  /**
   * @brief Funcion de renderizado del mundo. Se llama desde el render engine 
   */
  static void DrawWorld();

  /**
   * @brief Añadir un game object al mundo.
   */
  void InsertGameObject(CGameObject& _rGameObject);
  /**
   * @brief Activar un game object inactivo en el mundo con una informacion determinada.
   */
  bool SpawnGameObject(SSpawnInfo& _rSpawnInfo);
  /**
   * @brief Activar un game object inactivo.
   */
  void ActiveGameObject(CGameObject& _rGameObject);
  /**
   * @brief Desactivar un game object inactivo.
   */
  void DeactiveGameObject(CGameObject& _rGameObject);
  /**
   * @brief Devolver la escena del mundo.
   */
  CScene& GetScene();
  /**
   * @brief Comprobar si se ha acabado el juego chequeando el estado del jugador.
   */
  bool GameOver() const;

private:

  void Init_Internal();
  void Shutdown_Internal();
  /**
   * @brief Gestionar el spawn de los enemigos por los laterales.
   */
  void EnemySpawnerSlot(float _fDeltaTime);
  /**
   * @brief Actualizacion de los game objects del mundo.
   */
  void UpdateGameObjects(float _fDeltaTime);
  /**
   * @brief Resolver los game objects pendientes de activacion o desactivacion.
   */
  void ResolveGameObjectsActivation();
  /**
   * @brief Comprobacion de colisiones.
   */
  void ResolveCollisions();
  /**
   * @brief Busqueda de un game object por tipo y estado.
   */
  CGameObject* FindGameObjectByType(CGameObject::EGameObjectTypes _eType, bool _bIsActive = false) const;
  /**
   * @brief Chequeo si es valida la informacion de spawn en funcion del estado del mundo.
   */
  bool CheckValidSpawn(SSpawnInfo& _rSpawnInfo) const;
  /**
   * @brief Metodo de renderizado del mundo.
   */
  void DrawWorld_Internal();

  /**
   * Atributos ---
   */
  /**
   * @brief Numero de balas que se crearan en el mundo.
   */
  int m_iNumberOfBullets;
  /**
   * @brief Numero de enemigos que se crearan en el mundo.
   */
  int m_iNumberOfEnemies;

  /**
   * @brief Contenedor con todos los game objects del mundo.
   */
  std::vector<CGameObject*> m_tGameObjects;
  /**
   * @brief Cola de game objects pendientes de activar.
   */
  std::queue<CGameObject*> m_gameObjectsToActive;
  /**
   * @brief Cola de game objects pendientes de desactivar.
   */
  std::queue<CGameObject*> m_gameObjectsToDeactive;

  /**
   * @brief Instancia de la escena.
   */
  CScene m_scene;

  /**
   * @brief Tiempo entre spawn de enemigos.
   */
  float m_fTimeBetweenEnemySpawn;
  /**
   * @brief Contador para comprobar cuando se puede spawnear el siguiente enemigo.
   */
  float m_fTimeUntilNextSpawn;
  /**
   * @brief Probabilidad de spawn de un enemigo.
   */
  float m_fEnemySpawnProb;
};

