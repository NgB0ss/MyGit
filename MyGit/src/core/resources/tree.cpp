/* FILE:        tree.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 26.10.2026
 * PURPOSE:     Git project.
 *              Resources - tree executor file
 */

#include "tree.h"

/* Default ctor of tree resource
 * ARGUMENTS: 
 *   - Type ctor that you need:
 *       TreeCtor Type;
 */
core::resources::tree::tree( TreeCtor Type )
{
  if (Type == TreeCtor::BySystem)  // Ctor by system
  {
    filesystem::FileSystemState FSStt = filesystem::ReadFileSystem();

    for (const auto &[path, FStt]: FSStt.FSState)
      FileSystemState[path] = FStt.Hash;
    // Create blobs by tree that not created
    for (const auto &[path, hash]: FileSystemState)
      if (!filesystem::WriteBlob(hash, blob(path).ToData()))
        std::cout << "Blob cant be writed " << hash.string() << std::endl;
  }
  else  // Ctor default
    *this = tree();
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
      Hash = core::crypto::hash::FromStrToHash(OnePair.substr(PosStar + 2, OnePair.size()));

      FileSystemState.insert({Path, Hash});  // Add map uno
      OnePair.clear();                       // Clear pair string
    }
    OnePair.push_back(Data[i]);
  }
} /* End of 'core::resources::tree::tree' function */

/* Function that create version by path and tree data
 * ARGUMENTS:
 *    - Path where version need to be:
 *       std::string Path;
 * RETURNS: None.
 */
void core::resources::tree::ApplyVersion( std::string Path ) 
{
  filesystem::FileSystemState FSStt;

  std::filesystem::path DefPath, CurrentPath = std::filesystem::current_path();

  // Write tree to filesystem state variable
  for (const auto &[defPath, hash]: FileSystemState)
  {
    DefPath = std::filesystem::path(defPath);
    DefPath = std::filesystem::relative(DefPath, CurrentPath);
    if (DefPath.string().size() == 0)
      FSStt.FSState.insert({CurrentPath.string(), {0, FileSystemState[defPath]}});
    else
      FSStt.FSState.insert({Path + DefPath.string(), {0, FileSystemState[defPath]}});
  }

  // ApplyVersion filsystem with current path
  filesystem::MakeFileSystem(FSStt);
} /* End of 'core::resources::tree::ApplyVersion' function */

/* Function to bild data from tree class 
 * ARGUMENTS: None.
 * RETURNS: 
 *   (std::vector<uint8_t>)  Data that build from tree.
 */
std::vector<uint8_t> core::resources::tree::DataFromTree( void ) const
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
    OnePair += hash.string();
    OnePair += "\n";
    // Write pair to Data
    for (int i = 0; i < OnePair.size(); pointer++)
      Data[pointer] = OnePair[i++];
  }
  auto it = std::find(Data.begin(), Data.end(), '\0'); 

  Data.erase(it, Data.end());
  Data.shrink_to_fit();
  return Data;
} /* End of 'core::resources::tree::DataFromTree' function */

/* Function to get hash by tree class
 * ARGUMENTS: 
 *   - const std::vector<uint8_t> &Data;
 * RETURNS: 
 *   (core::crypto::hash) Hash of tree.
 */
core::crypto::hash core::resources::tree::GetHash( const std::vector<uint8_t> &Data ) const
{
  // Need sort tree, and get hash
  // We need sort tree bcse map is not know how elements insert in there
  // And if some elements swap, hash1 != hash2
  
  // Check, maybe we get data before
  std::vector<uint8_t> DataToSort;
  bool IsDataGet = true;

  if (Data.size() == 0)
    DataToSort = DataFromTree();
  else
    DataToSort = Data;
  // Create pairs vector to sort it after
  // Create struct to pairs hash->path
  struct files
  {
    std::string_view Path;
    std::string_view Hash;
  };

  std::vector<files> FilesView;
  int cnt = 0, it = 0, StarPos = 0;
  std::string_view StrDataToSort(reinterpret_cast<char *>(DataToSort.data()), DataToSort.size());
  std::string_view Curr;

  while (cnt++ < StrDataToSort.size())
  {
    it = StrDataToSort.find('\n', cnt);
    if (it == std::string::npos)
      it = StrDataToSort.size();
    Curr = StrDataToSort.substr(cnt, it - cnt);
    
    StarPos = StrDataToSort.find('*', cnt);
    if (StarPos != std::string::npos)
      FilesView.push_back({Curr.substr(0, StarPos), Curr.substr(StarPos + 2, Curr.size())});

    cnt = it + 1;
    it = 0;
  }
  // Sort tree
  std::sort(FilesView.begin(), FilesView.end(), []( const files &File1, const files &File2)
            {
              return File1.Path < File2.Path;
            });
} /* End of 'core::resources::tree::GetHash' function */

/* END OF 'tree.cpp' FILE */