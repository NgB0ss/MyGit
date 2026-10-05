/* FILE:        branch.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 06.10.2026
 * PURPOSE:     Git project.
 *              Resources - branch executor file
 */

#include "branch.h"

/* Create branch by name
 * ARGUMENTS: 
 *   - Name of branch:
 *       const std::string &Branch;
 */
core::resources::branch::branch( const std::string &Branch )
{
  CurrentCommitHash = crypto::hash(std::vector<uint8_t> ()); // e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
  if (!IsCurrentBrInit)
    ;// Read current branch
  
} /* End of 'core::resources::branch::branch' fucntion */

/* Branch ctor by bytes data
 * ARGUMENTS:
 *   - Data vector:
 *       const std::vector<uint8_t> &Data;
 */
core::resources::branch::branch( const std::vector<uint8_t> &Data )
{
} /* End of 'core::resources::branch::branch' fucntion */

/* Function to get current branch 
 * ARGUMENTS: None.
 * RETURNS: 
 *   (branch) Current branch
 */
core::resources::branch& core::resources::branch::GetCurrentBranch( void )
{
  return CurrentBranch;
} /* End of 'core::resources::branch::GetCurrentBranch' fucntion */

/* Swap current branch function 
 * ARGUMENTS:
 *   - Branch to swap:
 *       const branch &NewCurrBr;
 * RETURNS: None.
 */
void core::resources::branch::SwapCurrentBranch( const branch &NewCurrBr )
{
  CurrentBranch = NewCurrBr;
} /* End of 'core::resources::branch::SwapCurrentBranch' fucntion */

/* Function to get data by branch
 * ARGUMENTS: None.
 * RETURNS: 
 *   (std::vector<uint8_t>) Data in bytes.
 */
std::vector<uint8_t> core::resources::branch::FromBranchToData( void )
{
} /* End of 'core::resources::branch::FromBranchToData' fucntion */


/* END OF 'branch.cpp' FILE */