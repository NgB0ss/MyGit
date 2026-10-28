/* FILE:        mygit_commit.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 17.10.2026
 * PURPOSE:     Git project
 *              Mygit commit functions 
 */

#include "executor.h"
#include "regs/registrator.h"
#include "regs/function_pool.h"

/* Commit function of mygit
 * ARGUMENTS:
 *   - Argument of commit:
 *       std::string ArgCommit;
 *   - Message of commit:
 *       std::string Message;
 * RETURNS: None.
 */
void Commit( std::string ArgCommit, std::string Message )
{
  if (ArgCommit.find("-m") != -1)
  {
    core::resources::branch CurrBranch = core::resources::branch::GetCurrentBranch();
    core::resources::tree *CurrTreeBrnch = CurrBranch.GetTree();

    if (CurrTreeBrnch == nullptr)
    {
      std::cout << "No files in index" << std::endl;
      return;
    }
    core::crypto::hash HashTree = CurrTreeBrnch->GetHash();
    core::resources::commit CurrCommit =
      core::resources::commit(CurrBranch.GetLastCmmtHash(),
                              HashTree,
                              "Author", Message);
    if (!CurrCommit.Save(CurrBranch.GetName()))
      throw std::runtime_error("Commit cant be saved -> check rights of mygit\n");
    core::resources::tree EmptyQueue;

    CurrBranch.SetTree(EmptyQueue);
    CurrBranch.SetHashCurrCommit(CurrCommit);
    CurrBranch.Save();
  }
  else
    std::cout << "Not correct operator to commit -> see help" << std::endl;

} /* End of 'Commit' function */

/*** ADAPTER TO FUNCTION ***/

/* Adapter to add function 
 * ARGUMENTS:
 *   - Vector of arguments to function:
 *       - std::vector<ArgumentValue> Args;
 * RETURNS: None.
 */
static void Adapter( std::vector<ArgumentValue> Args )
{
  auto ArgCommit = std::get<std::string>(Args[0]);
  auto Message = std::get<std::string>(Args[1]);

  Commit(ArgCommit, Message);
} /* End of 'Adapter' function */

REGISTRATION_FUNCTION("commit", Commit,                                                      \
                      (std::vector<argument> {{"ArgCommit", ArgumentType::String, true},     \
                      {"Message", ArgumentType::String, true}}),                             \
                      Adapter)

/* END OF 'mtgit_commit.cpp' FILE */