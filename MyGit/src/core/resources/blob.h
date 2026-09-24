/* FILE:        blob.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 19.09.2026
 * PURPOSE:     Git project.
 *              Resources header file - blob
 */

#ifndef __blob_h_
#define __blob_h_

#include "def.h"
#include "filesystem/filesystem.h"

namespace core
{
	// Main resource namespace
	namespace resources
	{
		// Blob container class 
		class blob
		{
		private:
			bool IsFileBin = false;       // Flag by is file binary or no
			std::vector<uint8_t> Bytes;   // File data in bytes
		public:

			/* Ctor blob by file path 
			 * ARGUMENTS:
			 *   - File path:
			 *       std::string Path;
			 */
			blob( std::string Path );

			/* Function to apply blob to file
			 * ARGUMENTS:
			 *   - Path to file:
			 *       std::string Path;
			 * RETURNS: None.
			 */
			void Apply( std::string Path );
		}; /* End of 'blob' class */
	} /* end of 'resources' namespace */
} /* end of 'core' namespace */

#endif /* __blob_h_ */

/* END OF 'blob.h' FILE */