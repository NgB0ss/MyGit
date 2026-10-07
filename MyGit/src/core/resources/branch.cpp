/* FILE:        branch.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 07.10.2026
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
  std::vector<uint8_t> CurrBytes;
  int AllCount = 0;

  for (auto cnt: Data)
    if (Data[cnt] != ' ')
      CurrBytes.push_back(Data[cnt]), AllCount = cnt;
    else
      break;
  CurrentCommitHash = crypto::hash(CurrBytes);
  CurrBytes.clear();
  AllCount++;
  IsQueueInit = Data[AllCount];
  
  CurrBytes.insert(CurrBytes.begin(), (Data.begin() + AllCount), Data.end());
  QueueAdd = tree(CurrBytes);
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
  std::vector<uint8_t> Data, QueueDt;

  QueueDt = QueueAdd.DataFromTree();
  Data.insert(Data.begin(), CurrentCommitHash.GetHash().begin(), CurrentCommitHash.GetHash().end());
  Data.push_back(' ');
  Data.push_back(IsQueueInit);
  Data.push_back(' ');
  Data.insert(Data.end(), QueueDt.begin(), QueueDt.end());
  return Data;
} /* End of 'core::resources::branch::FromBranchToData' fucntion */


/* END OF 'branch.cpp' FILE */