#pragma once

class CVector2
{
public:

  CVector2();
  CVector2(float _fX, float _fY);

  float GetX() const;
  float GetY() const;
  void SetX(float _fX);
  void SetY(float _fY);

  CVector2& operator+(const CVector2 _other);
  CVector2& operator+=(const CVector2 _other);

private:

  float m_fX;
  float m_fY;
};

