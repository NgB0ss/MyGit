/* FILE:        mygit.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 15.09.2026
 * PURPOSE:     Git project
 *              Core coordinator module
 *              Class of coordinator
 */

#ifndef __mygit_h_
#define __mygit_h_

#include "executor/executor.h"
#include "parser/parser.h"

namespace core
{
  // Main coordinator class
  class mygit : public parser
  {
  private:
    std::filesystem::path Path; // Path where is .mygit or where is there will be
  public:
    /* Ctor of class
     * ARGUMENTS:
     *   - How many arguments from cmd:
     *       int argc;
     *   - Array of strings from cmd (arguments):
     *       char* argv[];
     */
    mygit( int argc, char* argv[] );

    /* Function to make this session
     * ARGUMENTS: None
     * RETURNS: None.
     */
    void RunSession( void );
  }; /* End of 'mygit' class */
} /* end of 'core' namespace */

#endif /* __mygit_h_ */

/* END OF 'mygit.h' FILE */