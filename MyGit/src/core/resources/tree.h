/* FILE:        tree.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 28.10.2026
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
      std::map<std::string, crypto::hash> FileSystemState {}; // Map of filesyste, state
      /* IN DEFAULT GIT:
       *   - Dirrectories in def git also have hashes, to optimiztion time, for commited big projects e.t.c
       *     But I have so many time and do it like def map, 
       *     maybe I change it after end core and write first executor functions
       */
      
      /* Function to bild data from tree class 
       * ARGUMENTS: None.
       * RETURNS: 
       *   (std::vector<uint8_t>)  Data that build from tree.
       */
      std::vector<uint8_t> ToData( void ) const;
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

      /* Function that create version by path and tree data
       * ARGUMENTS:
       *    - Path where version need to be (path null -> that mean path - current path):
       *       std::string Path;
       * RETURNS: None.
       */
      void ApplyVersion( std::string Path = {} );

      /* Function to save tree
       * ARGUMENTS: None.
       * RETURNS: 
       *   (bool) Is save success or not.
       */
      bool Save( void ) const;

      /* Function to get hash by tree class
       * ARGUMENTS: 
       *   - const std::vector<uint8_t> &Data = {};
       * RETURNS: 
       *   (core::crypto::hash) Hash of tree.
       */
      crypto::hash GetHash( const std::vector<uint8_t> &Data = {} ) const;

      /* Function to check is tree empty or no
       * ARGUMENTS: None.
       * RETURNS: 
       *   (bool) Is Empty or not.
       */
      bool IsEmpty( void ) const;
    }; /* End of 'tree' class */
  }  /* end of 'resources' namespace */
} /* end of 'core' namespace */

#endif /* __tree_h_ */

/* END OF 'tree.h' FILE */