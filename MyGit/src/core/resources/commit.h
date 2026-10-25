/* FILE:        commit.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 21.10.2026
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
      core::crypto::hash Parent{}, Tree{};                                        // Parent commit and tree filesystem state
      std::string Author{}, Message{};                                            // Author of commit message
      std::chrono::time_point<std::chrono::system_clock, std::chrono::minutes> Time{};       // Time that commit was created

    public:
      /* Default commit ctor
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      commit( void ) = default;

      /* Ctor commit by byte data 
       * ARGUMENTS:
       *   - Data that readed from commit:
       *       const std::vector<uint8_t> &Data;
       */
      commit( const std::vector<uint8_t> &Data );

      /* Ctor by all data of resource
       * ARGUMENTS:
       *   - Hash of parrent commit:
       *       const core::crypto::hash &Parent;
       *   - Hash of tree filesystem state of commit:
       *       const core::crypto::hash &Tree;
       *   - Author of commit:
       *       const std::string &Author;
       *   - Message of commit:
       *       const std::string &Msg;
       */
      commit( const core::crypto::hash &Parent,
              const core::crypto::hash &Tree,
              const std::string &Author,
              const std::string &Msg);

      /* Function to apply commit version 
       * ARGUMENTS: 
       *   - Path where vesrion will be builded:
       *       std::string Path;
       * RETURNS: None.
       */
      void ApplyVersion( std::string Path );

      /* Function to make version by commit and path where it need be
       * ARGUMENTS:
       *   - Path where version need be:
       *       std::string Path;
       * RETURNS: None.
      */
      void MakeVersionByCommit( std::string Path );

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