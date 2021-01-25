#pragma once
#include "Render/RenderableObject.h"
#include <string>


class CMap : public CRenderableObject
{

public:

  CMap();

  virtual void Render() const override;

  CVector2 GetLeftLimit() const;
  CVector2 GetRightLimit() const;

private:

  std::string m_sMap;
  CVector2 m_vSize;

};

