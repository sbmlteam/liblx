/*
 * sbmlStubs.h
 *
 *  Created on: 27 October 2020
 *      Author: Timothy Spain
 */

#ifndef SBMLSTUBS_H
#define SBMLSTUBS_H

#include <ctype.h>
#include <cstddef>

#include <liblx/common/extern.h>

#include <liblx/common/extern.h>


LIBLX_CPP_NAMESPACE_BEGIN

BEGIN_C_DECLS


LIBLX_EXTERN
char* 
safe_strdup(const char* s);


LIBLX_EXTERN
void* 
safe_malloc (size_t size);


LIBLX_EXTERN
unsigned int 
streq (const char *s, const char *t);


LIBLX_EXTERN
void
safe_free(void * element);

END_C_DECLS

LIBLX_CPP_NAMESPACE_END
#endif /*ndef SBMLSTUBS_H */
