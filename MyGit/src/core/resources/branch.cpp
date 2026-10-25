/* FILE:        branch.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 24.10.2026
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
  catch ( std::runtime_error Err ) { throw Err; }
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
  AllCount += BYTES_HASH + 1;
  IsQueueInit = Data[AllCount];
  AllCount += 2;
  
  if (IsQueueInit)
  {
    std::string HashStr;

    HashStr.insert(HashStr.begin() , (Data.begin() + AllCount), Data.end());
    QueueAdd = tree(filesystem::ReadTree(crypto::hash::FromStrToHash(HashStr)));
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
  // Init queue
  QueueAdd = NewTree;
  IsQueueInit = true;
} /* End of 'core::resources::branch::ApplyTree' function */

/* Function to get tree from branch
 * ARGUMENTS: None
 * RETURNS: 
 *   (tree *) Pointer to queue of branch
 */
core::resources::tree * core::resources::branch::GetTree( void )
{
  if (IsQueueInit)
    return &QueueAdd;
  return nullptr;
} /* End of 'core::resources::branch::GetTree' function */

/* Function to get last hash of commit 
 * ARGUMENTS: None.
 * RETURNS: 
 *   (crytpo::hash) Hash of parrent commit
 */
core::crypto::hash core::resources::branch::GetLastCmmtHash( void )
{
  return CurrentCommitHash;
} /* End of 'core::resources::branch::GetLastCmmtHash' function */

/* Function to get name of branch
 * ARGUMENTS: None.
 * RETURNS:
 *   (std::string) Name of branch.
 */
std::string core::resources::branch::GetName( void )
{
  return NameBranch;
} /* End of 'core::resources::branch::GetName' function */

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
      throw Err;
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
  std::string BytesCurrCommit = CurrentCommitHash.string();

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
      throw(std::runtime_error("Tree cant be written -> Make mygit init or check rights of mygit\n"));
  }

  if (!filesystem::WriteBranch(NameBranch, BytesBrnch))
    throw(std::runtime_error("Branch cant be written -> Make mygit init or check rights of programm\n"));
} /* End of 'core::resources::branch::SaveBranch' function */


/* END OF 'branch.cpp' FILE */