/* FILE:        mygit_log.cpp
 * AUTHOR:      Ngbs
 * LAST UPDATE: 21.10.2026
 * PURPOSE:     Git project.
 *              Mygit log function.
 */

#include "executor.h"
#include "regs/registrator.h"
#include "regs/function_pool.h"

/* Log mygit function 
 * ARGUMENTS:
 * RETURNS: None.
 */
void Log( std::string Path )
{
  std::filesystem::path CurrPath(Path);
  std::string fn;

  CurrPath = CurrPath / ".mygit" / "branches";
  for (const auto &entry: std::filesystem::directory_iterator(CurrPath))
  {
    fn = entry.path().filename().string();
    std::cout << fn << std::endl;
  }
} /* End of 'Log' function */

/*** ADAPTER TO FUNCTION ***/

/* Adapter to log function 
 * ARGUMENTS:
 *   - Vector of arguments to function:
 *       std::vector<ArgumentValue> Args;
 * RETURNS: None.
 */
static void Adapter( std::vector<ArgumentValue> Args )
{
  auto Path = std::get<std::string>(Args[0]);

  Log(Path);
} /* End of 'Adapter' function */


REGISTRATION_FUNCTION("log", Log, (std::vector<argument> {{"Path", ArgumentType::String, true}}), Adapter)

/* END OF 'mygit_log.cpp' FILE */
