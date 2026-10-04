/* FILE:        utils.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 04.10.2026
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

/* Function to parse string to time point
 * ARGUMENTS:
 *   - Time in string:
 *       const std::string &StrTime;
 * RETURNS: 
 *   (std::chrono::time_point<std::chrono::system_clock, std::chrono::minutes>) Time point.
 */
std::chrono::time_point<std::chrono::system_clock, std::chrono::minutes> utils::TimeFromStr( const std::string &StrTime )
{
  std::chrono::time_point<std::chrono::system_clock, std::chrono::minutes> TimePoint;
  std::istringstream ss{StrTime};

  ss >> std::chrono::parse("%F %R", TimePoint);
  if (ss.fail())
    throw(std::runtime_error("Error in parsed time of commit"));
  return TimePoint;
} /* End of 'utils::TimeFromStr' function */


/* END OF 'utils.cpp' FILE */
