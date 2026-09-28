/* FILE:        blob.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 26.09.2026
 * PURPOSE:     Git project.
 *              Resources - blob executor file
 */

#include "blob.h"

/* Ctor blob by file path 
 * ARGUMENTS:
 *   - File path:
 *       std::string Path;
 */
core::resources::blob::blob( std::string Path )
{
  try
  {
    Bytes = filesystem::ReadFileData(Path);
  }
  catch (const std::runtime_error &Err)
  {
    std::cout << Err.what() << "-> Blob is not created " << std::endl;
  }
} /* End of 'core::resources::blob::blob' function */

/* Ctor blob by data, that read from blobs (physic)
 * ARGUMENTS:
 *   - Data that must be blob:
 *       std::vector<uint8_t> Data;
 */
core::resources::blob::blob( const std::vector<uint8_t> &Data )
{
  Bytes = Data;
  Bytes.pop_back();
} /* End of 'core::resources::blob::blob' function */

/* Function to apply blob to file
 * ARGUMENTS:
 *   - Path to file:
 *       std::string Path;
 * RETURNS: None.
 */
void core::resources::blob::Apply( std::string Path )
{
  try
  {
    filesystem::WriteFileData(Path, Bytes);
  }
  catch (const std::runtime_error &Err)
  {
    std::cout << Err.what() << "-> Blob is not applyed " << std::endl;
  }
} /* End of 'core::resources::blob::Apply' function */

/* Function that create file by path and blob data
 * ARGUMENTS:
 * 	 - Path where file need to be:
 *       std::string Path;
 * RETURNS: None.
 */
void core::resources::blob::MakeFileByBlob( std::string Path )
{
  std::filesystem::path PathToFile(Path);
  std::filesystem::path Folders = PathToFile.parent_path();

  // Create only dirrectories
  fs::create_directories(PathToFile);
  std::ofstream File(Path, std::ios::binary);

  if (!File.is_open())
  {
    std::runtime_error Err(Path);
    throw(Err);
  }
  File.write(reinterpret_cast<char *>(Bytes.data()), Bytes.size());
} /* End of 'core::resources::blob::MakeFileByBlob' function */

/* Function that convert blob to data
 * ARGUMENTS: None.
 * RETURNS:
 *   (std::vector<unit8_t>) Data that was blob.
 */
std::vector<uint8_t> core::resources::blob::DataFromBlob( void )
{
  std::vector<uint8_t> Data;

  Data = Bytes;
  return Data;
} /* End of 'core::resources::blob::DataFromBlob' function */

/* END OF 'blob.cpp' FILE */