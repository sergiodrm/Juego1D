#include "Scene.h"
#include "GameObjects/Components/Derived/TransformComponent.h"
#include "GameObjects/Components/Derived/RenderComponent.h"
#include <Windows.h>
#include <consoleapi2.h>
#include <cstdio>

#include "GameObjects/GameObject.h"

CScene::CScene()
{
  m_sMap.insert(m_sMap.begin(), 50, '-');
}

void CScene::Render()
{
  COORD currentPosition;
  currentPosition.X = 10;
  currentPosition.Y = 0;
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
  for (size_t uIndex = 0; uIndex < m_sMap.size(); ++uIndex)
  {
    m_sMap[uIndex] = '-';
  }
}
