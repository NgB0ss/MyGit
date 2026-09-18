/* FILE:        mygit_init.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 13.09.2026
 * PURPOSE:     Git project
 *              Mygit init function 
 */

#include "executor.h"
#include "regs/registrator.h"
#include "regs/function_pool.h"


void Init( std::string Path )
{

}


REGISTRATION_FUNCTION("init", Init, std::vector<ArgumentType>{ArgumentType::String})
/* END OF 'mygit_init.cpp' FILE */