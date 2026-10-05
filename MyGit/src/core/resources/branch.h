/* FILE:        branch.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 06.10.2026
 * PURPOSE:     Git project.
 *              Resources header file - branch
 */

#ifndef __branch_h_
#define __branch_h_

#include "commit.h"

// Main core mygit namespace
namespace core
{
  // Main resource namespace
  namespace resources
  {
    // Branch resource namespace
    class branch
    {
    private:
      inline static bool IsCurrentBrInit = false;    // Flag that help with init current branch
      static branch CurrentBranch;            // Current branch that choosed (maybe can read from .mygit)
      crypto::hash CurrentCommitHash;         // Last commit hash
      tree QueueAdd;                          // Queue added files (saved like tree of filesystem)
      bool IsQueueInit = false;               // Flag that help with queueadd initialization

    public:
      /* Create branch by name
       * ARGUMENTS: 
       *   - Name of branch:
       *       const std::string &Branch;
       */
      branch( const std::string &Branch );

      /* Branch ctor by bytes data
       * ARGUMENTS:
       *   - Data vector:
       *       const std::vector<uint8_t> &Data;
       */
      branch( const std::vector<uint8_t> &Data );

      /* Function to get current branch 
       * ARGUMENTS: None.
       * RETURNS: 
       *   (branch) Current branch
       */
      branch& GetCurrentBranch( void );

      /* Swap current branch function 
       * ARGUMENTS:
       *   - Branch to swap:
       *       const branch &NewCurrBr;
       * RETURNS: None.
       */
      void SwapCurrentBranch( const branch &NewCurrBr );

      /* Function to get data by branch
       * ARGUMENTS: None.
       * RETURNS: 
       *   (std::vector<uint8_t>) Data in bytes.
       */
      std::vector<uint8_t> FromBranchToData( void );
    }; /* End of 'branch' class */
  }  /* end of 'resources' namespace */
} /* end of 'core' namespace */

#endif /* __branch_h_ */

/* END OF 'branch.h' FILE */