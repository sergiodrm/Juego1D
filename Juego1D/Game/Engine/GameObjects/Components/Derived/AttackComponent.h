#pragma once
#include "GameObjects/Components/Base/Component.h"

class CAttackComponent : public CComponent
{
public:

  CAttackComponent();

  virtual void Update(float _fDeltaTime) override;

private:

  void SpawnBullet(int _iDirection) const;

};

