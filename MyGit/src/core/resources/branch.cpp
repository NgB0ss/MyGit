/* FILE:        branch.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 10.10.2026
 * PURPOSE:     Git project.
 *              Resources - branch executor file
 */

#include "branch.h"

core::resources::branch core::resources::branch::CurrentBranch;

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

  NameBranch = Branch;

  try
  {
    Bytes = filesystem::ReadBranch(Branch);
  }
  catch ( const std::runtime_error &Err )
  {
    IsDelegate = false;
  }
  
  // Delegate if we can
  if (IsDelegate)
    (*this) = branch(Bytes);

  if (!IsCurrentBrInit)
    // Read name of current branch from .mygit
    // Create current branch
    try
    {
      CurrentBranch = branch(filesystem::ReadBranch(filesystem::ReadCurrBranchName()));
    }
    catch ( std::runtime_error Err )
    {
      std::cout << Err.what() << std::endl;
    }

  if (IsDelegate)
    return;

  // Set current commit to zero bytes hash
  CurrentCommitHash = crypto::hash(std::vector<uint8_t> ()); // ZERO_BYTES_BRNCH
  
  // Write new branch if ctor not delegated
  if (filesystem::WriteBranch(NameBranch, FromBranchToData()))
    std::cout << "Branch successfull create -> " << NameBranch << std::endl;
    
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
    if (cnt != ' ')
      CurrBytes.push_back(cnt), AllCount++;
    else
      break;
  NameBranch = std::string(CurrBytes.begin(), CurrBytes.end());
  AllCount++;
  CurrBytes.insert(CurrBytes.begin(),
                   Data.begin() + NameBranch.size(),
                   Data.begin() + NameBranch.size() + BYTES_HASH);
  CurrentCommitHash = crypto::hash(CurrBytes);
  CurrBytes.clear();
  AllCount += 32 + 1;
  IsQueueInit = Data[AllCount];
  
  if (IsQueueInit)
  {
    CurrBytes.insert(CurrBytes.begin(), (Data.begin() + AllCount), Data.end());
    QueueAdd = tree(CurrBytes);
  }
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
  filesystem::WriteCurrBranchName(NewCurrBr.NameBranch);
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
   * COMMITS WILL BE WRITE AFTER BRANCH INFO
   */
  std::vector<uint8_t> Data, QueueDt;
  std::array<uint8_t, BYTES_HASH> BytesCurrCommit = CurrentCommitHash.GetHash();

  QueueDt = QueueAdd.DataFromTree();
  Data.insert(Data.begin(), NameBranch.begin(), NameBranch.end());
  Data.push_back(' ');
  Data.insert(Data.end(), BytesCurrCommit.begin(), BytesCurrCommit.end());
  Data.push_back(' ');
  Data.push_back(IsQueueInit);
  Data.push_back(' ');
  Data.insert(Data.end(), QueueDt.begin(), QueueDt.end());
  return Data;
} /* End of 'core::resources::branch::FromBranchToData' fucntion */


/* END OF 'branch.cpp' FILE */