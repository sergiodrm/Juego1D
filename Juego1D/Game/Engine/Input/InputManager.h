#pragma once

#include "Utilities/SingletonBase.h"

#define KEYBOARD_J 'J'
#define KEYBOARD_L 'L'
#define KEYBOARD_A 'A'
#define KEYBOARD_D 'D'

typedef unsigned char Key;

class CInputManager : public ISingletonBase<CInputManager>
{
  DECLARE_SINGLETON_CLASS(CInputManager);

public:

  static void Init();
  static CInputManager& GetInstance();
  static void Shutdown();

  bool IsKeyPressed(Key _key);

};