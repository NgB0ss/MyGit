/* FILE:        executor.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 16.09.2026
 * PURPOSE:     Git project
 *              Executor executor file.
 */

#include "executor.h"
#include "regs/function_pool.h"

/* Function to correct choose function from parsered data
 * ARGUMENTS:
 *   - Parsered data:
 *       core::ParseredCommand Cmd;
 * RETURNS: None.
 */
void executor_core::ChooseFunc( core::ParsedCommand Cmd )
{
	command Command = FunctionPool.GetPool().find(Cmd.FuncName)->second; // Get command 
	std::vector<ArgumentValue> Args;														// Get value of arguments

	// Parsing string arguments to correct-type arguments
	for (int i = 0; i < Command.Arguments.size(); i++)
	{
		std::string CurrArgStr = Cmd.Arguments[i];
		argument CurrArg = Command.Arguments[i];

		if (CurrArg.type == ArgumentType::Integer)			   // Make coorect types from string - string
		{
			int RemakeArg = 0;

			try
			{
				RemakeArg = std::stoi(CurrArgStr);
			} 
			catch ( std::exception &exept )
			{
				throw(exept);
			}
			Args.push_back(RemakeArg);
		}
		else if (CurrArg.type == ArgumentType::Hash)       // Make correct type from string - hash
		{
			core::crypto::hash RemakeArg = core::crypto::hash::FromStrToHash(CurrArgStr);
			Args.push_back(RemakeArg);
		}
		else if (CurrArg.type == ArgumentType::String)       // We thing that that arguments is string
		{
			std::string RemakeArg = CurrArgStr;
			Args.push_back(RemakeArg);
		}
		else
			throw std::invalid_argument("Not correct type of argument :: Level -> ArgsToFuncArgs");
	}
	// Call adapter
	std::invoke(Command.Adapter, Args);
} /* End of 'ChooseFunc' function */

/* END OF 'executor.cpp' FILE */