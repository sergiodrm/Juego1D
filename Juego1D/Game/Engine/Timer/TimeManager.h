#pragma once
#include "Utilities/SingletonBase.h"
#include <Windows.h>



class CTimeManager : public ISingletonBase<CTimeManager>
{
  DECLARE_SINGLETON_CLASS(CTimeManager);

public:

  static void Init();
  static CTimeManager& GetInstance();
  static void Shutdown();

  void InitTimerToProcess();
  bool Update();

private:

  void Init_Internal();

private:

  LARGE_INTEGER m_iFrequency;
  LARGE_INTEGER m_iPreviousTime;
  double m_dFixedTick;
  double m_dMaxElapsedTime;
  double m_dElapsedTime;
  double m_dTotalTime;
  double m_dTimeBetweenFrames;
};

