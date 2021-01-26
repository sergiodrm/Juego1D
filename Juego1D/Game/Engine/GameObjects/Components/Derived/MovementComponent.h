#pragma once

#include "GameObjects/Components/Base/Component.h"

class CMovementComponent : public CComponent
{
public:

  CMovementComponent();

  virtual void Update(float _fDeltaTime) override;

  void Active() override;

  int GetMovementDirection() const;
  float GetSpeed() const;
  void SetSpeed(float _fSpeed);
  void SetMovementDirection(int _iMovementDirection);

  bool IsInputPlayerEnable() const;
  void SetInputPlayerEnable(bool _bInputPlayer);

private:

  void UpdateInputVector();
  void UpdateMovement(float _fDeltaTime);

  float m_fSpeed;
  float m_fPosition;
  int m_iMovementDirection;
  bool m_bInputPlayer;
};

