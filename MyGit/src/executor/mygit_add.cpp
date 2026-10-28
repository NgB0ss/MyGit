/* FILE:        mygit_add.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 28.10.2026
 * PURPOSE:     Git project
 *              Mygit add functions 
 */

#include "executor.h"
#include "regs/registrator.h"
#include "regs/function_pool.h"

/* Function to add files to index (queue) 
 * ARGUMENTS:
 *   - Argument of add:
 *       std::string ArgAdd;
 * RETURNS: None.
 */
void Add( std::string ArgAdd )
{
  if (ArgAdd == ".")  // Add all in this repo
  {
    core::resources::tree CurrTree(core::resources::TreeCtor::BySystem);
    core::resources::branch CurrBranch = core::resources::branch::GetCurrentBranch();
    
    CurrBranch.ApplyTree(CurrTree);
    CurrBranch.Save();
  }
  else if (ArgAdd.size() != 0)
  {
    std::cout << "Add by path of file is not ready, use add ." << std::endl;
  }
  else
    std::cout << "Choose operator to add -> see help" << std::endl;
} /* End of 'Add' function */

/*** ADAPTER TO FUNCTION ***/

/* Adapter to add function 
 * ARGUMENTS:
 *   - Vector of arguments to function:
 *       - std::vector<ArgumentValue> Args;
 * RETURNS: None.
 */
static void Adapter( std::vector<ArgumentValue> Args )
{
  auto ArgAdd = std::get<std::string>(Args[0]);

  Add(ArgAdd);
} /* End of 'Adapter' function */


REGISTRATION_FUNCTION("add", Add, (std::vector<argument> {{"ArgAdd", ArgumentType::String, true}}), Adapter)

/* END OF 'mtgit_add.cpp' FILE */