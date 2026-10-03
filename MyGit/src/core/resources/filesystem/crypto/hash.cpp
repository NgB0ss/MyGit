/* FILE:        hash.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 26.09.2026
 * PURPOSE:     Git project.
 *              Cryptography - hash system.
 */

#include "cryptography.h"

/* Function to aproximate hash to every byte subsequence
 * ARGUMENTS:
 *   - Byte vector:
 *       const std::vector<uint8_t> &BytesData;
 */
core::crypto::hash::hash( const std::vector<uint8_t> &BytesData )
{
  unsigned int HashLen = 0;
  std::unique_ptr<EVP_MD_CTX, void(*)(EVP_MD_CTX*)> mdctx(EVP_MD_CTX_new(), EVP_MD_CTX_free);

  // Check by is be context of hash maker or no
  if (!mdctx)
    throw std::runtime_error("Cant crate EVP_MD_CTX");

   // Initializing hash maker by algorithm sha-256
   if (EVP_DigestInit_ex(mdctx.get(), EVP_sha256(), nullptr) != 1)
     throw std::runtime_error("Error initializing SHA-256");

   // Send bytes to hash ctor
   if (EVP_DigestUpdate(mdctx.get(), BytesData.data(), BytesData.size()) != 1)
     throw std::runtime_error("Error send to hash data");

   // Write data of hash to hash class
   if (EVP_DigestFinal_ex(mdctx.get(), Bytes.data(), &HashLen) != 1)
        throw std::runtime_error("Error finalize hash");
} /* End of 'core::crypto::hash::hash' function */

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
std::array<uint8_t, BYTES_HASH> core::crypto::hash::GetHash( void )  const
{
  return Bytes;
}  /* End of 'core::crypto::hash::GetHash' function */

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
}  /* End of 'core::crypto::hash::SetHash' function */

/* END OF 'hash.cpp' FILE */