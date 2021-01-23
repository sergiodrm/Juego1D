#pragma once

class CRenderableObject
{
public:

  CRenderableObject(char _cSymbol = '-');

  void Render() const;

  void operator=(char _cSymbol);

private:

  char m_cSymbol;

};

