#include "Scene.h"
#include "GameObjects/Components/Derived/TransformComponent.h"
#include "GameObjects/Components/Derived/RenderComponent.h"
#include <Windows.h>
#include <consoleapi2.h>
#include <cstdio>

#include "GameObjects/GameObject.h"

CScene::CScene(size_t _uSize, char _cSpaceSymbol)
  : m_uSize(_uSize), m_cSpaceSymbol(_cSpaceSymbol)
{
  m_sMap.insert(m_sMap.begin(), m_uSize, m_cSpaceSymbol);
  m_iPositionX = 10;
  m_iPositionY = 1;
}

void CScene::Render()
{
  COORD currentPosition;
  currentPosition.X = static_cast<SHORT>(m_iPositionX);
  currentPosition.Y = static_cast<SHORT>(m_iPositionY);
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentPosition);
  printf("%s", m_sMap.c_str());
  ClearScene();
}

void CScene::UpdateGameObjectInMap(CGameObject& _rGameObject)
{
  CTransformComponent* pTransformComponent = _rGameObject.GetComponent<CTransformComponent>();
  CRenderComponent* pRenderComponent = _rGameObject.GetComponent<CRenderComponent>();
  int iPosition = pTransformComponent->GetPosition();
  char cSymbol = pRenderComponent->GetSymbol();
  if (iPosition >= 0 && iPosition < static_cast<int>(m_sMap.size()))
  {
    m_sMap[iPosition] = cSymbol;
  }
}

void CScene::ClearScene()
{
  for (size_t uIndex = 0; uIndex < m_uSize; ++uIndex)
  {
    m_sMap[uIndex] = m_cSpaceSymbol;
  }
}

size_t CScene::GetSize() const
{
  return m_uSize;
}

int CScene::GetPositionX() const
{
  return m_iPositionX;
}

int CScene::GetPositionY() const
{
  return m_iPositionX;
}
