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
		* 	 - Vector of argument types:
		*       std::vector<ArgumentType> ArgTypes;
		*/
	template <typename type>
	registrator( std::string NameFunc, type *Func, std::vector<ArgumentType> ArgTypes )
	{
		command CurrCmd;

		CurrCmd.Name = NameFunc;
		CurrCmd.Arguments = ArgTypes;
		CurrCmd.Adapter = []( vector<ArgumentValue> Args )
			{
				Func(Args); // Call function to make git session
			};

		FunctionPool.GetPool().insert(NameFunc, CurrCmd);
	} /* End of 'registrator' function */

}; /* End of 'registrator' class */

// Main macross to self-register function
#define REGISTRATION_FUNCTION(Name, F, Arg) \
          static registrator _(Name, F, Arg);

#endif /* __registrator_h_ */

/* END OF 'registrator.h' FILE */