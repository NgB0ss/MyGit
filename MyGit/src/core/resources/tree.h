/* FILE:        tree.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 27.09.2026
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
    enum class TreeCtor
    {
      Default, 
      BySystem
    };
    // Tree resource class
    class tree
    {
    private:
      std::map<std::string, crypto::hash> FileSystemState; // Map of filesyste, state
      /* IN DEFAULT GIT:
       *   - Dirrectories in def git also have hashes, to optimiztion time, for commited big projects e.t.c
       *     But I have so many time and do it like def map, 
       *     maybe I change it after end core and write first executor functions
       */
    public:
      /* Default ctro of tree */
      tree( void ) = default;

      /* Default ctor of tree resource
       * ARGUMENTS: 
       *   - Type ctor that you need:
       *       TreeCtor Type;
       */
      tree( TreeCtor Type );

      /* Function to bild data from tree 
       * ARGUMENTS:
       *   - Data:
       *       std::vector<uint8_t> Data;
       */
      tree( std::vector<uint8_t> Data );

      /* Function to apply tree to filesystem
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      void Apply( void );


      /* Function that create version by path and tree data
       * ARGUMENTS:
       *    - Path where version need to be:
       *       std::string Path;
       * RETURNS: None.
       */
      void MakeVersByTree( std::string Path );

      /* Function to bild data from tree class 
       * ARGUMENTS: None.
       * RETURNS: 
       *   (std::vector<uint8_t>)  Data that build from tree.
       */
      std::vector<uint8_t> DataFromTree( void );
    }; /* End of 'tree' class */
  }  /* end of 'resources' namespace */
} /* end of 'core' namespace */

#endif /* __tree_h_ */

/* END OF 'tree.h' FILE */