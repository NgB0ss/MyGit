/* FILE:        parser.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 15.09.2026
 * PURPOSE:     Git project
 *              Parser consalidator file
 */

#ifndef __parser_h_
#define __parser_h_

#include "def.h"

namespace core
{
	// Struct - whar parser return when arsered all lexems
	struct ParsedCommand
	{
    std::string FuncName;               // Name of parsered function
		std::vector<std::string> Arguments; // Arguments what return parser (all in string type)
	}; /* End of 'ParsedCommand' struct */

	// Parser main class
	class parser
	{
	private:
		int argc;     // Count of arguments from cmd
		char** argv; // Arguments from cmd
	public:
		/* Ctor of parser class
		 * ARGUMENTS: 
		 *   - Count of arguments from cmd:
		 *       int argc;
		 *   - Arguments from cmd:
		 *       char* argv[];
		 */
    parser( int argc, char* argv[] ) : argc(argc), argv(argv)
		{
		} /* End of 'parser' fuction */

		ParsedCommand ParseLex( void )
		{
			ParsedCommand Cmd;

			for (int i = 0; i < argc; i++)
			{
				if (i == 2)
					Cmd.FuncName = std::string(argv[i]);
				if (i >= 2)
					Cmd.Arguments.push_back(std::string(argv[i]));
			}

			return Cmd;
		}	/* End of 'ParseLex' function */
	}; /* End of 'parser' class */
} /* end of 'core' namespace */

#endif /* __parser_h_ */

/* END OF 'parser.h' FILE */