/* FILE:        filesystem_write.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 25.10.2026
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
  fs::path folder_path = BLOBS_OBJ_PATH / Hash.string().substr(0, 2);

  fs::create_directories(folder_path);
  fs::path file_path = folder_path / Hash.string();

  if (fs::exists(file_path)) // If that blob exist dont need overwrtie it
    return true;
  std::ofstream file(file_path, std::ios::binary);

  if (!file.is_open())
    return false;

  // If blob file created
  file.write(reinterpret_cast<const char*>(Data.data()), Data.size());
  if (file.fail())     // Check, wite file bytes or no
  {
    file.close();
    return false;
  }

  file.close();
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
  fs::path folder_path = TREES_OBJ_PATH / Hash.string().substr(0, 2);

  fs::create_directories(folder_path);
  fs::path file_path = folder_path / Hash.string();
  std::ofstream file(file_path, std::ios::binary);

  if (!file.is_open())
    return false;

  // If tree file created
  file.write(reinterpret_cast<const char*>(Data.data()), Data.size());
  if (file.fail())     // Check, wite file bytes or no
  {
    file.close();
    return false;
  }
  file.close();
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
  fs::path file_path = BRANCH_PATH / Branch;
  std::ofstream file(file_path, std::ios::app);

  if (!file.is_open())
    return false;

  // Write commit data
  file << "\n";
  file.write(reinterpret_cast<const char*>(Data.data()), Data.size());
  if (file.fail())     // Check, wite file bytes or no
  {
    file.close();
    return false;
  }
  file.close();
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
  // Folder path to branch
  fs::path folder_path = BRANCH_PATH;

  // Path aproximate
  fs::path file_path = folder_path / Branch;
  std::string BranchTmp = Branch + ".tmp";
  fs::path OutPath = file_path.parent_path() / BranchTmp;

  // File crating handle
  std::ofstream OutFile(OutPath);
  std::ifstream file(file_path);
  bool FirstEntry = false;

  if (!file.is_open())
    FirstEntry = true;
  if (!OutFile.is_open())
    return false;


  // Write new string to out file 
  OutFile.write(reinterpret_cast<const char*>(Data.data()), Data.size());
  if (OutFile.fail())
  {
    OutFile.close();
    file.close();
    return false;
  }

  // Skip 1 string and copy other data if main create before
  if (!FirstEntry)
  {
    std::string dummy;
    if (std::getline(file, dummy))
    {
      OutFile << "\n";
      OutFile << file.rdbuf();
    }
  }
  OutFile.close();
  if (!FirstEntry)
    file.close();

  fs::remove(file_path);
  fs::rename(OutPath, file_path);
  return true;
} /* End of 'core::filesystem::WriteBranch' function */

/* Function to write current branch name
 * ARGUMENTS:
 *   - Name of new current branch name:
 *       const std::string &NewName;
 * RETURNS: None.
 */
void core::filesystem::WriteCurrBranchName( std::string NewName )
{
  // WARNING: Curr branch saved non binary
  static fs::path Path = fs::current_path() / ".mygit" / "CurrentBranch";
  std::ofstream File(Path);

  if (!File.is_open())
    throw(std::runtime_error("File of current branch cant be opened"));
  File.write(NewName.data(), NewName.size());
  if (File.fail())     // Check, wite file bytes or no
  {
    File.close();
    throw(std::runtime_error("Branch name cant be writen"));
  }
  File.close();
} /* End of 'core::filesystem::WriteCurrBarnchName' function */

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
  fs::path PathFile(Path);
  fs::path Folder = PathFile.parent_path();

  fs::create_directories(Folder);
  if (!File.is_open()) // Try to oppen file
    return false;
  File.write(reinterpret_cast<const char *>(Data.data()), Data.size());
  if (File.fail())     // Check, wite file bytes or no
  {
    File.close();
    return false;
  }
  File.close();
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
    if (File.fail())     // Check, wite file bytes or no
    {
      File.close();
      throw std::runtime_error("Data cant be written");
    }
  }
}  /* End of 'core::filesystem::MakeFileSystem' function */

/* END OF 'filesystem_write.cpp' FILE */