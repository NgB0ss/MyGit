/* FILE:        user.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 29.10.2026
 * PURPOSE:     Git project.
 *              Resources header file - user.
 */

#ifndef __user_h_
#define __user_h_

#include "core/resources/filesystem/filesystem.h"

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
      std::string Nickname {};  // User nickname
      std::string Gmail {};     // Gmail of user
      crypto::hash Password {};  // Password of user

      /* Function to get data from user to save 
       * ARGUMENTS: None.
       * RETURNS:
       *   (std::vector<uint8_t>) Bytes.
       */
      std::vector<uint8_t> ToData( void ) const;
    public:
      /* Ctor of user class by all args
       * ARGUMENTS: 
       *   - Nickname of user:
       *       const std::string &Nickname;
       *   - Gmail of user:
       *       const std::string &Mail;
       *   - Hash password of user:
       *       const crypto::hash &Pswrd;
       */
      user( const std::string &Nick,
            const std::string &Mail, 
            const crypto::hash &Pswrd );

      /* Ctor of user by bytes from database
       * ARGUMENTS:
       *   - Bytes:
       *       const std::vector<uint8_t> &Bytes;
       */
      user( const std::vector<uint8_t> &Bytes );

      /* Function save user to database
       * ARGUMENTS: None.
       * RETURNS: 
       *   (bool) Is save ok or not.
       */
      bool Save( void ) const;

      /* Static function to check is user exist in database
       * ARGUMENTS:
       *   - User to check:
       *       const user &User;
       * RETURNS: 
       *   (bool) Is exist or not.
       */
      static bool IsExisted( const user &User );
    }; /* end of 'user' class */
  } /* End of 'resources' namespace */
} /* End of 'core' namespace */

#endif /* __user_h_ */