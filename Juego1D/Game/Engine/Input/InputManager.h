#pragma once

#include "Utilities/SingletonBase.h"

/**
 * Definicion de macros para representacion de teclas.
 */
#define KEYBOARD_J 'J'
#define KEYBOARD_L 'L'
#define KEYBOARD_A 'A'
#define KEYBOARD_D 'D'

typedef unsigned char Key;

/**
 * @brief Gestor de input para captar las acciones del player.
 * Sigue una arquitectura singleton para evitar que haya mas de una
 * instancia del gestor.
 */
class CInputManager : public ISingletonBase<CInputManager>
{
  DECLARE_SINGLETON_CLASS(CInputManager);

public:

  /**
   * Metodos de manejo del singleton.
   */
  static void Init();
  static CInputManager& GetInstance();
  static void Shutdown();

  /**
   * @brief Comprobar si una tecla esta pulsada.
   */
  bool IsKeyPressed(Key _key);

};