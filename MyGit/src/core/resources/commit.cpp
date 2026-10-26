/* FILE:        commit.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 04.10.2026
 * PURPOSE:     Git project.
 *              Resources - commit executor file
 */

#include "commit.h"

/* Ctor commit by byte data 
 * ARGUMENTS:
 *   - Data that readed from commit:
 *       const std::vector<uint8_t> &Data;
 */
core::resources::commit::commit( const std::vector<uint8_t> &Data )
{
  int CurrPos = 0;
  
  for (CurrPos; CurrPos < BYTES_HASH; CurrPos++)
    Parent.bytes()[CurrPos] = Data[CurrPos];
  CurrPos += BYTES_HASH + 2;
  // Write time
  std::string TimeStr;
  int SavePos = CurrPos;

  TimeStr.resize(16);
  for (int i = 0; CurrPos < SavePos + 16; CurrPos++)
    TimeStr[i++] = Data[CurrPos];
  Time = utils::TimeFromStr(TimeStr);
  CurrPos++;
  while (Data[CurrPos] != ' ')
    Author.push_back(Data[CurrPos++]);
  CurrPos++;
  CurrPos++;
  // Write message
  while (Data[CurrPos] != '"')
    Message.push_back(Data[CurrPos++]);
  CurrPos++;
  // Write tree hash
  SavePos = CurrPos;
  for (int i = 0; CurrPos < SavePos + BYTES_HASH; CurrPos++)
    Tree.bytes()[i] = Data[CurrPos];
} /* End of 'core::resources::commit::commit' fucntion */

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
core::resources::commit::commit( const core::crypto::hash &Parent,
                                 const core::crypto::hash &Tree,
                                 const std::string &Author,
                                 const std::string &Msg)
{
  commit::Parent = Parent;
  commit::Tree = Tree;
  commit::Author = Author;
  commit::Message = Msg;
  commit::Time = std::chrono::floor<std::chrono::minutes>(std::chrono::system_clock().now());
} /* End of 'core::resources::commit::commit' function */

/* Function to apply commit version 
 * ARGUMENTS: 
 *   - Path where version will be applied:
 *       std::strin Path;
 * RETURNS: None.
 */
void core::resources::commit::ApplyVersion( std::string Path )
{
  std::vector<uint8_t> Bytes;

  try
  {
    Bytes = filesystem::ReadTree(Tree);
  }
  catch ( std::runtime_error& Err )
  {
    throw(Err);
  }
  tree TreeCommit(Bytes);

  try
  {
    TreeCommit.ApplyVersion(Path);
  }
  catch ( std::runtime_error& Err )
  {
    throw(Err);
  }
} /* End of 'core::resources::commit::ApplyVersion' function */

/* Function to make version by commit and path where it need be
 * ARGUMENTS:
 *   - Path where we need version:
 *       std::string Path;
 *   - Hash of commit that need be applied:
 *       core::crypto::hash HashCommit;
 * RETURNS: None.
 */
void core::resources::commit::MakeVersionByCommit( std::string Path )
{
  std::vector<uint8_t> Bytes;

  try
  {
    Bytes = filesystem::ReadTree(Tree);
  }
  catch ( std::runtime_error& Err )
  {
    throw(Err);
  }
  tree TreeCommit(Bytes);
                          
  try
  {
    TreeCommit.ApplyVersion(Path);
  }
  catch ( std::runtime_error& Err )
  {
    throw(Err);
  }
} /* End of 'core::resources::commit::MakeVersionByCommit' function */

/* Function to get data from commit 
 * ARGUMENTS: None.
 * RETURNS:
 *   (std::vector<uint8_t>) Data of commit in bytes.
 */
std::vector<uint8_t> core::resources::commit::DataFromCommit( void )
{
  /* How commit saved in branch?
   *   - First:  Commit hash
   *   - Second: Data of commit
   */

  /* Data commit is:
   *   - (Parent hash) (Hash of commit) (Time) (Author) (Message) (Tree hash)
   *     Without ()
   */
  std::vector<uint8_t> Data;
  std::array<uint8_t, BYTES_HASH> CurrHash;
  int CurrPos = 0;
  
  CurrHash = Parent.bytes();
  // Write hash 
  Data.resize(BYTES_HASH * 2 + Author.size() + Message.size() + TIME_SYMBOLS + 7); // 5 symblos for spaces and 2 to ""
  Data.insert(Data.begin(), CurrHash.begin(), CurrHash.end());
  CurrPos += BYTES_HASH;
  Data[CurrPos++] = ' ';
  Data[CurrPos++] = ' ';
  // Write time
  std::string TimeStr = std::format("{:%Y-%m-%d %H:%M}", Time);

  Data.insert(Data.begin() + CurrPos, TimeStr.begin(), TimeStr.end());
  CurrPos += (int)TimeStr.size();
  Data[CurrPos++] = ' ';
  Data.insert(Data.begin() + CurrPos, Author.begin(), Author.end());
  CurrPos += (int)Author.size();
  Data[CurrPos++] = ' ';
  Data[CurrPos++] = '"';
  Data.insert(Data.begin() + CurrPos, Message.begin(), Message.end());
  CurrPos += (int)Message.size();
  Data[CurrPos++] = '"';
  Data[CurrPos++] = ' ';
  CurrHash = Tree.bytes();
  Data.insert(Data.begin() + CurrPos, CurrHash.begin(), CurrHash.end());

  crypto::hash HashCommit(Data);
  std::array<uint8_t, BYTES_HASH> HashArr = HashCommit.bytes();

  Data.insert(Data.begin() + BYTES_HASH + 1, HashArr.begin(), HashArr.end());  
  return Data;
} /* End of 'core::resources::commit::DataFromCommit' function */

/* END OF 'commit.cpp' FILE */