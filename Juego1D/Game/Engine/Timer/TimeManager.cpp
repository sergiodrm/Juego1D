#include "TimeManager.h"
#include <profileapi.h>

void CTimeManager::Init()
{
  CreateSingleton();
  GetSingleton().Init_Internal();
}

CTimeManager& CTimeManager::GetInstance()
{
  return GetSingleton();
}

void CTimeManager::Shutdown()
{
  DestroySingleton();
}

void CTimeManager::InitTimerToProcess()
{
  // Calcular los ciclos de contador entre el anterior frame y este
  LARGE_INTEGER iCurrentTime;
  QueryPerformanceCounter(&iCurrentTime);
  LARGE_INTEGER iElapsedTime;
  iElapsedTime.QuadPart = iCurrentTime.QuadPart - m_iPreviousTime.QuadPart;
  // Actualizar previous time y calcular el tiempo entre frames
  m_iPreviousTime = iElapsedTime;
  m_dTimeBetweenFrames = static_cast<double>(iElapsedTime.QuadPart) / static_cast<double>(m_iFrequency.QuadPart);
  m_dElapsedTime += m_dTimeBetweenFrames;

  // Si ha pasado mas tiempo del permitido, corregirlo.
  if (m_dElapsedTime > m_dMaxElapsedTime)
    m_dElapsedTime = m_dMaxElapsedTime;
}

bool CTimeManager::Update()
{
  // Comprobar que si se ha pasado el tiempo especificado entre frames.
  if (m_dElapsedTime > m_dFixedTick)
  {
    m_dElapsedTime -= m_dFixedTick;
    m_dTotalTime += m_dFixedTick;
    return true;
  }
  return false;
}

double CTimeManager::GetFixedTick() const
{
  return m_dFixedTick;
}


void CTimeManager::Init_Internal()
{
  QueryPerformanceFrequency(&m_iFrequency);
  QueryPerformanceCounter(&m_iPreviousTime);
  m_dFixedTick = 0.016;
  m_dMaxElapsedTime = 0.1;
  m_dElapsedTime = 0.0;
  m_dTimeBetweenFrames = 0.0;
  m_dTotalTime = 0.0;
}
