/* FILE:        executor.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 16.09.2026
 * PURPOSE:     Git project
 *              Executor consalidator file
 */

#ifndef __executor_h_
#define __executor_h_

#include "core/parser/parser_def.h"
#include "core/resources/resources.h"

// Main executor namespace
namespace executor_core
{
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

			std::function<void(std::vector<ArgumentType>)> Adapter;
	}; /* End of 'command' struct */

	class executor
	{
	private:
		std::map<std::string, command> function_pool;  // Functions pool
	public:
		/* Function to correct choose function from parsered data
		 * ARGUMENTS:
		 *   - Parsered data:
		 *       core::ParseredCommand Cmd;
		 * RETURNS: None.
		 */
		void ChooseFunc( core::ParsedCommand Cmd )
		{
			command Command = function_pool.find(Cmd.FuncName)->second; // Get command 
			std::vector<ArgumentValue> Args;														// Get value of arguments

			// Parsing string arguments to correct-type arguments
			for (int i = 0; i < Command.Arguments.size(); i++)
			{
				std::string CurrArgStr = Cmd.Arguments[i];
				argument CurrArg = Command.Arguments[i];

				if (CurrArg.type == ArgumentType::Integer)			   // Make coorect types from string - string
				{
				}
				else if (CurrArg.type == ArgumentType::Hash)       // Make correct type from string - hash
					core::crypto::hash RemakeArg = core::crypto::hash::FromStrToHash(CurrArgStr);
				else                                               // We thing that that arguments is string
					std::string RemakeArg = CurrArgStr;



				// Args.push_back();
			}
			// Call adapter


		} /* End of 'ChooseFunc' function */


	}; /* End of 'executor' class */
}	/* end of 'executor' namespace */

#endif /* __executor_h_ */