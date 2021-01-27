#pragma once

#include <string>


class CGameObject;

class CScene
{

public:

  CScene(size_t _uSize = 50, char _cSpaceSymbol = '-');

  void Render();
  void UpdateGameObjectInMap(CGameObject& _rGameObject);
  void ClearScene();
  size_t GetSize() const;
  int GetPositionX() const;
  int GetPositionY() const;

private:

  std::string m_sMap;

  size_t m_uSize;
  char m_cSpaceSymbol;
  int m_iPositionX;
  int m_iPositionY;

};

