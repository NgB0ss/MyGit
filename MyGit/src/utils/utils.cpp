/* FILE:        utils.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 30.10.2026
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


/* Function to aproximate path ro localappdata/programmdata
 * ARGUMENTS:
 *   - Reference to folder ID in Windws:
 *       REFKNOWFOLDERID: rfolderid;
 * RETURNS:
 *   (std::filesystem::path) Path to folder that u need.
 */
std::filesystem::path utils::GetWindowPath( REFKNOWNFOLDERID rfolderid )
{
  PWSTR pszPath = nullptr; // Wide string where will be saved path
  // Function that malloc memory to var
  // and return result of opersation,
  // also, save path in var
  HRESULT hr = SHGetKnownFolderPath(rfolderid, 0, nullptr, &pszPath); 
  if (SUCCEEDED(hr)) 
  {
    std::filesystem::path result(pszPath);
    CoTaskMemFree(pszPath); // Clean memory
    return result;
  }
  return std::filesystem::path();
} /* End of 'utils::GetWindowPath' function */

/* Function to swap console mode to not echo
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void utils::DisableEchoInput( void )
{
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode = 0;

  // Get current mode
  GetConsoleMode(hStdin, &mode);
  // Disable echo
  SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
} /* End of 'utils::DisableEchoInput' function */

/* Function to swap console mode to echo
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void utils::EnableEchoInput( void )
{
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode = 0;

  GetConsoleMode(hStdin, &mode);
  SetConsoleMode(hStdin, mode | ENABLE_ECHO_INPUT);
} /* End of 'utils::EnableEchoInput' function */


/* END OF 'utils.cpp' FILE */
