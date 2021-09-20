/**
 * @file    liblxfwd.h
 * @brief   Forward declarations for all opaque C types.
 * @author  Ben Bornstein
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
 * ------------------------------------------------------------------------ -->
 *
 * Declaring all types up-front avoids compilation errors of the form
 * <em>"Redefinition of type 'Foo'"</em>, and allows our combined C/C++
 * headers to depend minimally upon each other.  Put another way, the type
 * definitions below serve the same purpose as <tt>class Foo;</tt> forward
 * declarations in C++ code.
 */

#ifndef LIBLXFWD_H
#define LIBLXFWD_H


#include <liblx/common/liblx-namespace.h>
#include <liblx/common/liblx-version.h>


#ifdef __cplusplus
/**
 * Defined as a class when compiling for C++ and as a C struct when
 * compiling for C.
 */
#  define CLASS_OR_STRUCT class
#else
/**
 * Defined as a class when compiling for C++ and as a C struct when
 * compiling for C.
 */
#  define CLASS_OR_STRUCT struct
#endif  /* __cplusplus */

LIBLX_CPP_NAMESPACE_BEGIN

typedef CLASS_OR_STRUCT XMLError                  XMLError_t;

/**
 * @var typedef class XMLErrorLog XMLErrorLog_t
 * @copydoc XMLErrorLog
 */
typedef CLASS_OR_STRUCT XMLErrorLog               XMLErrorLog_t;

/**
 * @var typedef class XMLNode XMLNode_t
 * @copydoc XMLNode
 */
typedef CLASS_OR_STRUCT XMLNode                   XMLNode_t;

/**
 * @var typedef class XMLAttributes XMLAttributes_t
 * @copydoc XMLAttributes
 */
typedef CLASS_OR_STRUCT XMLAttributes             XMLAttributes_t;

/**
 * @var typedef class XMLNamespaces XMLNamespaces_t
 * @copydoc XMLNamespaces
 */
typedef CLASS_OR_STRUCT XMLNamespaces		  XMLNamespaces_t;

/**
 * @var typedef class XMLToken XMLToken_t
 * @copydoc XMLToken
 */
typedef CLASS_OR_STRUCT XMLToken                  XMLToken_t;

/** @cond doxygenLibsbmlInternal */
/**
 * @var typedef class XMLInputStream XMLInputStream_t
 * @copydoc XMLInputStream
 */
typedef CLASS_OR_STRUCT XMLInputStream            XMLInputStream_t;
/** @endcond */

/** @cond doxygenLibsbmlInternal */
/**
 * @var typedef class XMLOutputStream XMLOutputStream_t
 * @copydoc XMLOutputStream
 */
typedef CLASS_OR_STRUCT XMLOutputStream           XMLOutputStream_t;
/** @endcond */

/**
 * @var typedef class XMLTriple XMLTriple_t
 * @copydoc XMLTriple
 */
typedef CLASS_OR_STRUCT XMLTriple                 XMLTriple_t;

/* FIXME Remove when no longer needed */
typedef CLASS_OR_STRUCT LXNamespaces            LXNamespaces_t;

LIBLX_CPP_NAMESPACE_END

#undef CLASS_OR_STRUCT

#endif  /* ndef LIBLXFWD_H  */
