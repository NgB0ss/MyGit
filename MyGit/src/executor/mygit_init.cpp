/* FILE:        mygit_init.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 13.09.2026
 * PURPOSE:     Git project
 *              Mygit init function 
 */

#include "executor.h"
#include "regs/registrator.h"
#include "regs/function_pool.h"


/* Init mygit function 
 * ARGUMENTS:
 * RETURNS: None.
 */
void Init( std::string Path )
{
  std::filesystem::path CurrPath(Path);
  
  // Create all need dirrectories
  CurrPath = CurrPath / ".mygit";
  std::filesystem::create_directories(CurrPath);
  CurrPath = CurrPath / "objects" / "trees";
  std::filesystem::create_directories(CurrPath);
  CurrPath = CurrPath.parent_path() / "blobs";
  std::filesystem::create_directories(CurrPath);
  CurrPath = CurrPath.parent_path().parent_path() / "branches";
  std::filesystem::create_directories(CurrPath);
  CurrPath = CurrPath.parent_path() / "CurrentBranch";
  std::ofstream File(CurrPath);

  if (!File.is_open())
    throw(std::runtime_error("File of current branch cant be openned"));
  File.write("main", 4);
} /* End of 'Init' function */

/*** ADAPTER TO FUNCTION ***/

/* Adapter to init function 
 * ARGUMENTS:
 *   - Vector of arguments to function:
 *       - std::vector<ArgumentValue> Args;
 * RETURNS: None.
 */
static void Adapter( std::vector<ArgumentValue> Args )
{
  auto Path = std::get<std::string>(Args[0]);

  Init(Path);
} /* End of 'Adapter' function */


REGISTRATION_FUNCTION("init", Init, (std::vector<argument> {{"Path", ArgumentType::String, true}}), Adapter)
/* END OF 'mygit_init.cpp' FILE */