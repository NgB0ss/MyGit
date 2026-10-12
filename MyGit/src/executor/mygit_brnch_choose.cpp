/* FILE:        mygit_brnch_choose.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 11.10.2026
 * PURPOSE:     Git project
 *              Mygit brnch choose functions 
 */

#include "executor.h"
#include "regs/registrator.h"
#include "regs/function_pool.h"

void ChooseBranch( std::string NewBranchStr )
{
  if (!core::filesystem::IsBranchSavedBf(NewBranchStr))
  {
    std::cout << "Branch not created before -> cant be choose " << NewBranchStr << std::endl;
    return;
  }

  try
  {
    core::resources::branch NewBranch(NewBranchStr);
    core::resources::branch::SwapCurrentBranch(NewBranch);
  }
  catch ( std::runtime_error Err )
  {
    std::cout << Err.what() << std::endl;
  }
}

/*** ADAPTER TO FUNCTION ***/

/* Adapter to choose branch function 
 * ARGUMENTS:
 *   - Vector of arguments to function:
 *       - std::vector<ArgumentValue> Args;
 * RETURNS: None.
 */
static void Adapter( std::vector<ArgumentValue> Args )
{
  auto NewBranch = std::get<std::string>(Args[0]);

  ChooseBranch(NewBranch);
} /* End of 'Adapter' function */

REGISTRATION_FUNCTION("branch_choose", ChooseBranch, (std::vector<argument> {{"NewBranch", ArgumentType::String, true}}), Adapter)

/* END OF 'mtgit_brnch_choose.cpp' FILE */