/* FILE:        blob.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 18.10.2026
 * PURPOSE:     Git project.
 *              Resources header file - blob.
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
      std::vector<uint8_t> Bytes;   // File data in bytes
    public:

      /* Ctor blob by file path 
       * ARGUMENTS:
       *   - File path:
       *       std::string Path;
       */
      blob( const std::string &Path );

      /* Ctor blob by data, that read from blobs (physic)
       * ARGUMENTS:
       *   - Data that must be blob:
       *       std::vector<uint8_t> Data;
       */
      blob( std::vector<uint8_t> Data );

      /* FUnction that create file by path and blob data
       * ARGUMENTS:
       *    - Path where file need to be:
       *       std::string Path;
       * RETURNS: None.
       */
      void MakeFileByBlob( const std::string &Path ) const;

      /* Function that convert blob to data
       * ARGUMENTS: None.
       * RETURNS:
       *   (std::vector<unit8_t>) Data that was blob.
       */
      std::vector<uint8_t> ToData( void ) const;
    }; /* End of 'blob' class */
  } /* end of 'resources' namespace */
} /* end of 'core' namespace */

#endif /* __blob_h_ */

/* END OF 'blob.h' FILE */