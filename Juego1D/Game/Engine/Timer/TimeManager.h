#pragma once
#include "Utilities/SingletonBase.h"


class CTimeManager : public ISingletonBase<CTimeManager>
{
  DECLARE_SINGLETON_CLASS(CTimeManager);


  double m_dPreviousTime;
};

