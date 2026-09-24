/* FILE:        blob.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 24.09.2026
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
    utils::IsFileBin(Bytes);
  }
  catch (const std::runtime_error &Err)
  {
    std::cout << Err.what() << "-> Blob is not created " << std::endl;
  }
} /* End of 'core::resources::blob::blob' function */

/* Function to apply blob to file
 * ARGUMENTS:
 *   - Path to file:
 *       std::string Path;
 * RETURNS: None.
 */
void core::resources::blob::Apply( std::string Path )
{
  
} /* End of 'core::resources::blob::Apply' function */

/* END OF 'blob.cpp' FILE */