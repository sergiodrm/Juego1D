#pragma once

#include "GameObjects/Components/Base/Component.h"
#include "Render/RenderableObject.h"
#include "Utilities/MacroUtility.h"

class CRenderComponent : public CComponent
{
public:

  CRenderComponent();

  virtual void OnCreation(CGameObject* _pOwner) override;

  virtual void Update(float _fDeltaTime) override;

  void SetSymbol(char _cSymbol);

private:

  /**
   * @brief Render property which will be called by Render engine in render slot.
   */
  CRenderableObject m_renderableObject;
  
  
};
