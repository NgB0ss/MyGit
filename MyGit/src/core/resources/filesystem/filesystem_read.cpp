/* FILE:        filesystem_read.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 19.09.2026
 * PURPOSE:     Git project.
 *              Filesystem read function module.
 */

#include "filesystem.h"

/* Function to read blob
 * ARGUMENTS:
 *   - Hash of blob what need be reed:
 *       crypto:hash Hash;
 * RETURNS:
 *  (std::vector<uint8_t>) Data of blob.
 */
std::vector<uint8_t> core::filesystem::ReadBlob( crypto::hash Hash )
{
} /* End of 'core::filesystem::ReadBlob' function */

/* Function to read tree
 * ARGUMENTS:
 *   - Hash of tree what need be reed:
 *       crypto:hash Hash;
 * RETURNS:
 *  (std::vector<uint8_t>) Data of tree.
 */
std::vector<uint8_t> core::filesystem::ReadTree( crypto::hash Hash )
{
} /* End of 'core::filesystem::ReadTree' function */

/* Function to read commit
 * ARGUMENTS:
 *   - Hash of commit what need be reed:
 *       crypto:hash Hash;
 * RETURNS:
 *  (std::vector<uint8_t>) Data of commit.
 */
std::vector<uint8_t> core::filesystem::ReadCommit( crypto::hash Hash )
{
} /* End of 'core::filesystem::ReadCommit' function */

/* Function to read branch
 * ARGUMENTS:
 *   - Name of branch:
 *       std::string Branch;
 * RETURNS:
 *  (std::vector<uint8_t>) Data of branch.
 */
std::vector<uint8_t> core::filesystem::ReadBranch( std::string Branch )
{
} /* End of 'core::filesystem::ReadBranch' function */

/* END OF 'filesystem_read.cpp' FILE */