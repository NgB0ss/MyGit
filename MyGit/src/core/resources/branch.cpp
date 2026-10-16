/* FILE:        branch.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 16.10.2026
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

  if (IsDelegate)
    return;

  // Set current commit to zero bytes hash
  CurrentCommitHash = crypto::hash(std::vector<uint8_t> ()); // ZERO_BYTES_BRNCH
  
  // Write new branch if ctor not delegated
  try { SaveBranch(); }
  catch ( std::runtime_error Err ) { std::cout << Err.what(); }
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
    QueueAdd = tree(filesystem::ReadTree(crypto::hash(CurrBytes)));
  }
} /* End of 'core::resources::branch::branch' fucntion */

/* Function to apply tree to branch
 * ARGUMENTS: 
 *   - Tree to apply to branch:
 *       const tree &NewTree;
 * RETURNS: None.
 */
void core::resources::branch::ApplyTree( const core::resources::tree &NewTree )
{
  QueueAdd = NewTree;
}

/* Function to get current branch 
 * ARGUMENTS: None.
 * RETURNS: 
 *   (branch) Current branch
 */
core::resources::branch& core::resources::branch::GetCurrentBranch( void )
{
  if (!IsCurrentBrInit)
    try
    {
      CurrentBranch = branch(filesystem::ReadCurrBranchName());
      IsCurrentBrInit = true;
    }
    catch ( std::runtime_error Err )
    {
      std::cout << Err.what() << std::endl;
    }
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
   *       (CurrentCommitHash) (IsQeueAddInit) (QueueHash)
   * COMMITS WILL BE WRITE AFTER BRANCH INFO
   */
  std::vector<uint8_t> Data, QueueDt;
  std::array<uint8_t, BYTES_HASH> BytesCurrCommit = CurrentCommitHash.bytes();

  QueueDt = QueueAdd.DataFromTree();
  crypto::hash HashIndex(QueueDt);
  std::string HashStr = HashIndex.string();

  Data.insert(Data.begin(), NameBranch.begin(), NameBranch.end());
  Data.push_back(' ');
  Data.insert(Data.end(), BytesCurrCommit.begin(), BytesCurrCommit.end());
  Data.push_back(' ');
  Data.push_back(IsQueueInit);
  Data.push_back(' ');
  Data.insert(Data.end(), HashStr.begin(), HashStr.end());
  return Data;
} /* End of 'core::resources::branch::FromBranchToData' fucntion */

/* Function to save branch in filesystem
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void core::resources::branch::SaveBranch( void )
{
  std::vector<uint8_t> BytesBrnch = FromBranchToData();

  if (IsQueueInit)
  {
    std::vector<uint8_t> QueueData = QueueAdd.DataFromTree();

    if (!filesystem::WriteTree(crypto::hash(QueueData), QueueData))
      throw(std::runtime_error("Tree cant be written -> Make mygit init or check rights of mygit"));
  }

  if (!filesystem::WriteBranch(NameBranch, BytesBrnch))
    throw(std::runtime_error("Branch cant be written -> Make mygit init or check rights of programm"));
} /* End of 'core::resources::branch::SaveBranch' function */


/* END OF 'branch.cpp' FILE */