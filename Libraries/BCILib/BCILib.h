#ifndef BCI_H_INCLUDED
#define BCI_H_INCLUDED

#if defined(BCI_USE_BLOCK) || defined(BCI_USE_MATRIX) || defined(BCI_USE_ARRAYLIST)
  #ifndef BCI_USE_HEAP
    #define BCI_USE_HEAP
  #endif
#endif

#if defined(BCI_USE_MATRIX) || defined(BCI_USE_ARRAYLIST)
  #ifndef BCI_USE_BLOCK
    #define BCI_USE_BLOCK
  #endif
#endif

#if defined(BCI_USE_BANGBANG) || defined(BCI_USE_VEL_PID) || defined(BCI_USE_VEL_TBH)
  #ifndef BCI_USE_DEMA_FILTER
    #define BCI_USE_DEMA_FILTER
  #endif
#endif

#if defined(BCI_USE_LCDCONTROL)
  #ifndef BCI_USE_TIMER
    #define BCI_USE_TIMER
  #endif
#endif

#include "Math\math.h"
#include "Math\statePack.c"

#ifdef BCI_USE_JOYSTICK
#include "Util\joystickDefinitions.h"
#endif

#include "Util\semaphore.h"
#include "Util\util.h"

#ifdef BCI_USE_UART
  #include "Util\uart.c"
#endif

#ifdef BCI_USE_TIMER
  #include "Util\timer.c"
#endif

#ifdef BCI_USE_HEAP
  #include "Util\error.c"
#endif

#ifdef BCI_USE_EMA_FILTER
  #include "Filter\emaFilter.c"
#endif

#ifdef BCI_USE_DEMA_FILTER
#include "Filter\demaFilter.c"
#endif

#ifdef BCI_USE_FUA_FILTER
  #include "Filter\fuaFilter.c"
#endif

#ifdef BCI_USE_TUA_FILTER
  #include "Filter\tuaFilter.c"
#endif

#ifdef BCI_USE_BIQUAD_FILTER
  #include "Filter\biquadFilter.c"
#endif

#ifdef BCI_USE_POS_PID
  #include "Control\positionPID.c"
#endif

#ifdef BCI_USE_VEL_PID
  #include "Control\velocityPID.c"
#endif

#ifdef BCI_USE_VEL_TBH
  #include "Control\velocityTBH.c"
#endif

#ifdef BCI_USE_BANGBANG
  #include "Control\bangBang.c"
#endif

#ifdef BCI_USE_MOTORCONTROL
  #include "Control\motorControl.c"
#endif

#ifdef BCI_USE_LCDCONTROL
  #include "LCD\lcdControl.c"
#endif

#ifdef BCI_USE_HEAP
  #include "Heap\heap.c"
#endif

#ifdef BCI_USE_BLOCK
  #include "Heap\block.c"
#endif

#ifdef BCI_USE_ARRAYLIST
  #include "Heap\arrayList.c"
#endif

#ifdef BCI_USE_MATRIX
  #include "Math\matrix.c"
#endif

#include "Etc\suppressWarning.c"

#endif //BCI_H_INCLUDED
