/* FILE:        parser_def.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 15.09.2026
 * PURPOSE:     Git project
 *              Parser types file
 */

#ifndef __parser_def_h_
#define __parser_def_h_

#include "def.h"

namespace core
{
  // Struct - whar parser return when arsered all lexems
	struct ParsedCommand
	{
    std::string FuncName;               // Name of parsered function
		std::vector<std::string> Arguments; // Arguments what return parser (all in string type)
	}; /* End of 'ParsedCommand' struct */
} /* end of 'core' namespace */


#endif /* __parser_def_h_ */

/* END OF 'parser_def.h' FILE */