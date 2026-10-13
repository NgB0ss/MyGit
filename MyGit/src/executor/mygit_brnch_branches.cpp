/* FILE:        mygit_brnch_branches.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 13.10.2026
 * PURPOSE:     Git project
 *              Mygit branches view function 
 */

#include "executor.h"
#include "regs/registrator.h"
#include "regs/function_pool.h"

/* Init mygit function 
 * ARGUMENTS:
 *   - Path where function was called:
 *       std::string Path;
 * RETURNS: None.
 */
void BranchesView( std::string Path )
{
  for (const auto &entry: std::filesystem::directory_iterator(core::filesystem::BRANCH_PATH))
    std::cout << entry.path().filename() << std::endl;
} /* End of 'Init' function */

/*** ADAPTER TO FUNCTION ***/

/* Adapter to init function 
 * ARGUMENTS:
 *   - Vector of arguments to function:
 *       - std::vector<ArgumentValue> Args;
 * RETURNS: None.
 */
static void Adapter( std::vector<ArgumentValue> Args )
{
  auto Path = std::get<std::string>(Args[0]);

  BranchesView(Path);
} /* End of 'Adapter' function */


REGISTRATION_FUNCTION("branches", BranchesView, (std::vector<argument> {{"Path", ArgumentType::String, true}}), Adapter)


/* END OF 'mygit_brnch_branches.cpp' FILE */