/* FILE:        mygit_init.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 13.09.2026
 * PURPOSE:     Git project
 *              Mygit init function 
 */

#include "executor.h"
#include "regs/registrator.h"
#include "regs/function_pool.h"


/* Init mygit function 
 * ARGUMENTS:
 * RETURNS: None.
 */
void Init( std::string Path )
{

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

  Init(Path);
} /* End of 'Adapter' function */


REGISTRATION_FUNCTION("init", Init, (std::vector<argument> {{"Path", ArgumentType::String, true}}), Adapter)
/* END OF 'mygit_init.cpp' FILE */