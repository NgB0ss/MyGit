/* FILE:        authorization.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 30.10.2026
 * PURPOSE:     Git project.
 *              Authorization subsystem - main header file.
 */

#ifndef __authorization_h_
#define __authorization_h_

#include "user.h"
#include "core/parser/parser_def.h"

// Main project namespace
namespace core
{
  // Authorization subsystem namespace
  namespace authorization
  {
    // Enum class to check state corre of authorization
    enum class StateAuthorizationFunc
    {
      FuncCorrect,            // Authorization is correct
      FuncError,              // Authorization error
      FuncIsNotAuthorization  // Parsed function is not authorization 
    }; /* End of 'StateAuthorizationFunc' enum class */
    /* Function to check is user logined before in this session or no
     * ARGUMENTS: None.
     * RETURNS:
     *   (bool) Logined before or not.
     */
    bool IsLogined( void );
    
    /* Function to login already exist user 
     * ARGUMENTS: None.
     * RETURNS: 
     *   (bool) Is login Ok or not.
     */
    bool Login( void );

    /* Function to logout from this session 
     * ARGUMENTS: 
     *   - Parsered command from parser:
     *       const ParsedCommand &Cmd;
     * RETURNS: 
     *   (bool) Ok logout or not.
     */
    bool Logout( const ParsedCommand &Cmd );

    /* Function to create new user on this PC
     * ARGUMENTS: None.
     * RETURNS: 
     *   (bool) Create OK or not.
     */
    bool CreateUser( void );

    /* Function to authorization in mygit
     * ARGUMENTS:
     *   - Parsed command from parser:
     *       const ParsedCommand &Cmd;
     * RETURNS:
     *   (StateAuthorizationFunc) Is authorization success or not.
     */
    StateAuthorizationFunc Authorization( const ParsedCommand &Cmd );
  } /* End of 'resources' namespace */
} /* End of 'core' namespace */

#endif /* __authorization_h_ */