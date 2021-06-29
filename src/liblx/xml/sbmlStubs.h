/*
 * sbmlStubs.h
 *
 *  Created on: 27 October 2020
 *      Author: Timothy Spain
 */

#ifndef SBMLSTUBS_H
#define SBMLSTUBS_H

#include <ctype.h>

extern "C" {
    char* safe_strdup(const char* s);
    void* safe_malloc (size_t size);
    unsigned int streq (const char *s, const char *t);
}

#define safe_free  free

#endif /*ndef SBMLSTUBS_H */
