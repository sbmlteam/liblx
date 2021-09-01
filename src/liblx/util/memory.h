/*
 * memory.h
 *
 *  Created on: 27 October 2020
 *      Author: Timothy Spain
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <ctype.h>
#include <cstddef>

#include <liblx/common/extern.h>


LIBLX_CPP_NAMESPACE_BEGIN

BEGIN_C_DECLS


LIBLAX_EXTERN
void* 
safe_malloc (size_t size);


LIBLAX_EXTERN
void
safe_free(void * element);

END_C_DECLS

LIBLX_CPP_NAMESPACE_END
#endif /*ndef MEMORY_H */
