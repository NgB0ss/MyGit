/* FILE:        commit.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 29.09.2026
 * PURPOSE:     Git project.
 *              Resources - commit executor file
 */

#include "commit.h"

/* Ctor commit by byte data 
 * ARGUMENTS:
 *   - Data that readed from commit:
 *       std::vector<uint8_t> Data;
 */
core::resources::commit::commit( std::vector<uint8_t> Data )
{
} /* End of 'core::resources::commit::commit' fucntion */

/* Ctor by all data of resource
 * ARGUMENTS:
 *   - Hash of parrent commit:
 *       core::crypto::hash Parent;
 *   - Hash of tree filesystem state of commit:
 *       core::crypto::hash Tree;
 *   - Author of commit:
 *       std::string Author;
 *   - Message of commit:
 *       std::string Msg;
 */
core::resources::commit::commit( core::crypto::hash Parent,
												 core::crypto::hash Tree,
												 std::string Author,
												 std::string Msg)
{
} /* End of 'core::resources::commit::commit' function */

/* Function to apply commit version 
 * ARGUMENTS:
 *   - Hash commit that need by apply:
 *       core::crypto::hash	HashCommit;
 * RETURNS: None.
 */
void core::resources::commit::Apply( core::crypto::hash HashCommit )
{
} /* End of 'core::resources::commit::Apply' function */

/* Function to make version by commit and path where it need be
 * ARGUMENTS:
 *   - Path where we need version:
 *       std::string Path;
 *   - Hash of commit that need be applied:
 *       core::crypto::hash HashCommit;
 * RETURNS: None.
 */
void core::resources::commit::MakeVersionByCommit( std::string Path, core::crypto::hash HashCommit )
{
} /* End of 'core::resources::commit::MakeVersionByCommit' function */

/* Function to get data from commit 
 * ARGUMENTS: None.
 * RETURNS:
 *   (std::vector<uint8_t>) Data of commit in bytes.
 */
std::vector<uint8_t> core::resources::commit::DataFromCommit( void )
{
} /* End of 'core::resources::commit::DataFromCommit' function */

/* END OF 'commit.cpp' FILE */