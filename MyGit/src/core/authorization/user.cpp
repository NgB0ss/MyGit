/* FILE:        user.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 30.10.2026
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
 *   - Hash password of user:
 *       const std::string &Pswrd;
 */
core::authorization::user::user( const std::string &Nick,
                                 const std::string &Mail, 
                                 const crypto::hash &Pswrd )
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
  int cnt = 1;

  for (int i = 0; i < 3; i++)
  {
    std::string CurrStr;

    cnt = 1;
    while (Bytes[cnt] != '|')
      CurrStr.push_back(Bytes[cnt++]);
    if (i == 0)
      Nickname = CurrStr;
    else if (i == 1)
      Gmail = CurrStr;
    else 
      Password = crypto::hash::FromStrToHash(CurrStr);
  }
} /* End of 'core::authorization::user::user' function */

/* Function to get data from user to save 
 * ARGUMENTS: None.
 * RETURNS:
 *   (std::vector<uint8_t>) Bytes.
 */
std::vector<uint8_t> core::authorization::user::ToData( void ) const
{
  /* User will be saved like:
   *    Nickname|Gmail|PasswordHash 
   *    Only in programm, in database save -> check filesystem 
   */
  std::vector<uint8_t> Bytes;

  Bytes.push_back('|');
  Bytes.insert(Bytes.begin() + 1, Nickname.begin(), Nickname.end());
  Bytes.push_back('|');
  Bytes.insert(Bytes.end(), Gmail.begin(), Gmail.end());
  Bytes.push_back('|');
  // Insert password hash
  std::array<uint8_t, BYTES_HASH> Hash = Password.bytes();

  Bytes.insert(Bytes.end(), Hash.begin(), Hash.end());
  Bytes.push_back('|');
  return Bytes;
} /* End of 'core::authorization::user::ToData' function */

/* Function save user to database
 * ARGUMENTS: None.
 * RETURNS: 
 *   (bool) Is save ok or not.
 */
bool core::authorization::user::Save( void ) const
{
  return filesystem::WriteUser(ToData());
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
  bool flag = true;
  
  try { filesystem::ReadUser(User.Nickname); }
  catch ( const std::runtime_error &Err) { flag = false; }
  return true;
} /* End of 'core::authorization::user::IsExisted' function */

/* END OF 'user.cpp' FILE */