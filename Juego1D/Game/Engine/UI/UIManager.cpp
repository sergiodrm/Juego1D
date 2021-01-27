#include "UIManager.h"
#include "World/World.h"
#include "Render/RenderEngine.h"

void CUIManager::Init()
{
  CreateSingleton();
  GetSingleton().Init_Internal();
}

CUIManager& CUIManager::GetInstance()
{
  return GetSingleton();
}

void CUIManager::Shutdown()
{
  GetSingleton().Shutdown_Internal();
  DestroySingleton();
}

void CUIManager::Render() const
{
  int iPosX = CWorld::GetInstance().GetScene().GetPositionX() + static_cast<int>(CWorld::GetInstance().GetScene().GetSize()) + 2;
  int iPosY = CWorld::GetInstance().GetScene().GetPositionY();
  char sScreenInfo[5];
  sprintf_s(sScreenInfo, "%.2d", m_iEnemyCounter);
  CRenderEngine::Print(sScreenInfo, iPosX, iPosY);
}

void CUIManager::EnemyDead()
{
  m_iEnemyCounter++;
}

void CUIManager::Init_Internal()
{
  m_iEnemyCounter = 0;
}

void CUIManager::Shutdown_Internal()
{
  CRenderEngine::Print("GAME OVER\n\n", 10, 2);
}
