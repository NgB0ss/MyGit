/* FILE:        filesystem_read.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 24.10.2026
 * PURPOSE:     Git project.
 *              Filesystem read function module.
 */

#include "filesystem.h"

/* Function to read blob
 * ARGUMENTS:
 *   - Hash of blob what need be reed:
 *       const crypto:hash &Hash;
 * RETURNS:
 *  (std::vector<uint8_t>) Data of blob.
 */
std::vector<uint8_t> core::filesystem::ReadBlob( const crypto::hash &Hash )
{
  fs::path FilePath = BLOBS_OBJ_PATH / Hash.string();
  std::ifstream File(FilePath, std::ios::in | std::ios::binary | std::ios::ate );

  if (!File.is_open())
  {
    std::string message = "File of blob is not find" + Hash.string();
    throw std::runtime_error(message);
  }

  // If file was open
  std::streamsize Size = File.tellg();
  File.seekg(0, std::ios::beg);
  std::vector<uint8_t> Data(Size);
  File.read(reinterpret_cast<char *>(Data.data()), Size);
  if (File.fail())
    throw std::runtime_error("Data of blob cant be read");
  return Data;
} /* End of 'core::filesystem::ReadBlob' function */

/* Function to read tree
 * ARGUMENTS:
 *   - Hash of tree what need be reed:
 *       const crypto:hash &Hash;
 * RETURNS:
 *  (std::vector<uint8_t>) Data of tree.
 */
std::vector<uint8_t> core::filesystem::ReadTree( const crypto::hash &Hash )
{
  fs::path FilePath = TREES_OBJ_PATH / Hash.string().substr(0, 2) / Hash.string();
  std::ifstream File(FilePath, std::ios::in | std::ios::binary | std::ios::ate );

  if (!File.is_open())
  {
    std::string message = "File of tree is not find " + Hash.string();
    throw std::runtime_error(message);
  }

  // If file was open
  std::streamsize Size = File.tellg();
  File.seekg(0, std::ios::beg);
  std::vector<uint8_t> Data(Size);
  File.read(reinterpret_cast<char *>(Data.data()), Size);
  if (File.fail())
    throw std::runtime_error("Data of tree cant be read");
  File.close();
  return Data;
} /* End of 'core::filesystem::ReadTree' function */

/* Function to read commit
 * ARGUMENTS:
 *   - Name of branch:
 *       const std::string &Branch;
 *   - Hash of commit what need be reed:
 *       const crypto:hash &Hash;
 * RETURNS:
 *  (std::vector<uint8_t>) Data of commit.
 */
std::vector<uint8_t> core::filesystem::ReadCommit( const std::string &Branch, const crypto::hash &Hash )
{
  fs::path FilePath = BRANCH_PATH / Branch / ".brnch";
  std::ifstream File(FilePath, std::ios::in | std::ios::binary);

  if (!File.is_open())
  {
    std::string message = "File of commit is not find" + Branch;
    throw std::runtime_error(message);
  }

  // Find commit
  std::string CurrHash(BYTES_HASH, '\0');

  File.read(&CurrHash[0], BYTES_HASH);
  if (File.fail())
    throw std::runtime_error("Data of commit cant be read");
  while (CurrHash != Hash.string())
  {
    File.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    File.read(&CurrHash[0], BYTES_HASH);
    if (File.fail())
      throw std::runtime_error("Data of commit cant be read");
  }
  // Read data of commit
  std::string DataStr;
  std::getline(File, DataStr);
  if (File.fail())
    throw std::runtime_error("Data of commit cant be read");

  std::vector<uint8_t> Data(DataStr.size());

  for (int i = 0; i < DataStr.size(); i++)
    Data[i] = DataStr[i];

  File.close();
  return Data;
} /* End of 'core::filesystem::ReadCommit' function */

/* Function to read branch
 * ARGUMENTS:
 *   - Name of branch:
 *       const std::string &Branch;
 * RETURNS:
 *  (std::vector<uint8_t>) Data of branch.
 */
