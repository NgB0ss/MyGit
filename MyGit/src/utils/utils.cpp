/* FILE:        utils.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 26.09.2026
 * PURPOSE:     Git project.
 *              Utils executor file.
 */

#include "utils.h"

/* Function to check is file binary or no
 * ARGUMENTS: 
 *   - Bytes of file:
 *       const std::vector<uint8_t> &DataFile;
 * RETURNS: 
 *   (bool) Is file binary or no.
 */
bool utils::IsFileBin( const std::vector<uint8_t> &DataFile )
{
  size_t Size = DataFile.size() > 8000 ? 8000 : DataFile.size();  // Set size of buffer
  std::string DataStr;

  DataStr.resize(Size);
  return DataStr.find('\0') != std::string::npos;
} /* End of 'IsFileBin' function */

/* END OF 'utils.cpp' FILE */
