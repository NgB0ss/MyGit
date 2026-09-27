/* FILE:        utils.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 28.09.2026
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
  int Size = DataFile.size() > 8000 ? 8000 : DataFile.size();  // Set size of buffer
  std::string DataStr;

  DataStr.resize(Size);
  return DataStr.find('\0') != std::string::npos;
} /* End of 'IsFileBin' function */

/* Function to check is file binary or no
 * ARGUMENTS: 
 *   - Path to file to check is file binary:
 *       const std::string &Path;
 * RETURNS: 
 *   (bool) Is file binary or no, also no if file not find.
 */
bool utils::IsFileBin( const std::string &Path )
{
  std::ifstream File(Path);

  if (!File.is_open())
    return false;

  std::string Data;

  Data.resize(8000);
  File.read(Data.data(), 8000);
  return Data.find('\0') != std::string::npos;
} /* End of 'IsFileBin' function */


/* END OF 'utils.cpp' FILE */
