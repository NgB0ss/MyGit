/* FILE:        main.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 13.09.2026
 * PURPOSE:     Git project
 *              main file, start systems
 */

#include "core/mygit.h"

/* Main programm function - start all systems
 * ARGUMENTS:
 *   - Arguments count (>= 1)
 *       int argc;
 *   - Array of arguments from cmd
 *       char* argv[];
 * RETURNS: 
 *   (int) End code of programm.
 */
int main( int argc, char* argv[] )
{
	core::mygit MyGit(argc, argv);

	return 0;
}	/* End of 'main' function */

/* END OF 'main.cpp' FILE */