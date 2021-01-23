#include "RenderableObject.h"
#include <cstdio>

void CRenderableObject::Render() const
{
  printf("%c", m_cSymbol);
}
