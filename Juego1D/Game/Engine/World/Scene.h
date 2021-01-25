#pragma once


class CScene
{
public:

  explicit CScene(int _iNumBullets = 5, int _iNumEnemies = 10);
  void Init();
  void Shutdown();

private:

  const int m_iNumberOfBullets;
  const int m_iNumberOfEnemies;
};

