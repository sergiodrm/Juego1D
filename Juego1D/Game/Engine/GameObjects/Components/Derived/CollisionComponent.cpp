#include "CollisionComponent.h"
#include "TransformComponent.h"
#include "MovementComponent.h"
#include "GameObjects/GameObject.h"
#include "World/World.h"

CCollisionComponent::CCollisionComponent()
  : m_eTypeToIgnore(CGameObject::EGameObjectTypes::Invalid) {}

void CCollisionComponent::Update(float _fDeltaTime)
{
  // Comprobar que el game object esta dentro de los limites de la escena.

  // Unicamente se comprueba para game objects de tipo bala.
  if (GetOwner()->IsType(CGameObject::EGameObjectTypes::Bullet))
  {
    CTransformComponent* pTransformComponent = GetOwner()->GetComponent<CTransformComponent>();
    // Obtener la informacion de los limites por el gestor de entidades que contiene la escena.
    if (pTransformComponent->GetPosition() <= 0 || pTransformComponent->GetPosition() >= static_cast<int>(CWorld::GetInstance().GetScene().GetSize()))
    {
      // En caso de que el game object llegue a los limites, se introduce en la cola para desactivacion.
      CWorld::GetInstance().DeactiveGameObject(*GetOwner());
    }
  }
}

bool CCollisionComponent::Collides(CGameObject& _rOther) const
{
  if (_rOther.IsType(m_eTypeToIgnore))
    return false;

  // Obtener los componentes Transform de cada componente para comprobar la posicion y determinar si hay colision o no.
  CTransformComponent* pMyTransform = GetOwner()->GetComponent<CTransformComponent>();
  CTransformComponent* pOtherTransform = _rOther.GetComponent<CTransformComponent>();
  int iMyDirection = GetOwner()->GetComponent<CMovementComponent>()->GetMovementDirection();

  /**
   * Comprobar tanto la posicion actual como la siguiente (en la direccion de movimiento)
   * para evitar que se crucen los game objects si estan en posiciones contiguas.
   */
  bool bHasCollided = pMyTransform->GetPosition() == pOtherTransform->GetPosition() ||
    pMyTransform->GetPosition() + iMyDirection == pOtherTransform->GetPosition();
  return bHasCollided;
}

CGameObject::EGameObjectTypes CCollisionComponent::GetTypeToIgnore() const
{
  return m_eTypeToIgnore;
}

void CCollisionComponent::SetTypeToIgnore(CGameObject::EGameObjectTypes _eType)
{
  m_eTypeToIgnore = _eType;
}
