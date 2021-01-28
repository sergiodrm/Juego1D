#pragma once

#include <assert.h>

/**
* Sistema de logger basado en macros
*/
void _dbgprint(const char* _sMode, const char* _sFilename, int _iLine, const char* _sLevel, const char* _sFormat, ...);


#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#ifdef _DEBUG

#define PRINT_LOG(_sFormat, ...)      _dbgprint(ANSI_COLOR_RESET, __FILE__, __LINE__, "Log", _sFormat, __VA_ARGS__)
#define PRINT_WARNING(_sFormat, ...)  _dbgprint(ANSI_COLOR_YELLOW, __FILE__, __LINE__, "Warning", _sFormat, __VA_ARGS__)
#define PRINT_ERROR(_sFormat, ...)    _dbgprint(ANSI_COLOR_RED, __FILE__, __LINE__, "Error", _sFormat, __VA_ARGS__)
#else     
#define PRINT_LOG(_sFormat, ...)      
#define PRINT_WARNING(_sFormat, ...)  
#define PRINT_ERROR(_sFormat, ...)
#endif

/**
 * Macro para definir una clase base como Super.
 */
#define BASE_CLASS(_BASECLASSNAME) \
protected: \
  typedef _BASECLASSNAME Super 

/**
 *  Macros para comprobacion de afirmaciones.
 *  En caso de que la condicion no se cumpla, salta un breakpoint (debug).
 *  En caso de que la condicion no se cumpla, mostrara un error mediante assert (release).
 */
#ifdef _DEBUG

#define ensure_msg(_bTrueCondition, _sMsg)    \
  if (!(_bTrueCondition))                     \
  {                                           \
    PRINT_ERROR(_sMsg);                       \
    __debugbreak();                           \
  }                                           
#define ensure(_bTrueCondition)               \
  if (!(_bTrueCondition)) __debugbreak()

#else

#define ensure_msg(_bTrueCondition, _sMsg)  assert(_bTrueCondition)
#define ensure(_bTrueCondition)             assert(_bTrueCondition)

#endif