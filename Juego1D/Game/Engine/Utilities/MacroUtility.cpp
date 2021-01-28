#include "MacroUtility.h"
#include <stdio.h>
#include <string>
#include <stdarg.h>

void _dbgprint(const char* _sMode, const char* _sFilename, int _iLine, const char* _sLevel, const char* _sFormat, ...)
{
  // Comprobar que la cadena introducida no este vacia
  if (strcmp(_sFormat, "") == 0)
    return;

  // Extraer de la ruta especificada unicamente el nombre del fichero.
  unsigned int uSize = strlen(_sFilename) + 1;
  unsigned int uIndex = uSize - 1;
  while (uIndex >= 1 && _sFilename[uIndex - 1] != '\\')
    uIndex--;
  // Imprimir el string con el formato especificado
  printf("%s[%s:%d] %s: ", _sMode, _sFilename + uIndex, _iLine, _sLevel);

  va_list arglist;
  va_start(arglist, _sFormat);
  vprintf(_sFormat, arglist);
  va_end(arglist);
  printf(ANSI_COLOR_RESET "\n");
}
