/* FILE:        filesystem_read.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 28.09.2026
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
  static fs::path Path = fs::current_path();
  fs::path FilePath = Path / "objects" / "blobs" / Hash.GetStrHash();
  std::ifstream File(FilePath, std::ios::in | std::ios::binary | std::ios::ate );

  if (!File.is_open())
  {
    std::string message = "File of blob is not find" + Hash.GetStrHash();
    throw std::runtime_error(message);
  }

  // If file was open
  std::streamsize Size = File.tellg();
  File.seekg(0, std::ios::beg);
  std::vector<uint8_t> Data(Size);
  File.read(reinterpret_cast<char *>(Data.data()), Size);
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
  static fs::path Path = fs::current_path();
  fs::path FilePath = Path / "objects" / "trees" / Hash.GetStrHash();
  std::ifstream File(FilePath, std::ios::in | std::ios::binary | std::ios::ate );

  if (!File.is_open())
  {
    std::string message = "File of tree is not find" + Hash.GetStrHash();
    throw std::runtime_error(message);
  }

  // If file was open
  std::streamsize Size = File.tellg();
  File.seekg(0, std::ios::beg);
  std::vector<uint8_t> Data(Size);
  File.read(reinterpret_cast<char *>(Data.data()), Size);
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
  static fs::path Path = fs::current_path();
  fs::path FilePath = Path / "branches" / Branch / ".brnch";
  std::ifstream File(FilePath, std::ios::in | std::ios::binary);

  if (!File.is_open())
  {
    std::string message = "File of commit is not find" + Branch;
    throw std::runtime_error(message);
  }

  // Find commit
  std::string CurrHash(BYTES_HASH, '\0');

  File.read(&CurrHash[0], BYTES_HASH);
  while (CurrHash != Hash.GetStrHash())
  {
    File.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    File.read(&CurrHash[0], BYTES_HASH);
  }
  // Read data of commit
  std::string DataStr;
  std::getline(File, DataStr);

  std::vector<uint8_t> Data(DataStr.size());

  for (int i = 0; i < DataStr.size(); i++)
    Data[i] = DataStr[i];

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
  static fs::path Path = fs::current_path();
  fs::path FilePath = Path / "branches" / Branch;
  std::ifstream File(FilePath, std::ios::in | std::ios::binary);

  // Open file
  if (!File.is_open())
  {
    std::string message = "File of branch is not find" + Branch;
    throw std::runtime_error(message);
  }

  // Get hash of branch
  std::string HashBranch;
  std::getline(File, HashBranch);
  
  // Get end of file and read hash of last commit 
  File.seekg(0, std::ios::end);
  std::streampos fileSize = File.tellg();

  if (fileSize == 0)
  {
    std::string message = "File is empty" + Branch;
    throw std::runtime_error(message);
  }

  std::streamoff lastLineStart = 0;
  for (std::streamoff offset = 2; offset <= fileSize; offset++)
  {
    File.seekg(-offset, std::ios::end);
    char ch;

    File.get(ch);
    if (ch == '\n')
    {
      lastLineStart = File.tellg(); 
      break;
    }
  }

  File.seekg(lastLineStart);
  std::string CommitHashStr;
  std::vector<uint8_t> Data(BYTES_HASH * 2);

  File.read(&CommitHashStr.data()[0], BYTES_HASH);

  // Write hash branch to data
  for (int i = 0; i < BYTES_HASH; i++)
    Data[i] = HashBranch[i];

  // Write hash last commit to data
  for (int i = BYTES_HASH; i < BYTES_HASH * 2; i++)
    Data[i] = CommitHashStr[i - BYTES_HASH];
  return Data;
} /* End of 'core::filesystem::ReadBranch' function */

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
  File.read(reinterpret_cast<char *>(Data.data()), Size);
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
  MainPath = MainPath.parent_path();       // Get parrent of dirrectory where be .mygit
  
  // Recursive dirrectory itt to write all dirrectories to FileSystemState
  for (auto entry: fs::recursive_directory_iterator(MainPath))
    if (fs::is_regular_file(entry))
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
      FSt.Hash = crypto::hash(Data);
      FSStt.FSState.insert(std::pair<std::string, FileState> (Path, FSt));
    }

  return FSStt;
} /* End of 'core::filesystem::ReadFileSystem' function */

/* END OF 'filesystem_read.cpp' FILE */