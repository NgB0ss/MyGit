/* FILE:        user.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 29.10.2026
 * PURPOSE:     Git project.
 *              Resources header file - user.
 */

#ifndef __user_h_
#define __user_h_

// Main project namespace
namespace core
{
  // Authorization subsystem namespace
  namespace authorization
  {
    // User auth class
    class user
    {
    private:
      std::string Gmail;     // Gmail of user
      std::string Nickname;  // User nickname
      std::string Password;  // Password of user
    public:
    }; /* end of 'user' class */
  } /* End of 'resources' namespace */
} /* End of 'core' namespace */

#endif /* __user_h_ */