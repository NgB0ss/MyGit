/* FILE:        filesystem_write.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 28.09.2026
 * PURPOSE:     Git project.
 *              Filesystem write function module.
 */

#include "filesystem.h"

/* Function to write blob 
 * ARGUMENTS:
 *   - Hash of blob:
 *       const crypto::hash &Hash;
 *   - Data of blob:
 *       const std::vector<uint8_t> &Data;
 * RETURNS:
 *   (bool) Write success or no.
 */
bool core::filesystem::WriteBlob( const crypto::hash &Hash, const std::vector<uint8_t> &Data )
{
  static fs::path path = std::filesystem::current_path();  // Get dirrectory where we need .mygit
  fs::path folder_path = path / "objects" / "blobs" / Hash.GetStrHash().substr(0, 2);

  fs::create_directories(folder_path);
  fs::path file_path = folder_path / Hash.GetStrHash();
  std::ofstream file(file_path, std::ios::binary);

  if (!file.is_open())
    return false;
  
  // If blob file created
  file.write(reinterpret_cast<const char*>(Data.data()), Data.size());
  return true;
} /* End of 'core::filesystem::WriteBlob' function */

/* Function to write tree 
 * ARGUMENTS:
 *   - Hash of tree:
 *       const core::crypto::hash &Hash;
 *   - Data of tree:
 *       const std::vector<uint8_t> &Data;
 * RETURNS:
 *   (bool) Write success or no.
 */
bool core::filesystem::WriteTree( const crypto::hash &Hash, const std::vector<uint8_t> &Data )
{
  static fs::path path = std::filesystem::current_path();  // Get dirrectory where we need .mygit
  fs::path folder_path = path / "objects" / "trees" / Hash.GetStrHash().substr(0, 2);

  fs::create_directories(folder_path);
  fs::path file_path = folder_path / Hash.GetStrHash();
  std::ofstream file(file_path, std::ios::binary);

  if (!file.is_open())
    return false;
  
  // If tree file created
  file.write(reinterpret_cast<const char*>(Data.data()), Data.size());
  return true;
} /* End of 'core::filesystem::WriteTree' function */

/* Function to write commit 
 * ARGUMENTS:
 *   - Name of branch:
 *       const std::string &Branch;
 *   - Data of commit:
 *       const std::vector<uint8_t> &Data;
 * RETURNS:
 *   (bool) Write success or no.
 */
bool core::filesystem::WriteCommit( const std::string &Branch, const std::vector<uint8_t> &Data )
{
  static fs::path path = std::filesystem::current_path();  // Get dirrectory where we need .mygit
  fs::path folder_path = path / "branches";

  fs::create_directories(folder_path);
  fs::path file_path = folder_path / Branch;
  std::ofstream file(file_path, std::ios::out | std::ios::app | std::ios::binary);

  if (!file.is_open())
    return false;
  
  // Write commit data
  file.write(reinterpret_cast<const char*>(Data.data()), Data.size());
  return true;
} /* End of 'core::filesystem::WriteCommit' function */

/* Function to write branch 
 * ARGUMENTS:
 *   - Name of branch:
 *       const std::string &Branch;
 *   - Data of branch:
 *       const  std::vector<uint8_t> &Data;
 * RETURNS:
 *   (bool) Write success or no.
 */
bool core::filesystem::WriteBranch( const std::string &Branch, const std::vector<uint8_t> &Data )
{
  static fs::path path = std::filesystem::current_path();  // Get dirrectory where we need .mygit
  fs::path folder_path = path / "branches";

  fs::create_directories(folder_path);
  fs::path file_path = folder_path / Branch;
  std::ofstream file(file_path, std::ios::binary);

  if (!file.is_open())
    return false;
  
  // If blob file created
  file.write(reinterpret_cast<const char*>(Data.data()), Data.size());
  return true;
} /* End of 'core::filesystem::WriteBranch' function */

/* Function to write file data
 * ARGUMENTS:
 *   - Path to file what need to be write:
 *       const std::string &Path;
 *   - Data to be writed:
 *       const std::vector<uint8_t> &Data;
 * RETURNS: 
 *    (bool) Operation success or no.
 */
bool core::filesystem::WriteFileData( const std::string &Path, const std::vector<uint8_t> &Data )
{
  std::ofstream File(Path, std::ios::binary);

  if (!File.is_open())
  {
    std::runtime_error Err(Path);
    throw(Err);
  }
  File.write(reinterpret_cast<const char *>(Data.data()), Data.size());
  return true;
} /* End of 'core::filesystem::WriteFileData' function */

/* Function to make filesystem by resource
 * ARGUMENTS: 
 *   - Filesystem that need to be:
 *       const FileSystemState &FSStt;
 *   - 
 * RETURNS: None.
 */
void core::filesystem::MakeFileSystem( const FileSystemState &FSStt )
{
  // Run by every dirrectories
  for (const auto &[path, FileState]: FSStt.FSState)
  {
    fs::path Path(path);
    std::string FileName = Path.filename().string();
    
    Path.remove_filename();
    fs::create_directories(Path);
    Path = Path / FileName;
    std::ofstream File(Path, std::ios::binary);

    if (!File.is_open())
      throw(std::runtime_error("File cant oppened"));
    std::vector<uint8_t> Blob = ReadBlob(FileState.Hash);

    File.write(reinterpret_cast<char *>(Blob.data()), Blob.size());
  }
}  /* End of 'core::filesystem::MakeFileSystem' function */

/* END OF 'filesystem_write.cpp' FILE */