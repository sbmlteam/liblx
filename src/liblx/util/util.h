/*
 * util.h
 *
 *  Created on: 27 October 2020
 *      Author: Timothy Spain
 */

#ifndef UTIL_H
#define UTIL_H

#include <ctype.h>
#include <cstddef>

#include <liblx/common/extern.h>


LIBLX_CPP_NAMESPACE_BEGIN

BEGIN_C_DECLS


LIBLAX_EXTERN
char* 
safe_strdup(const char* s);


LIBLAX_EXTERN
unsigned int 
streq (const char *s, const char *t);

END_C_DECLS

LIBLX_CPP_NAMESPACE_END
#endif /*ndef UTIL_H */
