#pragma once

#include "Utilities/Vector2.h"

class CRenderableObject
{
public:

  CRenderableObject(char _cSymbol = '-');

  CVector2 GetPosition() const;
  void SetPosition(const CVector2& _vPosition);
  char GetSymbol() const;
  void SetSymbol(char _cSymbol);

  virtual void Render() const;

  bool IsActive() const;
  void Active();
  void Deactive();

protected:

  char m_cSymbol;
  CVector2 m_vPosition;
  bool m_bActive;

};

