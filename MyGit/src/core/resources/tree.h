/* FILE:        tree.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 26.09.2026
 * PURPOSE:     Git project.
 *              Resources header file - tree.
 */

#ifndef __tree_h_
#define __tree_h_

#include "blob.h"

// Core of mygit namespace
namespace core
{
	// Main resources namespace
	namespace resources
	{
		// Tree resource class
		class tree
		{
			// One of nodes in tree
			struct Node
			{
				std::map<std::string, Node> Childrens; // Childrens of that node

				bool IsDirrectory;										 //	Is that node have blob 
				crypto::hash BlobHash;								 // Blob hash if that not dirrectory
			}; /* End of 'Node' struct */
			
			Node *Root = nullptr; // Main root of tree
		}; /* End of 'tree' class */
	}	/* end of 'resources' namespace */
} /* end of 'core' namespace */

#endif /* __tree_h_ */

/* END OF 'tree.h' FILE */