#pragma once

#include "GameObjects/Components/Base/Component.h"
#include "Utilities/Vector2.h"

class CTransformComponent : public CComponent
{
public:

  CTransformComponent();

  CVector2 GetPosition() const;
  void SetPosition(const CVector2& _vPosition);
  void AddPosition(const CVector2& _vPosition);

private:

  CVector2 m_vPosition;

};
