#pragma once

#include "../Base/Component.h"

class CTransformComponent : public CComponent
{
public:

  CTransformComponent();

  void GetPosition(size_t& uPosX_, size_t& uPosY_) const;
  void SetPosition(size_t _uPosX, size_t _uPosY);
  void AddPosition(size_t _uPosX, size_t _uPosY);

private:

  size_t m_uPositionX;
  size_t m_uPositionY;

};
