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
    Parent.GetHash()[CurrPos] = Data[CurrPos];
  CurrPos++;
  // Write time
  std::string TimeStr;

  TimeStr.resize(16);
  for (int i = 0; CurrPos < CurrPos + 16; CurrPos++)
    TimeStr[i++] = Data[CurrPos];
  Time = utils::TimeFromStr(TimeStr);
  CurrPos++;
  // Write current position
  for (int i = 0; CurrPos < CurrPos + Author.size(); CurrPos++)
    Author.push_back(Data[CurrPos]);
  CurrPos++;
  // Write message
  for (int i = 0; CurrPos < CurrPos + Message.size(); CurrPos++)
    Message.push_back(Data[CurrPos]);
  CurrPos++;
  // Write tree hash
  for (int i = 0; CurrPos < CurrPos + BYTES_HASH; CurrPos++)
    Tree.GetHash()[i] = Data[CurrPos];
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
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void core::resources::commit::Apply( void )
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
    TreeCommit.Apply();
  }
  catch ( std::runtime_error& Err )
  {
    throw(Err);
  }
} /* End of 'core::resources::commit::Apply' function */

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
    TreeCommit.MakeVersByTree(Path);
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
   *   - (Parent hash) (Time) (Author) (Message) (Tree hash)
   *     Without ()
   */
  std::vector<uint8_t> Data;
  int CurrPos = 0;
  
  // Write hash 
  Data.resize(BYTES_HASH * 2 + Author.size() + Message.size() + 16 + 4); // 16 Symbols - time without time zone and 4 for spaces
  for (CurrPos; CurrPos < BYTES_HASH; CurrPos++)
    Data[CurrPos] = Parent.GetHash()[CurrPos];
  Data[CurrPos++] = ' ';
  // Write time
  std::string TimeStr = std::format("{:%Y-%m-%d %H %M}", Time);
  for (int i = 0; CurrPos < CurrPos + 16; CurrPos++)
    Data[CurrPos] = TimeStr[i++];
  Data[CurrPos++] = ' ';
  // Write current position
  for (int i = 0; CurrPos < CurrPos + Author.size(); CurrPos++)
    Data[CurrPos] = Author[i++];
  Data[CurrPos++] = ' ';
  // Write message
  for (int i = 0; CurrPos < CurrPos + Message.size(); CurrPos++)
    Data[CurrPos] = Message[i++];
  Data[CurrPos++] = ' ';
  // Write tree hash
  for (int i = 0; CurrPos < CurrPos + BYTES_HASH; CurrPos++)
    Data[CurrPos] = Tree.GetHash()[i];
  
  return Data;
} /* End of 'core::resources::commit::DataFromCommit' function */

/* END OF 'commit.cpp' FILE */