std::vector<uint8_t> core::filesystem::ReadBranch( const std::string &Branch )
{
  fs::path FilePath = BRANCH_PATH / Branch;
  std::ifstream File(FilePath);

  // Open file
  if (!File.is_open())                            
  {
    std::string message = "File of branch is not find" + Branch;
    throw std::runtime_error(message);
  }
  std::string DataStr;
  std::vector<uint8_t> Data;

  std::getline(File, DataStr);
  if (File.fail())
    throw std::runtime_error("Data of branch cant be read");
  Data.insert(Data.begin(), DataStr.begin(), DataStr.end());
  File.close();
  return Data;
} /* End of 'core::filesystem::ReadBranch' function */

/* Function to read name of current branch 
 * ARGUMENTS: None.
 * RETURNS:
 *   (std::string) Current branch.
 */
std::string core::filesystem::ReadCurrBranchName( void )
{
  // WARNING: Branch saved not binary 
  // Where current branch be saved?
  // .mygit\
  //    CurrentBranch
  //    ...
  static fs::path Path = fs::current_path() / ".mygit" / "CurrentBranch";
  std::ifstream File(Path);

  if (!File.is_open())
    throw(std::runtime_error("Current branch cant be opened"));
  std::string NameBrnch;

  std::getline(File, NameBrnch);
  if (File.fail())
    throw std::runtime_error("Data of current branch name cant be read");
  File.close();
  return NameBrnch;
} /* End of 'core::filesystem::ReadCurrBranchName' function */

/* Function to check saved branch before or no 
 * ARGUMENTS: 
 *   - Name of branch to need check:
 *       std::string NameBranch;
 * RETURNS:
 *   (bool) Is saved before or no.
 */
bool core::filesystem::IsBranchSavedBf( std::string NameBranch )
{
  fs::path Path = BRANCH_PATH / NameBranch;
  return fs::exists(Path);
} /* End of 'core::filesystem::IsBranchSavedBf' function */

/* Function to read file data
 * ARGUMENTS:
 *   - Path to file what need to be read:
 *       const std::string &Path;
 * RETURNS: 
 *   (std::vector<uint8_t>) Data of readed file
 */
std::vector<uint8_t> core::filesystem::ReadFileData( const std::string &Path )
{
  fs::path path(Path);
  std::ifstream File(path, std::ios::binary | std::ios::ate);

  // Catch error if file is not openned 
  if (!File.is_open())
  {
    std::runtime_error Err("File is not openned");
    std::cout << path;
    throw(Err);
  }

  // Aproximate file size
  std::streamsize Size;
  Size = File.tellg();
  File.seekg(0);

  // Read data
  std::vector<uint8_t> Data;

  Data.resize(Size);
  File.read(reinterpret_cast<char *>(Data.data()), Size);
  if (File.fail())
    throw std::runtime_error("Data of file cant be read");
  File.close();
  return Data;
} /* End of 'core::filesystem:ReadFileData' function */

/* Function to read filesystem state
 * ARGUMENTS: None.
 * RETURNS:
 *   (FileSystemState) Current filesystem state;
 */
core::filesystem::FileSystemState core::filesystem::ReadFileSystem( void )
{
  FileSystemState FSStt;

  fs::path MainPath = fs::current_path();  // Get path where mygit called

  // Recursive dirrectory itt to write all dirrectories to FileSystemState
  for (auto entry: fs::recursive_directory_iterator(MainPath))
    if (fs::is_regular_file(entry) && entry.path().string().find(".mygit") == -1)
    {
      std::string Path = entry.path().string();
      FileState FSt;

      FSt.Size = fs::file_size(entry);
      std::vector<uint8_t> Data;
      std::ifstream File(Path, std::ios::binary);

      if (!File.is_open())
        throw(std::runtime_error("File cant be opened"));

      Data.resize(FSt.Size);
      File.read(reinterpret_cast<char *>(Data.data()), FSt.Size);
      core::crypto::hash Hash(Data);

      FSt.Hash = Hash;
      FSStt.FSState.insert(std::pair<std::string, FileState> (Path, FSt));
    }

  return FSStt;
} /* End of 'core::filesystem::ReadFileSystem' function */

/* END OF 'filesystem_read.cpp' FILE */