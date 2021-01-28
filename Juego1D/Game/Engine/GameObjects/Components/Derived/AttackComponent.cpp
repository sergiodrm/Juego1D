#include "AttackComponent.h"
#include "Input/InputManager.h"
#include "World/World.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/Derived/TransformComponent.h"


CAttackComponent::CAttackComponent()
  : m_fTimeBetweenAttacks(1.2f), m_fTimeUntilNextAttack(0.f) {}

void CAttackComponent::Update(float _fDeltaTime)
{
  // Chequear si ha pasado el tiempo entre disparos
  if (m_fTimeUntilNextAttack == 0.f)
  {
    // Comprobar si se ha pulsado alguna tecla asignada al disparo
    int iDirection = 0;
    if (CInputManager::GetInstance().IsKeyPressed(KEYBOARD_J))
    {
      iDirection = -1;
    }
    else if (CInputManager::GetInstance().IsKeyPressed(KEYBOARD_L))
    {
      iDirection = 1;
    }
    // En caso de detectar input, spawnear bala
    if (iDirection != 0)
    {
      SpawnBullet(iDirection);
      // Una vez spawneada, cambiar variable contador para empezar la cuenta atras
      m_fTimeUntilNextAttack = m_fTimeBetweenAttacks;
    }
  }
  else
  {
    // Cuenta atras
    m_fTimeUntilNextAttack -= _fDeltaTime;
    if (m_fTimeUntilNextAttack < 0.f)
      m_fTimeUntilNextAttack = 0.f;
  }
}

void CAttackComponent::SpawnBullet(int _iDirection) const
{
  // Rellenar la informacion de spawn para enviarsela a la instancia de World.
  SSpawnInfo spawnInfo;
  spawnInfo.m_eType = CGameObject::EGameObjectTypes::Bullet;
  spawnInfo.m_iDirection = _iDirection;
  spawnInfo.m_iPosition = GetOwner()->GetComponent<CTransformComponent>()->GetPosition();
  spawnInfo.m_cSymbol = _iDirection == -1 ? '<' : '>';
  // Solicitar spawn al gestor de game objects.
  CWorld::GetInstance().SpawnGameObject(spawnInfo);
}

