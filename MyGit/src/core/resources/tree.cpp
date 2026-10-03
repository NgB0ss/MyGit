/* FILE:        tree.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 29.09.2026
 * PURPOSE:     Git project.
 *              Resources - tree executor file
 */

#include "tree.h"

/* Default ctor of tree resource
 * ARGUMENTS: None.
 */
core::resources::tree::tree( void )
{
  filesystem::FileSystemState FSStt = filesystem::ReadFileSystem();

  for (const auto &[path, FStt]: FSStt.FSState)
    FileSystemState[path] = FStt.Hash;
} /* End of 'core::resources::tree::tree' function */

/* Function to bild data from tree 
 * ARGUMENTS:
 *   - Data:
 *       std::vector<uint8_t> Data;
 */
core::resources::tree::tree( std::vector<uint8_t> Data )
{
  // INVERSE FUNCTION -> FromTreeToData
  int pointer = 0;
  std::string OnePair;

  for (int i = 0; i < Data.size(); i++)
  {
    if (Data[i] == '\n')  // End of pair
    {  
      std::string Path;
      core::crypto::hash Hash;
      size_t PosStar = OnePair.find('*');

      Path = OnePair.substr(0, PosStar);     // Path ro file
      Hash = core::crypto::hash::FromStrToHash(OnePair.substr(PosStar + 1, OnePair.size()));

      FileSystemState.insert({Path, Hash});  // Add map uno
      OnePair.clear();                       // Clear pair string
    }
    OnePair.push_back(Data[i]);
  }
} /* End of 'core::resources::tree::tree' function */

/* Function to apply tree to filesystem
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void core::resources::tree::Apply( void )
{
  filesystem::FileSystemState FSStt;

  // Write tree to filesystem state variable
  for (const auto &[path, hash]: FileSystemState)
    FSStt.FSState.insert({path, {0, FileSystemState[path]}});

  // Apply filsystem with current path
  filesystem::MakeFileSystem(FSStt);
} /* End of 'core::resources::tree::Apply' function */

/* Function that create version by path and tree data
 * ARGUMENTS:
 *    - Path where version need to be:
 *       std::string Path;
 * RETURNS: None.
 */
void core::resources::tree::MakeVersByTree( std::string Path )
{
  filesystem::FileSystemState FSStt;

  // Write tree to filesystem state variable
  for (const auto &[defPath, hash]: FileSystemState)
    FSStt.FSState.insert({Path + defPath, {0, FileSystemState[defPath]}});

  // Apply filsystem with current path
  filesystem::MakeFileSystem(FSStt);
} /* End of 'core::resources::tree::MakeVersByTree' function */

/* Function to bild data from tree class 
 * ARGUMENTS: None.
 * RETURNS: 
 *   (std::vector<uint8_t>)  Data that build from tree.
 */
std::vector<uint8_t> core::resources::tree::DataFromTree( void )
{
  /* HOW WRITE:
   *   - PATH TO FILE, HASH OF BLOB FILE, \n
   *     ...
   */
  std::vector<uint8_t> Data;
  int pointer = 0;

  Data.resize(FileSystemState.size() * (MAX_PATH + BYTES_HASH));
  for (const auto& [path, hash]: FileSystemState)
  {
    std::string OnePair = path;

    OnePair += "**";
    OnePair += hash.GetStrHash();
    OnePair += "\n";
    // Write pair to Data
    for (int i = 0; pointer < OnePair.size(); pointer++)
      Data[pointer] = OnePair[i++];
  }
  Data.shrink_to_fit();
  return Data;
} /* End of 'core::resources::tree::DataFromTree' function */

/* END OF 'tree.cpp' FILE */