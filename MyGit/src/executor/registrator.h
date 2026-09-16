/* FILE:        registrator.h
 * AUTHOR:      Ngbs
 * LAST UPDATE: 16.09.2026
 * PURPOSE:     Git project
 *              Self-registrator of functions
 */

#ifndef __registrator_h_
#define __registrator_h_

// Main executor namespace
namespace executor_core
{
	// Self-registrator class
	class registrator
	{

	}; /* End of 'registrator' class */

	// Main macross to self-register function
  #define REGISTRATION_FUNCTION(f, arg) f + arg
} /* end of '' namspace */

#endif /* __registrator_h_ */

/* END OF 'registrator.h' FILE */