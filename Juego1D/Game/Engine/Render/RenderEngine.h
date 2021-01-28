#pragma once

#include "Utilities/SingletonBase.h"

// Formato de funcion para printear la escena desde el gestor de entidades.
typedef void (*DrawWorldFunction)();

/**
 * @brief Manager para gestionar las tareas de renderizado.
 * Este gestor se encarga de borrar la pantalla y volver a dibujar
 * el contenido actualizado a traves de un puntero a funcion externo.
 */
class CRenderEngine : public ISingletonBase<CRenderEngine>
{
  DECLARE_SINGLETON_CLASS(CRenderEngine);

public:

  /**
   *    Metodos del singleton.
   */
  static void Init();
  static CRenderEngine& GetInstance();
  static void Shutdown();

  /**
   *    Render API
   */

  /**
   * @brief Metodo para renderizar la escena.
   */
  void Render() const;
  /**
   * @brief Cambiar la funcion externa de renderizado de la escena.
   */
  void SetDrawWorldFunction(DrawWorldFunction _pDrawFunction);

  /**
   * @brief Printear una cadena en una posicion especifica.
   */
  static void Print(const char* _sStringToPrint, int _iPosX, int _iPosY);

private:

  /**
   * Inicializacion y destruccion internal llamadas desde la inicializacion del singleton.
   */
  void Init_Internal();
  void Shutdown_Internal();

  /**
   * @brief Borrar el contenido actual de la consola.
   */
  static void ClearScreen();


private:

  /**
   *  @brief Puntero a funcion externa que se llamara durante la fase de renderizado tras limpiar la consola.
   */
  DrawWorldFunction m_pDrawWorldFunction;
};

