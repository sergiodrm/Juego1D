#pragma once

#include <string>

// Forward declaration
class CGameObject;

/**
 * @brief Clase escena donde se almacenara lo
 * relacionado con la zona de juego.
 */
class CScene
{
public:

  CScene(size_t _uSize = 50, char _cSpaceSymbol = '-');

  /**
   * @brief Imprimir la escena almacenada.
   */
  void Render();
  /**
   * @brief Actualizar la posicion de un game object en la escena.
   */
  void UpdateGameObjectInMap(CGameObject& _rGameObject);
  /**
   * @brief Limpiar el contenido de la escena.
   */
  void ClearScene();

  size_t GetSize() const;
  int GetPositionX() const;
  int GetPositionY() const;

private:

  /**
   * @brief Contenedor de la escena.
   */
  std::string m_sMap;
  /**
   * @brief Dimension de la escena.
   */
  size_t m_uSize;
  /**
   * @brief Simbolo de los espacios de la escena que no esten ocupados por un game object.
   */
  char m_cSpaceSymbol;
  /**
   * @brief Posicion de renderizado de la escena.
   */
  int m_iPositionX;
  int m_iPositionY;

};

