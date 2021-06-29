/**
 * @file    liblx-version.h
 * @brief   Define libLX version numbers for access from client software.
 * @author  Michael Hucka
 * 
 * <!--------------------------------------------------------------------------
 * This file is part of libLX.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libLX.
 *
 * Copyright (C) 2019 jointly by the following organizations:
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. University of Heidelberg, Heidelberg, Germany
 *
 * Copyright (C) 2013-2018 jointly by the following organizations:
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 *     3. University of Heidelberg, Heidelberg, Germany
 *
 * Copyright (C) 2009-2013 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 *  
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 *     Pasadena, CA, USA 
 *  
 * Copyright (C) 2002-2005 jointly by the following organizations: 
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. Japan Science and Technology Agency, Japan
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is provided
 * in the file named "LICENSE.txt" included with this software distribution and
 * also available online as http://sbml.org/software/libsbml/license.html
 *------------------------------------------------------------------------- -->
 */

#ifndef LIBLX_VERSION_H
#define LIBLX_VERSION_H

#include <liblx/xml/common/extern.h>


/**
 * LIBLX_DOTTED_VERSION:
 *
 * A version string of the form "1.2.3".
 */
#define LIBLX_DOTTED_VERSION	"0.0.1"


/**
 * LIBLX_VERSION:
 *
 * The version as an integer: version 1.2.3 becomes 10203.  Since the major
 * number comes first, the overall number will always increase when a new
 * libLX is released, making it easy to use less-than and greater-than
 * comparisons when testing versions numbers.
 */
#define LIBLX_VERSION		00001


/**
 * LIBLX_VERSION_STRING:
 *
 * The numeric version as a string: version 1.2.3 becomes "10203".
 */
#define LIBLX_VERSION_STRING	"00001"


LIBLX_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS

/**
 * Returns the version number of this copy of libLX as an integer.
 *
 * @return the libLX version as an integer; version 1.2.3 becomes 10203.
 */
LIBLX_EXTERN
int 
getLibLXVersion () ;


/**
 * Returns the version number of this copy of libLX as a string.
 *
 * @return the libLX version as a string; version 1.2.3 becomes
 * "1.2.3".
 *
 * @see getlibLXVersionString()
 */
LIBLX_EXTERN
const char* 
getLibLXDottedVersion ();


/**
 * Returns the version number of this copy of libLX as a string without
 * periods.
 *
 * @return the libLX version as a string: version 1.2.3 becomes "10203".
 *
 * @see getLibLXDottedVersion()
 */
LIBLX_EXTERN
const char* 
getLibLXVersionString ();


/**
 * Returns an indication whether libLX has been compiled with
 * against a specific library. 
 *
 * @param option the library to test against, this can be one of
 *        "expat", "libxml", "xerces-c", "bzip2", "zip"
 * 
 * @return 0 in case the libLX has not been compiled against
 *         that library and nonzero otherwise (for libraries 
 *         that define an integer version number that number will 
 *         be returned).
 *
 * @see getLibLXDependencyVersionOf(const char* option)
 */
LIBLX_EXTERN
int 
isLibLXCompiledWith(const char* option);


/**
 * Returns the version string for the dependency library used. 
 *
 * @param option the library for which the version
 *        should be retrieved, this can be one of
 *        "expat", "libxml", "xerces-c", "bzip2", "zip"
 * 
 * @return NULL in case libLX has not been compiled against
 *         that library and a version string otherwise.
 *
 * @see isLibLXCompiledWith(const char* option)
 */
LIBLX_EXTERN
const char* 
getLibLXDependencyVersionOf(const char* option);


END_C_DECLS
LIBLX_CPP_NAMESPACE_END

#endif  /* LIBLX_VERSION_H */
