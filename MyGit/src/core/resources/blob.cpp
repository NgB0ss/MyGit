/* FILE:        blob.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 26.10.2026
 * PURPOSE:     Git project.
 *              Resources - blob executor file
 */

#include "blob.h"

/* Ctor blob by file path 
 * ARGUMENTS:
 *   - File path:
 *       std::string Path;
 */
core::resources::blob::blob( const std::string &Path )
{
  Bytes = filesystem::ReadFileData(Path);
} /* End of 'core::resources::blob::blob' function */

/* Ctor blob by data, that read from blobs (physic)
 * ARGUMENTS:
 *   - Data that must be blob:
 *       std::vector<uint8_t> Data;
 */
core::resources::blob::blob( std::vector<uint8_t> Data )
{
  // Move ctors
  Bytes = std::move(Data);
} /* End of 'core::resources::blob::blob' function */

/* Function that create file by path and blob data
 * ARGUMENTS:
 *    - Path where file need to be:
 *       std::string Path;
 * RETURNS: None.
 */
void core::resources::blob::MakeFileByBlob( const std::string &Path ) const
{
  if (!filesystem::WriteFileData(Path, Bytes))
    throw std::runtime_error(Path + " File data cant be written");
} /* End of 'core::resources::blob::MakeFileByBlob' function */

/* Function that convert blob to data
 * ARGUMENTS: None.
 * RETURNS:
 *   (std::vector<unit8_t>) Data that was blob.
 */
std::vector<uint8_t> core::resources::blob::ToData( void ) const 
{
  return Bytes;
} /* End of 'core::resources::blob::ToData' function */

/* Function to save blob 
 * ARGUMENTS: None.
 * RETURNS: 
 *   (bool) Is save success or not.
 */
bool core::resources::blob::Save( void ) const
{
  return filesystem::WriteBlob(crypto::hash(Bytes), Bytes);
} /* End of 'core::resources::blob::Save' function */

/* Funtion to ge hash from blob
 * ARGUMENTS: None.
 * RETURNS:
 *   (core::crypto::hash) Hash of blob.
 */
core::crypto::hash core::resources::blob::GetHash( void ) const
{
  return crypto::hash(Bytes);
} /* End of 'core::resources::blob::GetHash' function */

/* END OF 'blob.cpp' FILE */