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
	static fs::path Path = fs::current_path();
	fs::path FilePath = Path / "objects" / "trees" / Hash.GetStrHash();
	std::ifstream File(FilePath, std::ios::in | std::ios::binary | std::ios::ate );

	if (!File.is_open())
	{
		std::string message = "File of tree is not find" + Hash.GetStrHash();
		throw std::runtime_error(message);
	}

	// If file was open
	std::streamsize Size = File.tellg();
	File.seekg(0, std::ios::beg);
	std::vector<uint8_t> Data(Size);
	File.read(reinterpret_cast<char *>(Data.data()), Size);
	return Data;
} /* End of 'core::filesystem::ReadTree' function */

/* Function to read commit
 * ARGUMENTS:
 *   - Name of branch:
 *       std::string Branch;
 *   - Hash of commit what need be reed:
 *       crypto:hash Hash;
 * RETURNS:
 *  (std::vector<uint8_t>) Data of commit.
 */
std::vector<uint8_t> core::filesystem::ReadCommit( std::string Branch, crypto::hash Hash )
{
	static fs::path Path = fs::current_path();
	fs::path FilePath = Path / "branches" / Branch / ".brnch";
	std::ifstream File(FilePath, std::ios::in | std::ios::binary);

	if (!File.is_open())
	{
		std::string message = "File of commit is not find" + Branch;
		throw std::runtime_error(message);
	}

	// Find commit
	std::string CurrHash(BYTES_HASH, '\0');

	File.read(&CurrHash[0], BYTES_HASH);
  while (CurrHash != Hash.GetStrHash())
	{
		File.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		File.read(&CurrHash[0], BYTES_HASH);
	}
	// Read data of commit
	std::string DataStr;
	std::getline(File, DataStr);

	std::vector<uint8_t> Data(DataStr.size());

	for (int i = 0; i < DataStr.size(); i++)
		Data.push_back(DataStr[i]);

	return Data;
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
	static fs::path Path = fs::current_path();
	fs::path FilePath = Path / "branches" / Branch;
	std::ifstream File(FilePath, std::ios::in | std::ios::binary);

	// Open file
	if (!File.is_open())
	{
		std::string message = "File of branch is not find" + Branch;
		throw std::runtime_error(message);
	}

	// Get hash of branch
	std::string HashBranch;
	std::getline(File, HashBranch);
	
	// Get end of file and read hash of last commit 
	/* NEED TO DO */
} /* End of 'core::filesystem::ReadBranch' function */

/* END OF 'filesystem_read.cpp' FILE */