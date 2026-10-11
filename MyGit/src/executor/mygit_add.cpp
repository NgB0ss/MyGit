/* FILE:        mygit_add.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 10.10.2026
 * PURPOSE:     Git project
 *              Mygit add functions 
 */

#include "executor.h"
#include "regs/registrator.h"
#include "regs/function_pool.h"

void Add( std::string ArgAdd )
{

}

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