/*
 * sbmlMemoryStubs.h
 *
 *  Created on: 27 October 2020
 *      Author: Timothy Spain
 */

#ifndef SBMLMEMORYSTUBS_H
#define SBMLMEMORYSTUBS_H

#include <ctype.h>
#include <cstddef>

extern "C"
char* safe_strdup(const char* s);
extern "C"
void* safe_malloc (size_t size);

/**
 * Easier-to-read and NULL-friendly string comparison.
 */
unsigned int
streq (const char *s, const char *t);

#define safe_free  free

#endif /*ndef SBMLMEMORYSTUBS_H */
