/* FILE:        tree.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 28.10.2026
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
      if (!blob(path).Save())
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
  std::filesystem::path Relative, CurrentPath = std::filesystem::current_path();
  bool IsApp = false;

  // Is apply tree or make by tree in other path
  if (Path.size() == 0)
    IsApp = true;
  // If that tree must be applied to this dirrectory-> that mean thet we need to delete all file
  // Before we applied filesystem
  if (IsApp) 
  {
    filesystem::ClearFilesystem(std::filesystem::current_path().string());
  }

  // Write tree to filesystem state variable
  for (const auto &[defPath, hash]: FileSystemState)
  {
    // Correct defpath without \n
    std::filesystem::path Def;
    if (defPath[0] == '\n')
      Def = defPath.substr(1, defPath.size());
    else
      Def = defPath;
    // Aproximate realtive path
    Relative = std::filesystem::relative(Def, CurrentPath);
    if (IsApp)
      FSStt.FSState.insert({Def.string(), {0, hash}});
    else
      FSStt.FSState.insert({Path + "\\" + Relative.string(), {0, hash}});
  }

  // ApplyVersion filsystem with current path
  filesystem::MakeFileSystem(FSStt);
} /* End of 'core::resources::tree::ApplyVersion' function */

/* Function to bild data from tree class 
 * ARGUMENTS: None.
 * RETURNS: 
 *   (std::vector<uint8_t>)  Data that build from tree.
 */
std::vector<uint8_t> core::resources::tree::ToData( void ) const
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
} /* End of 'core::resources::tree::ToData' function */

/* Function to save tree
 * ARGUMENTS: None.
 * RETURNS: 
 *   (bool) Is save succes or not.
 */
bool core::resources::tree::Save( void ) const
{
  std::vector<uint8_t> BytesToSave;
  
  BytesToSave = ToData();
  return filesystem::WriteTree(GetHash(BytesToSave), BytesToSave);
} /* End of 'core::resources::Save' function */

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
    DataToSort = ToData();
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
  std::string_view StrDataToSort(reinterpret_cast<char *>(DataToSort.data()), DataToSort.size());

  size_t cnt = 0;
  while (cnt < StrDataToSort.size())
  {
    size_t it = StrDataToSort.find('\n', cnt);
    if (it == std::string_view::npos)
      it = StrDataToSort.size();
  
 
    std::string_view Curr = StrDataToSort.substr(cnt, it - cnt);
  
    if (!Curr.empty() && Curr.back() == '\r') {
      Curr.remove_suffix(1);
    }

    size_t StarPos = Curr.find("**");
    if (StarPos != std::string_view::npos)
    {
      std::string_view path = Curr.substr(0, StarPos);
      std::string_view hash = Curr.substr(StarPos + 2); 
      FilesView.push_back({path, hash});
    }

    cnt = it + 1;
  }

  // Sort tree
  std::sort(FilesView.begin(), FilesView.end(), [](const files &File1, const files &File2)
            {
              return File1.Path < File2.Path;
            });

  // Now decoding
  size_t total_size = 0;
  for (const auto& file : FilesView) {
      total_size += file.Path.size() + 2 + file.Hash.size() + 1; // path + "**" + hash + "\n"
  }

  std::vector<uint8_t> SortedData;
  SortedData.reserve(total_size);
 
  for (const auto& file : FilesView)
  {
    SortedData.insert(SortedData.end(), file.Path.begin(), file.Path.end());
    SortedData.push_back('*');
    SortedData.push_back('*');
    SortedData.insert(SortedData.end(), file.Hash.begin(), file.Hash.end());
    SortedData.push_back('\n');
  }

  return crypto::hash(SortedData);
} /* End of 'core::resources::tree::GetHash' function */

/* Function to check is tree empty or no
 * ARGUMENTS: None.
 * RETURNS: 
 *   (bool) Is Empty or not.
 */
bool core::resources::tree::IsEmpty( void ) const
{
  return !FileSystemState.size();
} /* End of 'core::respurces::tree::IsEmpty' function */

/* END OF 'tree.cpp' FILE */