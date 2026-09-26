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
		private:
			// One of nodes in tree
			struct Node
			{
				std::map<std::string, Node> Childrens; // Childrens of that node

				bool IsDirrectory;										 //	Is that node have blob 
				crypto::hash BlobHash;								 // Blob hash if that not dirrectory
			}; /* End of 'Node' struct */
			
			Node *Root = nullptr; // Main root of tree
		public:

			/* Default ctor of tree resource
			 * ARGUMENTS: None.
			 */
			tree( void );

			/* Function to bild data from tree 
			 * ARGUMENTS:
			 *   - Data:
			 *       std::vector<uint8_t> Data;
			 */
			tree( std::vector<uint8_t> Data );

			/* Function to apply tree to filesystem
			 * ARGUMENTS:
			 *   - Path to file:
			 *       std::string Path;
			 * RETURNS: None.
			 */
			void Apply( std::string Path );

			/* Function that create version by path and tree data
			 * ARGUMENTS:
			 * 	 - Path where version need to be:
			 *       std::string Path;
			 * RETURNS: None.
			 */
			void MakeVersByTree( std::string Path );

			/* Function to bild data from tree class 
			 * ARGUMENTS: None.
			 * RETURNS: 
			 *   (std::vector<uint8_t>)	Data that build from tree.
			 */
			std::vector<uint8_t> DataFromTree( void );
		}; /* End of 'tree' class */
	}	/* end of 'resources' namespace */
} /* end of 'core' namespace */

#endif /* __tree_h_ */

/* END OF 'tree.h' FILE */