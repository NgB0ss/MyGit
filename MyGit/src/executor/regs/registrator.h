/* FILE:        registrator.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 18.09.2026
 * PURPOSE:     Git project
 *              Self-registrator of functions
 */

#ifndef __registrator_h_
#define __registrator_h_

#include "function_pool.h"

// Self-registrator class
class registrator
{
public:
  /* Ctor of class
    * ARGUMENTS: 
    *   - Name of commnd:
    *       std::string NameFunc;
    *   - Function that will be registration:
    *       type *Func;
    *    - Vector of argument types:
    *       std::vector<ArgumentType> ArgTypes;
    */
  template <typename type, typename typeA>
  registrator( std::string NameFunc, type *Func, std::vector<argument> Arguments, typeA *Adapter )
  {
    command CurrCmd;

    CurrCmd.Name = NameFunc;
    CurrCmd.Arguments = Arguments;
    CurrCmd.Adapter = Adapter;

    FunctionPool.GetPool().insert(std::pair(NameFunc, CurrCmd));
  } /* End of 'registrator' function */

}; /* End of 'registrator' class */

// Main macross to self-register function
#define REGISTRATION_FUNCTION(Name, F, Arg, Adapter) \
          static registrator _(Name, F, Arg, Adapter);

#endif /* __registrator_h_ */

/* END OF 'registrator.h' FILE */