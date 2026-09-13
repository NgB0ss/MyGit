/* FILE:        parser.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 13.09.2026
 * PURPOSE:     Git project
 *              Parser consalidator file
 */

#ifndef __parser_h_
#define __parser_h_

namespace core
{
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

		void ParseLex( void )
		{

		}	/* End of 'ParseLex' function */
	}; /* End of 'parser' class */
} /* end of 'core' namespace */

#endif /* __parser_h_ */

/* END OF 'parser.h' FILE */