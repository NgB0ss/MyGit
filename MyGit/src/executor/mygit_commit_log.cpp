/* FILE:        mygit_commit_log.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 24.10.2026
 * PURPOSE:     Git project
 *              Mygit commit log function
 */

#include "executor.h"
#include "regs/registrator.h"
#include "regs/function_pool.h"

/* Function output help
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void CommitLog( void )
{
  std::filesystem::path Path = std::filesystem::current_path();
  
  Path = Path / core::filesystem::BRANCH_PATH;
  core::resources::branch CurrBrnch = core::resources::branch::GetCurrentBranch();
} /* End of 'CommitLog' function */

/*** ADAPTER TO FUNCTION ***/

/* Adapter to choose branch function 
 * ARGUMENTS:
 *   - Vector of arguments to function:
 *       - std::vector<ArgumentValue> Args;
 * RETURNS: None.
 */
static void Adapter( std::vector<ArgumentValue> Args )
{
  CommitLog();
} /* End of 'Adapter' function */

// REGISTRATION_FUNCTION("commit_log", CommitLog, (std::vector<argument> {}), Adapter)


/* END OF 'mygit_commit_log.cpp' FILE */