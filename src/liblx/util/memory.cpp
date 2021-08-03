/*
 * sbmlStubs.cpp
 *
 *  Created on: 23 October 2020
 *      Author: Timothy Spain
 */

#include "memory.h"

#include <cstring>
#include <cstdlib>
#include <string>

LIBLX_CPP_NAMESPACE_BEGIN


LIBLAX_EXTERN
void* 
safe_malloc (size_t size)
{
	  void *p = (void *) malloc(size);


	  if (p == NULL)
	  {
	#ifdef EXIT_ON_ERROR
	    fprintf(stderr, MSG_OUT_OF_MEMORY);
	    exit(-1);
	#endif
	  }

	  return p;

}


LIBLAX_EXTERN
void
safe_free(void * element)
{
  if (!element)
    return;

  free(element);
  element = NULL;
}

LIBLX_CPP_NAMESPACE_END

