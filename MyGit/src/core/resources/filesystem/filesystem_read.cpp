/* FILE:        filesystem_read.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 30.10.2026
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
  fs::path FilePath = BLOBS_OBJ_PATH / Hash.string().substr(0, 2) / Hash.string();
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
  fs::path FilePath = BRANCH_PATH / Branch;
  std::ifstream File(FilePath, std::ios::in | std::ios::binary);

  if (!File.is_open())
  {
    std::string message = "File of commit is not find " + Branch;
    throw std::runtime_error(message);
  }

  // Find commit
  std::string CurrHash, CurrStr;
  int cnt = 0;
  
  while (std::getline(File, CurrStr))
  {
    if (cnt++ <= 1)
      continue;
    CurrHash.insert(CurrHash.begin(),
                    CurrStr.begin() + BYTES_HASH + 1,
                    CurrStr.begin() + BYTES_HASH * 2 + 1);
    if (CurrHash == Hash.string())
      break;
    // Clear all current strings
    CurrHash.clear();
    CurrStr.clear();
  }
  std::vector<uint8_t> Data;

  Data.insert(Data.begin(), CurrStr.begin(), CurrStr.end());
  File.close();
  return Data;
} /* End of 'core::filesystem::ReadCommit' function */

/* Read all commits funcion
 * ARGUMENTS:
 *   - Branch name from what we need read commits:
 *       const std::string &Branch;
 * RETURNS: 
 *   (std::vector<std::vector<uint8_t>>) Pait hash-commit bytes;
 */
std::vector<std::vector<uint8_t>> core::filesystem::ReadAllCommits( const std::string &Branch )
{
  fs::path FilePath = BRANCH_PATH / Branch;
  std::ifstream File(FilePath);

  if (!File.is_open())
    throw std::runtime_error("File of branch cant be oppened (Read all commits step)");
  std::vector<std::vector<uint8_t>> HashCommitPairs;

  // Paing commit pairs and returns it
  std::string curr;
  int cnt = 0;
  std::vector<uint8_t> Bytes;

  while (std::getline(File, curr))
  {
    if (cnt++ <= 1) // Skip branch data and \n
      continue;
    Bytes.insert(Bytes.begin(), curr.begin(), curr.end());

    HashCommitPairs.push_back(Bytes);
  }
  return HashCommitPairs;
} /* End of 'core::filesystem::ReadAllCommits' fucntion */

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

/*******************************************
*
** DATABASE AND AUTHORIZATION FUNCTIONS **
*
*******************************************/

/* Function to read nickname of user
 * ARGUMENTS:
 *   - Nickname of user that need be read:
 *       const std::string &Nickname;
 * RETURNS: 
 *   (std::vector<uint8_t>) Bytes of user.
 */
std::vector<uint8_t> core::filesystem::ReadUser( const std::string &Nickname )
{
  std::ifstream File(DATABASE_PATH, std::ios::binary);

  if (!File.is_open())
    throw std::runtime_error("User cant be readed -> check right to read programm data " + Nickname);
  std::vector<uint8_t> Bytes;
  std::string curr;

  // Find user by nickname
  while (std::getline(File, curr))
    if (curr.find(Nickname) == std::string::npos)
      continue;
    else
      break;
  if (curr.size() == 0)
    throw std::runtime_error("User not find " + Nickname);
  Bytes.insert(Bytes.begin(), curr.begin(), curr.end());
  return Bytes;
} /* End of 'core::filesystem::ReadUser' function */

/* Function to read current user 
 * ARGUMENTS: None.
 * RETURNS:
 *   (std::string) Current user nickname
 */
std::string core::filesystem::ReadCurrUserSession( void )
{
} /* End of 'core::filesystem::ReadCurrUserSession' function */

/* END OF 'filesystem_read.cpp' FILE */