/* FILE:        utils.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 24.09.2026
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
} /* end of 'utils' namespace */

#endif /* __utils_h_ */