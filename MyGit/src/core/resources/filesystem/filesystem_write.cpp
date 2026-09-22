/* FILE:        filesystem_write.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 22.09.2026
 * PURPOSE:     Git project.
 *              Filesystem write function module.
 */

#include "filesystem.h"

/* Function to write blob 
 * ARGUMENTS:
 *   - Hash of blob:
 *       crypto::hash Hash;
 *   - Data of blob:
 *       std::vector<uint8_t> Data;
 * RETURNS:
 *   (bool) Write success or no.
 */
bool core::filesystem::WriteBlob( crypto::hash Hash, std::vector<uint8_t> Data )
{
	static fs::path path = std::filesystem::current_path();  // Get dirrectory where we need .mygit
  fs::path folder_path = path / "objects" / "blobs" / Hash.GetStrHash().substr(0, 2);

	fs::create_directories(folder_path);
	fs::path file_path = folder_path / Hash.GetStrHash();
	std::ofstream file(file_path, std::ios::binary);

	if (!file.is_open())
	  return false;
	
	// If blob file created
	file.write(reinterpret_cast<const char*>(Data.data()), Data.size());
	return true;
} /* End of 'core::filesystem::WriteBlob' function */

/* Function to write tree 
 * ARGUMENTS:
 *   - Hash of tree:
 *       core::crypto::hash Hash;
 *   - Data of tree:
 *       std::vector<uint8_t> Data;
 * RETURNS:
 *   (bool) Write success or no.
 */
bool core::filesystem::WriteTree( core::crypto::hash Hash, std::vector<uint8_t> Data )
{
	static fs::path path = std::filesystem::current_path();  // Get dirrectory where we need .mygit
  fs::path folder_path = path / "objects" / "trees" / Hash.GetStrHash().substr(0, 2);

	fs::create_directories(folder_path);
	fs::path file_path = folder_path / Hash.GetStrHash();
	std::ofstream file(file_path, std::ios::binary);

	if (!file.is_open())
	  return false;
	
	// If tree file created
	file.write(reinterpret_cast<const char*>(Data.data()), Data.size());
	return true;
} /* End of 'core::filesystem::WriteTree' function */

/* Function to write commit 
 * ARGUMENTS:
 *   - Name of branch:
 *       std::string Branch;
 *   - Data of commit:
 *       std::vector<uint8_t> Data;
 * RETURNS:
 *   (bool) Write success or no.
 */
bool core::filesystem::WriteCommit( std::string Branch, std::vector<uint8_t> Data )
{
	static fs::path path = std::filesystem::current_path();  // Get dirrectory where we need .mygit
  fs::path folder_path = path / "branches";

	fs::create_directories(folder_path);
	fs::path file_path = folder_path / Branch;
	std::ofstream file(file_path, std::ios::out | std::ios::app | std::ios::binary);

	if (!file.is_open())
	  return false;
	
	// Write commit data
	file.write(reinterpret_cast<const char*>(Data.data()), Data.size());
	return true;
} /* End of 'core::filesystem::WriteCommit' function */

/* Function to write branch 
 * ARGUMENTS:
 *   - Name of branch:
 *       std::string Branch;
 *   - Data of branch:
 *       std::vector<uint8_t> Data;
 * RETURNS:
 *   (bool) Write success or no.
 */
bool core::filesystem::WriteBranch( std::string Branch, std::vector<uint8_t> Data )
{
	static fs::path path = std::filesystem::current_path();  // Get dirrectory where we need .mygit
  fs::path folder_path = path / "branches";

	fs::create_directories(folder_path);
	fs::path file_path = folder_path / Branch;
	std::ofstream file(file_path, std::ios::binary);

	if (!file.is_open())
	  return false;
	
	// If blob file created
	file.write(reinterpret_cast<const char*>(Data.data()), Data.size());
	return true;
} /* End of 'core::filesystem::WriteBranch' function */

/* END OF 'filesystem_write.cpp' FILE */