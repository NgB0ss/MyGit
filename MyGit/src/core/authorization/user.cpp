/* FILE:        user.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 29.10.2026
 * PURPOSE:     Git project.
 *              Resources executor file - user.
 */

#include "user.h"

/* Ctor of user class by all args
 * ARGUMENTS: 
 *   - Nickname of user:
 *       const std::string &Nickname;
 *   - Gmail of user:
 *       const std::string &Mail;
 *   - Password of user:
 *       const std::string &Pswrd;
 */
core::authorization::user::user( const std::string &Nick,
      const std::string &Mail, 
      const std::string &Pswrd )
{
  Nickname = Nick;
  Gmail = Mail;
  Password = Pswrd;
} /* End of 'core::authorization::user::user' function */

/* Ctor of user by bytes from database
 * ARGUMENTS:
 *   - Bytes:
 *       const std::vector<uint8_t> &Bytes;
 */
core::authorization::user::user( const std::vector<uint8_t> &Bytes )
{
  // Decoder of bytes
} /* End of 'core::authorization::user::user' function */

/* Function to get data from user to save 
 * ARGUMENTS: None.
 * RETURNS:
 *   (std::vector<uint8_t>) Bytes.
 */
std::vector<uint8_t> core::authorization::user::ToData( void )
{
  /* User will be saved like:
   *    Nickname|Gmail|Password 
   *    Only in programm, in database save -> check filesystem 
   */
  std::vector<uint8_t> Bytes;

  Bytes.insert(Bytes.begin(), Nickname.begin(), Nickname.end());
  Bytes.push_back('|');
  Bytes.insert(Bytes.end(), Gmail.begin(), Gmail.end());
  Bytes.push_back('|');
  Bytes.insert(Bytes.end(), Password.begin(), Password.end());
  return Bytes;
} /* End of 'core::authorization::user::ToData' function */

/* Function save user to database
 * ARGUMENTS: None.
 * RETURNS: 
 *   (bool) Is save ok or not.
 */
bool core::authorization::user::Save( void ) const
{
  return true;
} /* End of 'core::authorization::user::Save' function */

/* Static function to check is user exist in database
 * ARGUMENTS:
 *   - User to check:
 *       const user &User;
 * RETURNS: 
 *   (bool) Is exist or not.
 */
bool core::authorization::user::IsExisted( const user &User )
{
  return true;
} /* End of 'core::authorization::user::IsExisted' function */

/* END OF 'user.cpp' FILE */