#pragma once

#include <string>


class CGameObject;

class CScene
{

public:

  CScene();

  void Render();
  void UpdateGameObjectInMap(CGameObject& _rGameObject);
  void ClearScene();

private:

  std::string m_sMap;

};

