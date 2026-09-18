/* FILE:        executor.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 16.09.2026
 * PURPOSE:     Git project
 *              Executor header file.
 */

#ifndef __executor_h_
#define __executor_h_

#include "core/resources/resources.h"
#include <core/parser/parser_def.h>

// Namespace for executor core logic
namespace executor_core
{
  // Function to choose and execute the correct function from parsed data
  void ChooseFunc(core::ParsedCommand Cmd);
} /* end of 'executor_core' namespace */

#endif /* __executor_h_ */

/* END OF 'executor.h' FILE */