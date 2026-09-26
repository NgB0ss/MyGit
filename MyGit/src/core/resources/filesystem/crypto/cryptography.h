/* FILE:        cryptography.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 24.09.2026
 * PURPOSE:     Git project.
 *              Cryptography consalidator module.
 */

#ifndef __cryptography_h_
#define __cryptography_h_

#include "def.h"
#include <openssl/evp.h>

#define BYTES_HASH 32

// Main core namespace
namespace core
{
	// Cryptography namespace 
	namespace crypto
	{
		class hash
		{
		private:
			bool IsStrinCalc = false;                // Flag is string calculated

			std::string HashInString;	               // Hash in string
			std::array<uint8_t, BYTES_HASH> Bytes;   // Hash bytes
		public:
      
			/* Default class consructor
			 * ARGUMENTS: None.
			 * RETURNS: None.
			 */
			hash( void ) = default;

			/* Function to aproximate hash to every byte subsequence
			 * ARGUMENTS:
			 *   - Byte vector:
			 *       const std::vector<uint8_t> &BytesData;
			 */
			hash( const std::vector<uint8_t> &BytesData );

			/* Function to make from string - hash
			 * ARGUMENTS:
			 *   - String data:
			 *       std::string DataStr;
			 * RETURNS: 
			 *   (hash) Total hash.
			 */
			static hash FromStrToHash( std::string DataStr );

			/* Get string from hash class
			 * ARGUMENTS: None.
			 * RETURNS:
			 *   (std::array<uint8_t, BYTES_HASH>) Hash.
			 */
			std::array<uint8_t, BYTES_HASH> GetHash( void ) const;

			/* Get string from hash class
			 * ARGUMENTS: 
			 *   - Hash data to set:
			 *       std::array<uint8_t, 32> Data;
			 * RETURNS:
			 *   (uint8_t *) Hash.
			 */
			void SetHash( std::array<uint8_t, BYTES_HASH> Data );

			/* Get string from hash class
			 * ARGUMENTS: None.
			 * RETURNS:
			 *   (std::string) Hash in string.
			 */
			std::string GetStrHash( void ) const;
		}; /* End of 'hash' class */
	} /* end of 'crypto' namespace */
} /* end of 'core' namespace */

#endif /* __cryptography_h_ */

/* END OF 'cryptography.h' FILE */