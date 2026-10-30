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
  std::string CurrUserNickname;
  
  // Throw -> Run session catch
  CurrUserNickname = filesystem::ReadCurrUserSession();
  if (CurrUserNickname.size() == 0)
    return false;
  return true;
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
  // Command like MyGit login
  // Check that parsed command that needed command
  if (Cmd.FuncName != "login")
    return false;

  // Try login
  std::string Nickname, Password;

  std::cout << "Nickname:" << std::endl;
  std::cin >> Nickname;
  if (Nickname.size() > MAX_AUTH)
    return false;
  std::cout << "Password:" << std::endl;
  utils::DisableEchoInput();
  std::cin >> Password;
  utils::EnableEchoInput();

  std::vector<uint8_t> BytesPswrd;

  BytesPswrd.insert(BytesPswrd.begin(), Password.begin(), Password.end());
  crypto::hash CurrentPassword(BytesPswrd);
  user User(filesystem::ReadUser(Nickname));

  if (User.HashPassword() != CurrentPassword)
    return false;

  filesystem::WriteCurrUserSession(Nickname);
  return true;
} /* End of 'core::authorization::Login' function */

/* Function to logout from this session 
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void core::authorization::Logout( void )
{
  // Command like MyGit logout
  //   - Clean current session -> write empty user nickname
  filesystem::WriteCurrUserSession(std::string());
} /* End of 'core::authorization::Logout' function */

/* Function to create new user on this PC
 * ARGUMENTS:
 *   - Command that parser return:
 *       ParsedCommand Cmd;
 * RETURNS: 
 *   (bool) Create OK or not.
 */
bool core::authorization::CreateUser( ParsedCommand Cmd )
{
  if (Cmd.FuncName != "create_user")
    return false;

  // Try login
  std::string Nickname, Gmail, Password;

  std::cout << "Nickname:" << std::endl;
  std::cin >> Nickname;
  if (Nickname.size() > MAX_AUTH)
    return false;
  std::cout << "Gmail" << std::endl;
  std::cin >> Gmail;
  std::cout << "Password:" << std::endl;
  utils::DisableEchoInput();
  std::cin >> Password;
  utils::EnableEchoInput();

  std::vector<uint8_t> BytesPswrd;

  BytesPswrd.insert(BytesPswrd.begin(), Password.begin(), Password.end());
  crypto::hash CurrentPassword(BytesPswrd);
  user User(Nickname, Gmail, CurrentPassword);

  return User.Save();
} /* End of 'core::authorization::CreateUser' function */

/* END OF 'authorization.cpp' FILE */