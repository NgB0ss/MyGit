/* FILE:        filesystem.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 30.10.2026
 * PURPOSE:     Git project.
 *              Filesystem main file - physic save resources
 */

#ifndef __filesystem_h_
#define __filesystem_h_

#include "crypto/cryptography.h"

// Max windows path without API
#define MAX_PATH 260

namespace core
{
  // Redefinition filesystem namespace
  namespace fs = std::filesystem;

  namespace filesystem
  {
    // HARDCODE PATH SAVE
    // Path of .mygit dirrectory
    inline const fs::path MYGIT_PATH = fs::current_path() / ".mygit";
    // Path of branches dirrectory in current .mygit
    inline const fs::path BRANCH_PATH = fs::current_path() / ".mygit" / "branches";
    // Path of blobs object dirrectory in current .mygit
    inline const fs::path BLOBS_OBJ_PATH = fs::current_path() / ".mygit" / "objects" / "blobs";
    // Path of trees object dirrectory in current .mygit
    inline const fs::path TREES_OBJ_PATH = fs::current_path() / ".mygit" / "objects" / "trees";
    // Path of local session of this user wndws
    inline const fs::path LOCAL_SESSION_PATH = utils::GetWindowPath(FOLDERID_LocalAppData) / "session.dat";
    // Path of user database on this PC
    inline const fs::path DATABASE_PATH = utils::GetWindowPath(FOLDERID_ProgramData) / "users.db";

    struct FileState
    {
      uintmax_t Size;         // Size of file
      crypto::hash Hash;      // Hash of file with flag i there binary (like blob hash)
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

    /* Function to celar current filesystem 
     * ARGUMENTS:
     *   - Path to clear filesystem:
     *       std::string Path;
     * RETURNS: 
     *   (bool) IsOkOrNo.
     */
    bool ClearFilesystem( std::string Path );

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
     *   - Data to be writed:
     *       const std::vector<uint8_t> &Data;
     * RETURNS: 
     *    (bool) Operation success or no.
     */
    bool WriteFileData( const std::string &Path, const std::vector<uint8_t> &Data );

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

    /* Read all commits funcion
     * ARGUMENTS:
     *   - Branch name from what we need read commits:
     *       const std::string &Branch;
     * RETURNS: 
     *   (std::vector<std::vector<uint8_t>>) Pait hash-commit bytes;
     */
    std::vector<std::vector<uint8_t>> ReadAllCommits( const std::string &Branch );

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

    /* Function to write current branch name
     * ARGUMENTS:
     *   - Name of new current branch name:
     *       const std::string &NewName;
     * RETURNS: None.
     */
    void WriteCurrBranchName( std::string NewName );

    /* Function to read branch
     * ARGUMENTS:
     *   - Name of branch:
     *       const std::string &Branch;
     * RETURNS:
     *  (std::vector<uint8_t>) Data of branch.
     */
    std::vector<uint8_t> ReadBranch( const std::string &Branch );

    /* Function to read name of current branch 
     * ARGUMENTS: None.
     * RETURNS:
     *   (std::string) Current branch.
     */
    std::string ReadCurrBranchName( void );

    /* Function to check saved branch before or no 
     * ARGUMENTS: 
     *   - Name of branch to need check:
     *       std::string NameBranch;
     * RETURNS:
     *   (bool) Is saved before or no.
     */
    bool IsBranchSavedBf( std::string NameBranch );

    /*******************************************
     *
     ** DATABASE AND AUTHORIZATION FUNCTIONS **
     *
     *******************************************/

    
    /* Function to write user to database
     * ARGUMENTS:
     *   - Bytes to write:
     *       std::vector<uint8_t> Bytes;
     * RETURNS:
     *   (bool) Is saved ok or not.
     */
    bool WriteUser( const std::vector<uint8_t> &Bytes );

    /* Function to read nickname of user
     * ARGUMENTS:
     *   - Nickname of user that need be read:
     *       const std::string &Nickname;
     * RETURNS: 
     *   (std::vector<uint8_t>) Bytes of user.
     */
    std::vector<uint8_t> ReadUser( const std::string &Nickname );
  }  /* end of 'filesystem' namespace */
} /* end of 'core' namespace */

#endif /* __filesystem_h_ */

/* END OF 'filesystem.h' FILE */