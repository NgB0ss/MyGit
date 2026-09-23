/* FILE:        hash.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 19.09.2026
 * PURPOSE:     Git project.
 *              Cryptography - hash system.
 */

#include "cryptography.h"

/* Function to make from string - hash
 * ARGUMENTS:
 *   - String data:
 *       std::string DataStr;
 * RETURNS: 
 *   (hash) Total hash.
 */
core::crypto::hash core::crypto::hash::FromStrToHash( std::string DataStr )
{
	hash Data;

	if (DataStr.size() != BYTES_HASH)
		return hash();
	else
	{
		for (int i = 0; i < BYTES_HASH; i++)
			Data.Bytes[0] = DataStr[i];
		Data.HashInString = DataStr;
		Data.IsStrinCalc = true;
	}
  return Data;
} /* End of 'core::crypto::hash::FromStrToHash` fucntion */

/* Get string from hash class
 * ARGUMENTS: None.
 * RETURNS:
 *   (std::array<uint8_t, BYTES_HASH>) Hash.
 */
std::array<uint8_t, BYTES_HASH> core::crypto::hash::GetHash( void )	const
{
	return Bytes;
}	/* End of 'core::crypto::hash::GetHash' function */

/* Get string from hash class
 * ARGUMENTS: None.
 * RETURNS:
 *   (std::string) Hash in string.
 */
std::string core::crypto::hash::GetStrHash( void ) const 
{
	if (IsStrinCalc)
		return HashInString;
	else
		return std::string();
} /* End of 'core::crypto::hash::GetStrHash' function */

/* Get string from hash class
 * ARGUMENTS: 
 *   - Hash data to set:
 *       std::array<uint8_t, 32> Data;
 * RETURNS:
 *   (uint8_t *) Hash.
 */
void core::crypto::hash::SetHash( std::array<uint8_t, BYTES_HASH> Data )
{
  Bytes = Data;
}	/* End of 'core::crypto::hash::SetHash' function */

/* END OF 'hash.cpp' FILE */