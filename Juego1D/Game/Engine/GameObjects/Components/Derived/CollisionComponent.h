#pragma once

#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Base/Component.h"

class CCollisionComponent : public CComponent
{
public:

  CCollisionComponent();

  void Update(float _fDeltaTime) override;
  bool Collides(CGameObject& _rOther) const;

  CGameObject::EGameObjectTypes GetTypeToIgnore() const;
  void SetTypeToIgnore(CGameObject::EGameObjectTypes _eType);

private:

  CGameObject::EGameObjectTypes m_eTypeToIgnore;

};

