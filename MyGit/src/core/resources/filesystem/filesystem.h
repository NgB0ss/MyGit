/* FILE:        filesystem.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 13.09.2026
 * PURPOSE:     Git project.
 *              Filesystem main file - physic save resources
 */

#ifndef __filesystem_h_
#define __filesystem_h_

#include "crypto/cryptography.h"

namespace core
{
	// Redefinition filesystem namespace
	namespace fs = std::filesystem;

	namespace filesystem
	{
		struct FileState
		{
			fs::file_time_type LastWrite;   // Time when file was remaked
			uintmax_t Size;                 // Size of file
			bool IsFileBin;                 // File is binary or not
			crypto::hash Hash;              // Hash of file with flag i there binary (like blob hash)
		}; /* End of 'FileState' struct */

		// File system state struct 
		struct FileSystemState
		{
			std::map<std::string, FileState> FSState;  // Filesystem state map
		}; /* End of 'FileSystemState' struct */

		/******** FILESYSTEM ********/
		/* Function to make filesystem by resource
		 * ARGUMENTS: 
		 *   - Filesystem that need to be:
		 *       const FileSystemState &FSStt;
		 * RETURNS: None.
		 */
		void MakeFileSystem( const FileSystemState &FSStt );

		/* Function to read filesystem state
		 * ARGUMENTS: None.
		 * RETURNS:
		 *   (FileSystemState) Current filesystem state;
		 */
		FileSystemState ReadFileSystem( void );

		/******** FILES ********/
		/* Function to read file data
		 * ARGUMENTS:
		 *   - Path to file what need to be read:
		 *       const std::string &Path;
		 * RETURNS: 
		 *   (std::vector<uint8_t>) Data of readed file
		 * 
		 */
		std::vector<uint8_t> ReadFileData( const std::string &Path );

		/* Function to write file data
		 * ARGUMENTS:
		 *   - Path to file what need to be write:
		 *       const std::string &Path;
		 *   - Is file binary:
		 *       const bool &IsBin;
		 *   - Data to be writed:
		 *       const std::vector<uint8_t> &Data;
		 * RETURNS: 
		 * 	 (bool) Operation success or no.
		 */
		bool WriteFileData( const std::string &Path, const bool &IsBin, const std::vector<uint8_t> &Data );

		/********   BLOB    ********/
    /* Function to write blob 
		 * ARGUMENTS:
		 *   - Hash of blob:
		 *       const crypto::hash &Hash;
		 *   - Data of blob:
		 *       const std::vector<uint8_t> &Data;
		 * RETURNS:
		 *   (bool) Write success or no.
		 */
		bool WriteBlob( const crypto::hash &Hash, const std::vector<uint8_t> &Data );

		/* Function to read blob
		 * ARGUMENTS:
		 *   - Hash of blob what need be reed:
		 *       const crypto:hash &Hash;
		 * RETURNS:
		 *  (std::vector<uint8_t>) Data of blob.
		 */
		std::vector<uint8_t> ReadBlob( const crypto::hash &Hash );

		/********   TREE    ********/
		/* Function to write tree 
		 * ARGUMENTS:
		 *   - Hash of tree:
		 *       const core::crypto::hash &Hash;
		 *   - Data of tree:
		 *       const std::vector<uint8_t> &Data;
		 * RETURNS:
		 *   (bool) Write success or no.
		 */
		bool WriteTree( const core::crypto::hash &Hash, const std::vector<uint8_t> &Data );

		/* Function to read tree
		 * ARGUMENTS:
		 *   - Hash of tree what need be reed:
		 *       const crypto:hash &Hash;
		 * RETURNS:
		 *  (std::vector<uint8_t>) Data of tree.
		 */
		std::vector<uint8_t> ReadTree( const crypto::hash &Hash );

		/*******   COMMIT    *******/
		/* Function to write commit 
		 * ARGUMENTS:
		 *   - Name of branch:
		 *       const std::string &Branch;
		 *   - Data of commit:
		 *       const std::vector<uint8_t> &Data;
		 * RETURNS:
		 *   (bool) Write success or no.
		 */
		bool WriteCommit( const std::string &Branch, const std::vector<uint8_t> &Data );

		/* Function to read commit
		 * ARGUMENTS:
		 *   - Name of branch:
		 *       const std::string &Branch;
		 *   - Hash of commit what need be reed:
		 *       const crypto:hash &Hash;
		 * RETURNS:
		 *  (std::vector<uint8_t>) Data of commit.
		 */
		std::vector<uint8_t> ReadCommit( const std::string &Branch, const crypto::hash &Hash );

		/*******   BRANCH    *******/
		/* Function to write branch 
		 * ARGUMENTS:
		 *   - Name of branch:
		 *       const std::string &Branch;
		 *   - Data of branch:
		 *       const std::vector<uint8_t> &Data;
		 * RETURNS:
		 *   (bool) Write success or no.
		 */
		bool WriteBranch( const std::string &Branch, const std::vector<uint8_t> &Data );

		/* Function to read branch
		 * ARGUMENTS:
		 *   - Name of branch:
		 *       const std::string &Branch;
		 * RETURNS:
		 *  (std::vector<uint8_t>) Data of branch.
		 */
		std::vector<uint8_t> ReadBranch( const std::string &Branch );
	}	/* end of 'filesystem' namespace */
} /* end of 'core' namespace */

#endif /* __filesystem_h_ */

/* END OF 'filesystem.h' FILE */