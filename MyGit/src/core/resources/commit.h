/* FILE:        commit.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 29.09.2026
 * PURPOSE:     Git project.
 *              Resources header file - commit
 */

#ifndef __commit_h_
#define __commit_h_

#include "tree.h"

#define MAX_MSG 150  // Max symbols in 1 message to commit 
#define MAX_AUTH 150 // Max author info

// Main core mygit namespace
namespace core
{
  // Main resource namespace
  namespace resources
  {
    // Commit resource class
    class commit
    {
    private:
      core::crypto::hash Parent, Tree;                                                     // Parent commit and tree filesystem state
      std::string Author, Message;                                                         // Author of commit message
      std::chrono::time_point<std::chrono::system_clock, std::chrono::minutes> Time;       // Time that commit was created

    public:
      /* Ctor commit by byte data 
       * ARGUMENTS:
       *   - Data that readed from commit:
       *       std::vector<uint8_t> Data;
       */
      commit( std::vector<uint8_t> Data );

      /* Ctor by all data of resource
       * ARGUMENTS:
       *   - Hash of parrent commit:
       *       core::crypto::hash Parent;
       *   - Hash of tree filesystem state of commit:
       *       core::crypto::hash Tree;
       *   - Author of commit:
       *       std::string Author;
       *   - Message of commit:
       *       std::string Msg;
       */
      commit( core::crypto::hash Parent,
              core::crypto::hash Tree,
              std::string Author,
              std::string Msg );

      /* Function to apply commit version 
       * ARGUMENTS:
       *   - Hash commit that need by apply:
       *       core::crypto::hash  HashCommit;
       * RETURNS: None.
       */
      void Apply( core::crypto::hash HashCommit );

      /* Function to make version by commit and path where it need be
       * ARGUMENTS:
       *   - Path where we need version:
       *       std::string Path;
       *   - Hash of commit that need be applied:
       *       core::crypto::hash HashCommit;
       * RETURNS: None.
      */
      void MakeVersionByCommit( std::string Path, core::crypto::hash HashCommit );

      /* Function to get data from commit 
       * ARGUMENTS: None.
       * RETURNS:
       *   (std::vector<uint8_t>) Data of commit in bytes.
       */
      std::vector<uint8_t> DataFromCommit( void );
    }; /* End of 'commit' class */
  }  /* end of 'resources' namespace */
} /* end of 'core' namespace */


#endif /* __commit_h_ */

/* END OF 'commit.h' FILE */