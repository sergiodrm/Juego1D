#pragma once

#include "GameObjects/Components/Base/Component.h"
#include "Utilities/Vector2.h"


class CMovementComponent : public CComponent
{
public:

  CMovementComponent();

  virtual void Update(float _fDeltaTime) override;

  CVector2 GetMovementDirection() const;
  float GetSpeed() const;
  void SetSpeed(float _fSpeed);
  void SetMovementDirection(const CVector2& _vMovementDirection);

  bool IsInputPlayerEnable() const;
  void SetInputPlayerEnable(bool _bInputPlayer);

private:

  void UpdateInputVector();
  void UpdateMovement(float _fDeltaTime) const;

  float m_fSpeed;
  CVector2 m_vMovementDirection;
  bool m_bInputPlayer;
};

