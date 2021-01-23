#pragma once

#include "../Base/Component.h"

class CTransformComponent : public CComponent
{
public:

  CTransformComponent();

  size_t GetPosition() const;
  void SetPosition(size_t _uPosition);
  void AddPosition(size_t _uOffset);

private:

  size_t m_uPosition;

};
