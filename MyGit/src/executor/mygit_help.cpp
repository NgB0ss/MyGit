/* FILE:        mygit_help.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 18.10.2026
 * PURPOSE:     Git project.
 *              Mygit help function.
 */

#include "executor.h"
#include "regs/registrator.h"
#include "regs/function_pool.h"

/* Function output help
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void Help( void )
{
  std::cout << "MyGit - Version Control System\n\n";

  std::cout << "Usage:\n";
  std::cout << "  mygit init                       Initialize a new repository\n";
  std::cout << "  mygit commit -m \"...\"            Save the current changes as a commit\n";
  std::cout << "  mygit branch_create \"BranchName\" Create a new branch\n";
  std::cout << "  mygit branch_choose \"BranchName\" Switch to another branch\n";
  std::cout << "  mygit add .                      Stage all changes in the repository\n";
  std::cout << "  mygit add \"NameFile\"             Stage a specific file\n";
  std::cout << "  mygit reset uncommited           Discard staged changes\n";
  std::cout << "  mygit get \"HashCommit\"           Restore the repository to a specific commit\n";
  std::cout << "  mygit branches                   List all branches\n";
} /* End of 'Help' function */

/*** ADAPTER TO FUNCTION ***/

/* Adapter to choose branch function 
 * ARGUMENTS:
 *   - Vector of arguments to function:
 *       - std::vector<ArgumentValue> Args;
 * RETURNS: None.
 */
static void Adapter( std::vector<ArgumentValue> Args )
{
  Help();
} /* End of 'Adapter' function */

REGISTRATION_FUNCTION("help", Help, (std::vector<argument> {}), Adapter)

/* END OF 'mygit_help.cpp' FILE */
