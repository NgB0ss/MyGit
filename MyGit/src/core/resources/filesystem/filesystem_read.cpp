/* FILE:        filesystem_read.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 22.09.2026
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
	static fs::path Path = fs::current_path();
	fs::path FilePath = Path / "objects" / "blobs" / Hash.GetStrHash();
	std::ifstream File(FilePath, std::ios::in | std::ios::binary | std::ios::ate );

	if (!File.is_open())
	{
		std::string message = "File of blob is not find" + Hash.GetStrHash();
		throw std::runtime_error(message);
	}

	// If file was open
	std::streamsize Size = File.tellg();
	File.seekg(0, std::ios::beg);
	std::vector<uint8_t> Data(Size);
	File.read(reinterpret_cast<char *>(Data.data()), Size);
	return Data;
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