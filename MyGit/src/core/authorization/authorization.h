/* FILE:        authorization.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 29.10.2026
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
    /* Function to check is user logined before in this session or no
     * ARGUMENTS: None.
     * RETURNS:
     *   (bool) Logined before or not.
     */
    bool IsLogined( void );
    
    /* Function to login already exist user 
     * ARGUMENTS: 
     *   - Command that parser return:
     *       ParseredCommand Cmd;
     * RETURNS: 
     *   (bool) Is login Ok or not.
     */
    bool Login( ParsedCommand Cmd );

    /* Function to logout from this session 
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    void Logout( void );

    /* Function to create new user on this PC
     * ARGUMENTS:
     *   - Command that parser return:
     *       ParsedCommand Cmd;
     * RETURNS: None.
     */
    void CreateUser( ParsedCommand Cmd );
  } /* End of 'resources' namespace */
} /* End of 'core' namespace */

#endif /* __authorization_h_ */