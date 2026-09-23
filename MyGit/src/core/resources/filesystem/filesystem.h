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
		/********   BLOB    ********/
    /* Function to write blob 
		 * ARGUMENTS:
		 *   - Hash of blob:
		 *       crypto::hash Hash;
		 *   - Data of blob:
		 *       std::vector<uint8_t> Data;
		 * RETURNS:
		 *   (bool) Write success or no.
		 */
		bool WriteBlob( crypto::hash Hash, std::vector<uint8_t> Data );

		/* Function to read blob
		 * ARGUMENTS:
		 *   - Hash of blob what need be reed:
		 *       crypto:hash Hash;
		 * RETURNS:
		 *  (std::vector<uint8_t>) Data of blob.
		 */
		std::vector<uint8_t> ReadBlob( crypto::hash Hash );

		/********   TREE    ********/
		/* Function to write tree 
		 * ARGUMENTS:
		 *   - Hash of tree:
		 *       core::crypto::hash Hash;
		 *   - Data of tree:
		 *       std::vector<uint8_t> Data;
		 * RETURNS:
		 *   (bool) Write success or no.
		 */
		bool WriteTree( core::crypto::hash Hash, std::vector<uint8_t> Data );

		/* Function to read tree
		 * ARGUMENTS:
		 *   - Hash of tree what need be reed:
		 *       crypto:hash Hash;
		 * RETURNS:
		 *  (std::vector<uint8_t>) Data of tree.
		 */
		std::vector<uint8_t> ReadTree( crypto::hash Hash );

		/*******   COMMIT    *******/
		/* Function to write commit 
		 * ARGUMENTS:
		 *   - Name of branch:
		 *       std::string Branch;
		 *   - Data of commit:
		 *       std::vector<uint8_t> Data;
		 * RETURNS:
		 *   (bool) Write success or no.
		 */
		bool WriteCommit( std::string Branch, std::vector<uint8_t> Data );

		/* Function to read commit
		 * ARGUMENTS:
		 *   - Name of branch:
		 *       std::string Branch;
		 *   - Hash of commit what need be reed:
		 *       crypto:hash Hash;
		 * RETURNS:
		 *  (std::vector<uint8_t>) Data of commit.
		 */
		std::vector<uint8_t> ReadCommit( std::string Branch, crypto::hash Hash );

		/*******   BRANCH    *******/
		/* Function to write branch 
		 * ARGUMENTS:
		 *   - Name of branch:
		 *       std::string Branch;
		 *   - Data of branch:
		 *       std::vector<uint8_t> Data;
		 * RETURNS:
		 *   (bool) Write success or no.
		 */
		bool WriteBranch( std::string Branch, std::vector<uint8_t> Data );

		/* Function to read branch
		 * ARGUMENTS:
		 *   - Name of branch:
		 *       std::string Branch;
		 * RETURNS:
		 *  (std::vector<uint8_t>) Data of branch.
		 */
		std::vector<uint8_t> ReadBranch( std::string Branch );
	}	/* end of 'filesystem' namespace */
} /* end of 'core' namespace */

#endif /* __filesystem_h_ */

/* END OF 'filesystem.h' FILE */