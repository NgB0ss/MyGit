/* FILE:        authorization.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 29.10.2026
 * PURPOSE:     Git project.
 *              Authorization subsystem - main executor file.
 */

#include "authorization.h"

/* Function to check is user logined before in this session or no
 * ARGUMENTS: None.
 * RETURNS:
 *   (bool) Logined before or not.
 */
bool core::authorization::IsLogined( void )
{
} /* End of 'core::authorization::IsLogined' function */
    
/* Function to login already exist user 
 * ARGUMENTS: 
 *   - Command that parser return:
 *       ParseredCommand Cmd;
 * RETURNS: 
 *   (bool) Is login Ok or not.
 */
bool core::authorization::Login( ParsedCommand Cmd )
{
} /* End of 'core::authorization::Login' function */

/* Function to logout from this session 
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void core::authorization::Logout( void )
{
} /* End of 'core::authorization::Logout' function */

/* Function to create new user on this PC
 * ARGUMENTS:
 *   - Command that parser return:
 *       ParsedCommand Cmd;
 * RETURNS: None.
 */
void core::authorization::CreateUser( ParsedCommand Cmd )
{
} /* End of 'core::authorization::CreateUser' function */

/* END OF 'authorization.cpp' FILE */