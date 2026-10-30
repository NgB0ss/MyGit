/* FILE:        mygit.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 30.10.2026
 * PURPOSE:     Git project.
 *              Coordinator module executor.
 */

#include "mygit.h"

/* Ctor of class
 * ARGUMENTS:
 *   - How many arguments from cmd:
 *       int argc;
 *   - Array of strings from cmd (arguments):
 *       char* argv[];
 */
core::mygit::mygit( int argc, char* argv[] ) : parser(argc, argv, std::filesystem::current_path())
{
  Path = std::filesystem::current_path();
} /* End of 'mygit' function */

/* Function to make this session
 * ARGUMENTS: None
 * RETURNS: None.
 */
void core::mygit::RunSession( void )
{
  // Parser arguments and choose executor function, before it -> login
  try
  {
    ParsedCommand Cmd = ParseLex();
    
    if (!authorization::IsLogined())
    {
      if (!authorization::Login(Cmd))
        if (!authorization::CreateUser(Cmd))
          throw std::runtime_error("Not logined session");
    }
    else
      executor_core::ChooseFunc(Cmd);
  }
  catch ( std::runtime_error Err )
  {
    std::cout << Err.what();
  }
} /* End of 'RunSession' function */

/* END OF 'mygit.cpp' FILE */