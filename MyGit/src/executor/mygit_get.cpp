/* FILE:        mygit_get.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 25.10.2026
 * PURPOSE:     Git project.
 *              Mygit get version function. 
 */

#include "executor.h"
#include "regs/registrator.h"
#include "regs/function_pool.h"

/* Get mygit function 
 * ARGUMENTS:
 *   - Hash of commit that we need get:
 *       core::crypto::hash HashCommit;
 *   - Path where we need get this version (if path 0 -> apply version to this project):
 *       std::string Path; 
 * RETURNS: None.
 */
void Get( core::crypto::hash HashCommit, std::string Path = {} )
{
  core::resources::branch CurrBranch;
  core::resources::commit CommitVers;

  try
  {
    CurrBranch = core::resources::branch::GetCurrentBranch();
    CommitVers = core::resources::commit(core::filesystem::ReadCommit(CurrBranch.GetName(), HashCommit));
  }
  catch ( const std::runtime_error &Err )
  {
    std::cout << Err.what() << std::endl;
    return;
  }
  CommitVers.ApplyVersion(Path);
} /* End of 'Get' function */

/*** ADAPTER TO FUNCTION ***/

/* Adapter to log function 
 * ARGUMENTS:
 *   - Vector of arguments to function:
 *       std::vector<ArgumentValue> Args;
 * RETURNS: None.
 */
static void Adapter( std::vector<ArgumentValue> Args )
{
  auto HashCommit = std::get<core::crypto::hash>(Args[0]);

  Get(HashCommit);
} /* End of 'Adapter' function */


REGISTRATION_FUNCTION("get",                                        \
                      Get,                                          \
                      (std::vector<argument> {                      \
                        {"HashCommit", ArgumentType::Hash, true},   \
                        {"Path", ArgumentType::String, false}       \
                      }), Adapter)

/* END OF 'mygit_get.cpp' FILE */