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
 * ARGUMENTS: None.
 * RETURNS: 
 *   (bool) Is login Ok or not.
 */
bool core::authorization::Login( void )
{
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

  return filesystem::WriteCurrUserSession(Nickname);
} /* End of 'core::authorization::Login' function */

/* Function to logout from this session 
 * ARGUMENTS: 
 *   - Parsered command from parser:
 *       const ParsedCommand &Cmd;
 * RETURNS: 
 *   (bool) Ok logout or not.
 */
bool core::authorization::Logout( const ParsedCommand &Cmd )
{
  // Command like MyGit logout
  //   - Clean current session -> write empty user nickname
  if (Cmd.FuncName == "logout")
    return filesystem::WriteCurrUserSession(std::string());
  return false;
} /* End of 'core::authorization::Logout' function */

/* Function to create new user on this PC
 * ARGUMENTS: None.
 * RETURNS: 
 *   (bool) Create OK or not.
 */
bool core::authorization::CreateUser( void )
{
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


/* Function to authorization in mygit
 * ARGUMENTS:
 *   - Parsed command from parser:
 *       const ParsedCommand &Cmd;
 * RETURNS:
 *   (StateAuthorizationFunc) Authorization state correct.
 */
core::authorization::StateAuthorizationFunc core::authorization::Authorization( const ParsedCommand &Cmd )
{
  // Check command to authorization command
  // If not logout -> logined or not and login or create if not and true if logined
  if (Cmd.FuncName == "login")
    return Login() ? StateAuthorizationFunc::FuncCorrect : StateAuthorizationFunc::FuncError;
  else if (Cmd.FuncName == "create_user")
    return CreateUser() ? StateAuthorizationFunc::FuncCorrect : StateAuthorizationFunc::FuncError;
  else 
    return StateAuthorizationFunc::FuncIsNotAuthorization;
} /* End of 'core::authorization::Authorization' functoin */

/* END OF 'authorization.cpp' FILE */