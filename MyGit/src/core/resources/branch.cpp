/* FILE:        branch.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 28.10.2026
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
  try { Save(); }
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
                   Data.begin() + AllCount,
                   Data.begin() + AllCount + BYTES_HASH);
  std::array<uint8_t, BYTES_HASH> Arr;

  for (int i = 0; i < BYTES_HASH; i++)
    Arr[i] = CurrBytes[i];
  CurrentCommitHash.SetHash(Arr);
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
void core::resources::branch::SetTree( const core::resources::tree &NewTree )
{
  // Init queue
  QueueAdd = NewTree;
  if (NewTree.IsEmpty())
    IsQueueInit = false;
  else
    IsQueueInit = true;
} /* End of 'core::resources::branch::SetTree' function */

/* Function to set last commit hash 
 * ARGUMENTS: 
 *   - Commit to set hash:
 *       commit NewLastCommit;
 * RETURNS: None.
 */
void core::resources::branch::SetHashCurrCommit( const commit &NewLastCommit )
{
  CurrentCommitHash = crypto::hash(NewLastCommit.GetHash());
} /* End of 'core::resources::branch::SetHashCurrCommit' function */

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
std::string core::resources::branch::GetName( void ) const
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
std::vector<uint8_t> core::resources::branch::ToData( void ) const
{
  /* How branch wiil be saved in bytes?:
   *   - In default sequence field:
   *       (CurrentCommitHash) (IsQeueAddInit) (QueueHash)
   * COMMITS WILL BE WRITE AFTER BRANCH INFO
   */
  std::vector<uint8_t> Data;
  std::string BytesCurrCommit = CurrentCommitHash.string();

  crypto::hash HashIndex = QueueAdd.GetHash();
  std::string HashStr = HashIndex.string();

  Data.insert(Data.begin(), NameBranch.begin(), NameBranch.end());
  Data.push_back(' ');
  Data.insert(Data.end(), BytesCurrCommit.begin(), BytesCurrCommit.end());
  Data.push_back(' ');
  Data.push_back(IsQueueInit);
  Data.push_back(' ');
  Data.insert(Data.end(), HashStr.begin(), HashStr.end());
  return Data;
} /* End of 'core::resources::branch::ToData' fucntion */

/* Function to save branch in filesystem
 * ARGUMENTS: None.
 * RETURNS: 
 *   (bool) Is save success or not.
 */
bool core::resources::branch::Save( void ) const
{
  std::vector<uint8_t> BytesBrnch = ToData();

  if (IsQueueInit)
    QueueAdd.Save();

  return filesystem::WriteBranch(NameBranch, BytesBrnch);
} /* End of 'core::resources::branch::Save' function */



/* END OF 'branch.cpp' FILE */