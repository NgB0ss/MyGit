/* FILE:        mygit.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 16.09.2026
 * PURPOSE:     Git project.
 *              Coordinator module executor.
 */

#include "mygit.h"

/* Ctor of class
 * ARGUMENTS:
 *   - How many arguments from cmd:
 *       int argc;
 *   - Array of strings from cmd (arguments):
 *       char* argv[];
 */
core::mygit::mygit( int argc, char* argv[] ) : parser(argc, argv)
{
  Path = std::filesystem::current_path();
} /* End of 'mygit' function */

/* Function to make this session
 * ARGUMENTS: None
 * RETURNS: None.
 */
void core::mygit::RunSession( void )
{
	// Parser arguments and choose executor function

	executor_core::ChooseFunc(ParseLex());
} /* End of 'RunSession' function */

/* END OF 'mygit.cpp' FILE */