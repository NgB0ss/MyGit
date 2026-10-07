/* FILE:        parser.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 07.10.2026
 * PURPOSE:     Git project
 *              Parser consalidator file
 */

#ifndef __parser_h_
#define __parser_h_

#include "parser_def.h"

namespace core
{
  // Parser main class
  class parser
  {
  private:
    int argc;     // Count of arguments from cmd
    char** argv; // Arguments from cmd
    std::filesystem::path Current_Path; // Path here mygit was called

  public:
    /* Ctor of parser class
     * ARGUMENTS: 
     *   - Count of arguments from cmd:
     *       int argc;
     *   - Arguments from cmd:
     *       char* argv[];
     *   - Current path:
     *       std::filesystem::path Path;
     */
    parser( int argc, char* argv[], std::filesystem::path Path ) : argc(argc), argv(argv), Current_Path(Path)
    {
    } /* End of 'parser' fuction */

    ParsedCommand ParseLex( void )
    {
      std::string Path;
      ParsedCommand Cmd;

      for (int i = 0; i < argc; i++)
      {
        if (i == 0)
          Path = argv[i];
        if (i == 1)
          Cmd.FuncName = std::string(argv[i]);
        if (i >= 2)
          Cmd.Arguments.push_back(std::string(argv[i]));
      }

      // Functions that need path in arguments
      if (Cmd.FuncName == "init")
        Cmd.Arguments.push_back(Current_Path.string());

      return Cmd;
    }  /* End of 'ParseLex' function */
  }; /* End of 'parser' class */
} /* end of 'core' namespace */

#endif /* __parser_h_ */

/* END OF 'parser.h' FILE */