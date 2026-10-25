/* FILE:        mygit_commit_log.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 24.10.2026
 * PURPOSE:     Git project
 *              Mygit commit log function
 */

#include "executor.h"
#include "regs/registrator.h"
#include "regs/function_pool.h"

/* Function output help
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void CommitLog( void )
{
  std::filesystem::path Path = std::filesystem::current_path();
  
  Path = Path / core::filesystem::BRANCH_PATH;
  core::resources::branch CurrBrnch = core::resources::branch::GetCurrentBranch();
  std::vector
    <std::pair<core::crypto::hash,
     std::vector<uint8_t>>
    > AllCommits = core::filesystem::ReadAllCommits(CurrBrnch.GetName());
  std::string CommitOutput;

  for (auto &[hash, bytes]: AllCommits)
  {
    CommitOutput.clear();
    // Earase bytes from 0 symbols
    auto it = std::find(bytes.begin(), bytes.end(), '\0');

    if (it != bytes.end())
      bytes.erase(it, bytes.end());
    bytes.shrink_to_fit();
    if (bytes.size() < BYTES_HASH * 2)
    {
      std::cout << "Error in readed commit data" << std::endl;
      return;
    }
    CommitOutput.resize(bytes.size() - 2 * BYTES_HASH);
    for (int count = 0, i = BYTES_HASH; i < bytes.size() - BYTES_HASH; i++)
      CommitOutput[count++] = bytes[i];
    std::cout << hash.string() << " " << CommitOutput << std::endl;
  }
} /* End of 'CommitLog' function */

/*** ADAPTER TO FUNCTION ***/

/* Adapter to choose branch function 
 * ARGUMENTS:
 *   - Vector of arguments to function:
 *       - std::vector<ArgumentValue> Args;
 * RETURNS: None.
 */
static void Adapter( std::vector<ArgumentValue> Args )
{
  CommitLog();
} /* End of 'Adapter' function */

REGISTRATION_FUNCTION("commit_log", CommitLog, (std::vector<argument> {}), Adapter)


/* END OF 'mygit_commit_log.cpp' FILE */