#ifndef __7842F_LIB_H
#define __7842F_LIB_H






#ifdef _7842F_USE_SMA
#include "Filter/smaFilter.c"
#endif

#ifdef _7842F_USE_EMA
#include "Filter/emaFilter.c"
#endif



#include "PID/PIDSystem.h"

#ifdef _7842F_USE_PID
#include "PID/PIDSystem.c"
#endif

#ifdef _7842F_USE_PID_EMA
#include "PID/PIDEMASystem.c"
#endif








#ifdef _7842F_USE_RPM
#include "Other/RPMSystem.c"
#endif

#ifdef _7842F_USE_ODOM
#include "Other/OdomSystem.c"
#endif


#ifdef _7842F_USE_HYBRID_AUTO
#include "AutoHybridSystem/AutoHybridInit.c"
#include "AutoHybridSystem/AutoHybridFunctions.c"
#include "AutoHybridSystem/AutoHybridTask.c"
#endif




#endif
