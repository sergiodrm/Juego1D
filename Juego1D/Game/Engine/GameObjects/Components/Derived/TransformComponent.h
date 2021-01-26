#pragma once

#include "GameObjects/Components/Base/Component.h"

class CTransformComponent : public CComponent
{
public:

  CTransformComponent();

  int GetPosition() const;
  void SetPosition(int _iPosition);
  void AddPosition(int _iPosition);

private:

  int m_iPosition;

};
