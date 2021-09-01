/*
 * util.cpp
 *
 *  Created on: 23 October 2020
 *      Author: Timothy Spain
 */

#include "util.h"
#include "memory.h"

#include <cstring>
#include <cstdlib>
#include <string>

LIBLX_CPP_NAMESPACE_BEGIN


LIBLAX_EXTERN
char* 
safe_strdup(const char* s)
{
	  size_t  size;
	  char   *duplicate;

	  if (s == NULL) return NULL;

	  size      = strlen(s) + 1;
	  duplicate = (char *) safe_malloc(size * sizeof(char));


	  strncpy(duplicate, s, size);

	  return duplicate;

}



LIBLAX_EXTERN
unsigned int 
streq (const char *s, const char *t)
{
  if (s == NULL)
    return t == NULL;
  else if (t == NULL)
    return 0;
  else
    return !strcmp(s, t);
}


LIBLX_CPP_NAMESPACE_END

