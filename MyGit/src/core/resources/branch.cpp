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
  // Try to delegate ctor by bytes
  std::vector<uint8_t> Bytes;
  bool IsDelegate = true;

  try
  {
    Bytes = filesystem::ReadBranch(Branch);
  }
  catch ( std::runtime_error &Err )
  {
    IsDelegate = false;
  }
  // Delegate if we can
  if (IsDelegate)
    (*this) = branch(Bytes);

  if (!IsCurrentBrInit)
    // Read name of current branch from .mygit
    // Create current branch
    CurrentBranch = branch(filesystem::ReadBranch(filesystem::ReadCurrBranchName()));

  if (IsDelegate)
    return;

  CurrentCommitHash = crypto::hash(std::vector<uint8_t> ()); // ZERO_BYTES_BRNCH
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
  /* How branch wiil be saved in bytes?:
   *   - In default sequence field:
   *       (CurrentCommitHash) (IsQeueAddInit) (QueueData <- Watch in tree decoder)
   */


} /* End of 'core::resources::branch::FromBranchToData' fucntion */


/* END OF 'branch.cpp' FILE */