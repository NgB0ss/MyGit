/* FILE:        mygit.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 13.09.2026
 * PURPOSE:     Git project
 *              Core coordinator module
 *              Class of coordinator
 */

#ifndef __mygit_h_
#define __mygit_h_

#include "resources/resources.h"

namespace core
{
	// Main coordinator class
	class mygit // : public parser
	{
	private:
		std::string Path;
	public:
		/* Ctor of class
		 * ARGUMENTS:
		 *   - How many arguments from cmd:
		 *       int argc;
		 *   - Array of strings from cmd (arguments):
		 *       char* argv[];
		 */
		mygit( int argc, char* argv[] )
		{
		} /* End of 'mygit' function */
	}; /* End of 'mygit' class */
} /* end of 'core' namespace */

#endif /* __mygit_h_ */

/* END OF 'mygit.h' FILE */