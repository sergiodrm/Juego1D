#pragma once
#include "Utilities/SingletonBase.h"
#include <Windows.h>


/**
 * @brief Gestor de tiempo.
 */
class CTimeManager : public ISingletonBase<CTimeManager>
{
  DECLARE_SINGLETON_CLASS(CTimeManager);

public:

  /**
   * Metodos del singleton
   */
  static void Init();
  static CTimeManager& GetInstance();
  static void Shutdown();

  /**
   * @brief Preparar los contadores de tiempo.
   * Este metodo debe llamarse antes de la fase de actualizacion de la logica.
   */
  void InitTimerToProcess();
  /**
   * @brief Actualizacion del gestor, donde se calculara el elapsed time y se
   * devolvera si ha pasado el tiempo de actualizacion de logica o no.
   */
  bool Update();

  /**
   * @brief Devolver un paso constante de tiempo.
   */
  double GetFixedTick() const;

private:

  void Init_Internal();

private:

  /**
   * @brief Frecuencia de reloj del ordenador.
   */
  LARGE_INTEGER m_iFrequency;
  /**
   * @brief Ciclos de contador de la anterior iteracion.
   */
  LARGE_INTEGER m_iPreviousTime;
  /**
   * @brief Paso de tiempo fijo entre frames para la logica.
   */
  double m_dFixedTick;
  /**
   * @brief Maximo tiempo permitido entre frames.
   */
  double m_dMaxElapsedTime;
  /**
   * @brief Tiempo pasado entre frames acumulado.
   */
  double m_dElapsedTime;
  /**
   * @brief Tiempo total que ha pasado desde la creacion de la instancia.
   */
  double m_dTotalTime;
  /**
   * @brief Tiempo entre frames.
   */
  double m_dTimeBetweenFrames;
};

