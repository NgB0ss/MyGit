/* FILE:        def.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 16.09.2026
 * PURPOSE:     Git project
 *              Default header file
 */

#ifndef __def_h_
#define __def_h_

/* Includes lib */
#include <map>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <iostream>
#include <vector>
#include <functional>
#include <variant>
#include <filesystem>
#include <fstream>
#include <utility>
#include <array>
#include <stdexcept>

/* Debug memory allocation support */
#ifdef _DEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
static struct __Dummy
{
  /* Structure constructor */
  __Dummy( void )
  {
    SetDbgMemHooks();
  } /* End of '__Dummy' constructor */
} __oops;
#endif /* _DEBUG */

#ifdef _DEBUG
#  ifdef _CRTDBG_MAP_ALLOC
#    define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#  endif /* _CRTDBG_MAP_ALLOC */
#endif /* _DEBUG */

#endif /* __def_h_ */

/* END OF 'def.h' FILE */