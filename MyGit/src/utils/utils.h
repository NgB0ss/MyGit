/* FILE:        utils.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 04.10.2026
 * PURPOSE:     Git project.
 *              Utilit consalidation header file.
 */

#ifndef __utils_h_
#define __utils_h_

// Include test consalidation file
#include "tests/test.h"

// Main utils namespace
namespace utils
{
  /* Function to check is file binary or no
   * ARGUMENTS: 
   *   - Bytes of file:
   *       const std::vector<uint8_t> &DataFile;
   * RETURNS: 
   *   (bool) Is file binary or no.
   */
  bool IsFileBin( const std::vector<uint8_t> &DataFile );

  /* Function to check is file binary or no
   * ARGUMENTS: 
   *   - Path to file to check is file binary:
   *       const std::string &Path;
   * RETURNS: 
   *   (bool) Is file binary or no.
   */
  bool IsFileBin( const std::string &Path );

  /* Function to parse string to time point
   * ARGUMENTS:
   *   - Time in string:
   *       const std::string &StrTime;
   * RETURNS: 
   *   (std::chrono::time_point<std::chrono::system_clock, std::chrono::minutes>) Time point.
   */
  std::chrono::time_point<std::chrono::system_clock, std::chrono::minutes> TimeFromStr( const std::string &StrTime );
} /* end of 'utils' namespace */

#endif /* __utils_h_ */