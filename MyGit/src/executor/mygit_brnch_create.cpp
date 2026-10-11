/* FILE:        mygit_brnch_create.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 10.10.2026
 * PURPOSE:     Git project
 *              Mygit brnch create functions 
 */

#include "executor.h"
#include "regs/registrator.h"
#include "regs/function_pool.h"

void CreateBranch( std::string NewBranchStr )
{
  try
  {
    core::resources::branch NewBranch(NewBranchStr);
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

  CreateBranch(NewBranch);
} /* End of 'Adapter' function */

REGISTRATION_FUNCTION("branch_create", CreateBranch, (std::vector<argument> {{"NewBranch", ArgumentType::String, true}}), Adapter)

/* END OF 'mtgit_brnch_create.cpp' FILE */
