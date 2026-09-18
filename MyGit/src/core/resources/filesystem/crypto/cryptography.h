/* FILE:        cryptography.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 16.09.2026
 * PURPOSE:     Git project.
 *              Cryptography consalidator module.
 */

#ifndef __cryptography_h_
#define __cryptography_h_

#include "def.h"

// Main core namespace
namespace core
{
	// Cryptography namespace 
	namespace crypto
	{
		class hash
		{
		private:
		public:
			/* Function to make from string - hash
			 * ARGUMENTS:
			 *   - String data:
			 *       std::string DataStr;
			 * RETURNS: 
			 *   (hash) Total hash.
			 */
			static hash FromStrToHash( std::string DataStr )
			{
        return hash();
			} /* End of 'FromStrToHash' function */
		}; /* End of 'hash' class */
	} /* end of 'crypto' namespace */
} /* end of 'core' namespace */

#endif /* __cryptography_h_ */

/* END OF 'cryptography.h' FILE */