#pragma once

#include "GameObjects/Components/Base/Component.h"

class CRenderComponent : public CComponent
{
public:

  CRenderComponent();

  virtual void OnCreation(CGameObject* _pOwner) override;

  virtual void Update(float _fDeltaTime) override;

  void SetSymbol(char _cSymbol);
  char GetSymbol() const;

private:

  char m_cSymbol;
};
