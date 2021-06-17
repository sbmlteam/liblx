/*
 * sbmlMemoryStubs.cpp
 *
 *  Created on: 23 October 2020
 *      Author: Timothy Spain
 */

#include "sbmlMemoryStubs.h"

#include <cstring>
#include <cstdlib>
#include <string>

char* safe_strdup(const char* s)
{
	  size_t  size;
	  char   *duplicate;

	  if (s == NULL) return NULL;

	  size      = strlen(s) + 1;
	  duplicate = (char *) safe_malloc(size * sizeof(char));


	  strncpy(duplicate, s, size);

	  return duplicate;

}

void* safe_malloc (size_t size)
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

/*std::list<SBMLNamespaces> SBMLNamespaces::getSupportedNamespaces()
{
	return std::list<SBMLNamespaces>();
}

void SBMLNamespaces::freeSBMLNamespaces(std::list<SBMLNamespaces> nmsp)
{
	// The goggles
}

std::string SBMLNamespaces::getURI()
{
	return std::string("");
}

SBMLNamespaces* SBMLNamespaces::clone() const {
	return new SBMLNamespaces(*this);
}
*/
/*
const char*
getLibSBMLDottedVersion ()
{
	return LIBLX_DOTTED_VERSION;
}
*/
