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
 *       const crypto:hash &Hash;
 * RETURNS:
 *  (std::vector<uint8_t>) Data of blob.
 */
std::vector<uint8_t> core::filesystem::ReadBlob( const crypto::hash &Hash )
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
 *       const crypto:hash &Hash;
 * RETURNS:
 *  (std::vector<uint8_t>) Data of tree.
 */
std::vector<uint8_t> core::filesystem::ReadTree( const crypto::hash &Hash )
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
 *       const std::string &Branch;
 *   - Hash of commit what need be reed:
 *       const crypto:hash &Hash;
 * RETURNS:
 *  (std::vector<uint8_t>) Data of commit.
 */
std::vector<uint8_t> core::filesystem::ReadCommit( const std::string &Branch, const crypto::hash &Hash )
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
		Data[i] = DataStr[i];

	return Data;
} /* End of 'core::filesystem::ReadCommit' function */

/* Function to read branch
 * ARGUMENTS:
 *   - Name of branch:
 *       const std::string &Branch;
 * RETURNS:
 *  (std::vector<uint8_t>) Data of branch.
 */
std::vector<uint8_t> core::filesystem::ReadBranch( const std::string &Branch )
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
	File.seekg(0, std::ios::end);
	std::streampos fileSize = File.tellg();

  if (fileSize == 0)
	{
		std::string message = "File is empty" + Branch;
		throw std::runtime_error(message);
	}

	std::streamoff lastLineStart = 0;
	for (std::streamoff offset = 2; offset <= fileSize; offset++)
	{
		File.seekg(-offset, std::ios::end);
		char ch;

		File.get(ch);
		if (ch == '\n')
		{
			lastLineStart = File.tellg(); 
      break;
		}
	}

	File.seekg(lastLineStart);
	std::string CommitHashStr;
	std::vector<uint8_t> Data(BYTES_HASH * 2);

	File.read(&CommitHashStr.data()[0], BYTES_HASH);

	// Write hash branch to data
  for (int i = 0; i < BYTES_HASH; i++)
		Data[i] = HashBranch[i];

	// Write hash last commit to data
	for (int i = BYTES_HASH; i < BYTES_HASH; i++)
		Data[i] = CommitHashStr[i - BYTES_HASH];
} /* End of 'core::filesystem::ReadBranch' function */

/* END OF 'filesystem_read.cpp' FILE */