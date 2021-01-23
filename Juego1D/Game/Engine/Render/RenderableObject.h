#pragma once

class CRenderableObject
{
public:

  CRenderableObject(char _cSymbol = '-');

  void GetPosition(size_t& uPosX_, size_t& uPosY_) const;
  void SetPosition(size_t _uPosX, size_t _uPosY);
  char GetSymbol() const;
  void SetSymbol(char _cSymbol);

  void Render() const;

  void operator=(char _cSymbol);

private:

  char m_cSymbol;
  size_t m_uPositionX;
  size_t m_uPositionY;

};

