#pragma once

// Forward declaration
class CGameObject;

class CComponent
{
public:

  virtual void Init();
  virtual void Update(float _fDeltaTime);
  virtual void Terminate();

  CGameObject* GetOwner() const;


private:

  CGameObject* m_pOwner;

};

