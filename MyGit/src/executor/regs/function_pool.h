/* FILE:        function_pool.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 18.09.2026
 * PURPOSE:     Git project.
 *              Function pool container.
 */

#ifndef __function_pool_h_
#define __function_pool_h_

#include <def.h>
#include "core/resources/resources.h"

// Arguments type in mygit functions
enum class ArgumentType
{
	String,   // String type
	Hash,			// Hash type
	Integer		// Integer type
}; /* End of 'ArgumentType' class */

// Arguments value in ,ygit functions
using ArgumentValue = std::variant<
		std::string,        // String value
		core::crypto::hash,	// Hash value
		int
>;

struct argument
{
		std::string name;
		ArgumentType type;
		bool required;
}; /* End of 'Argument' struct */

// 1 Command struct (pool type)
struct command
{
	std::string Name;
	std::vector<argument> Arguments;

	std::function<void( std::vector<ArgumentValue> )> Adapter;
}; /* End of 'command' struct */

// Class to save commands
class function_pool
{
private:
	std::map<std::string, command> Functions;  // Functions pool
public:
	/* Funtion to get pool
		* ARGUEMENTS: None
		* RETURNS:
		*   (auto) Pool of functions.
		*/
	auto GetPool( void )
	{
		return Functions;
	}	/* End of 'GetPool' function */
}; /* End of 'function_pool' class */

inline function_pool FunctionPool; // Static container to save all functions

#endif /* __function_pool_h_ */

/* END OF 'function_pool.h' FILE */