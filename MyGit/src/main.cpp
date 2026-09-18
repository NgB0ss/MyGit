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
int main( /* int argc, char* argv[] */ )
{
	int argc = 3;
  char **argv = new char*[argc];

  // argv[0] Ч »м€ программы
  argv[0] = new char[std::strlen("my_program.exe") + 1];
  std::strcpy(argv[0], "my_program.exe");

  // argv[1] Ч ѕуть к диску
  argv[1] = new char[std::strlen("C:\\") + 1];
  std::strcpy(argv[1], "C:\\");

  // argv[2] Ч  оманда init
  argv[2] = new char[std::strlen("init") + 1];
  std::strcpy(argv[2], "init");

  core::mygit MyGit(argc, argv);

	// Run mygit
	MyGit.RunSession();

  delete argv[2];
  delete argv[1];
  delete argv[0];
  delete argv;

	return 0;
}	/* End of 'main' function */

/* END OF 'main.cpp' FILE */