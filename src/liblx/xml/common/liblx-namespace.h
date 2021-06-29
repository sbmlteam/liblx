/**
 * @file    liblx-namespace.h
 * @brief   Defines C++ namespace of libLX
 * @author  Akiya Jouraku, Timothy Spain
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
 *
 */

#ifndef LIBLX_NAMESPACE_H
#define LIBLX_NAMESPACE_H

/*
 *
 * The idea of the following macros are borrowed from
 * Xerces-C++ XML Parser (http://xerces.apache.org/xerces-c/).
 *
 */

/* Define to enable libLX C++ namespace */
#undef LIBLX_USE_CPP_NAMESPACE


#if defined(__cplusplus) && defined(LIBLX_USE_CPP_NAMESPACE) && !defined(SWIG)
  /* C++ namespace of libLX */
  #define LIBLX_CPP_NAMESPACE            liblx
  #define LIBLX_CPP_NAMESPACE_BEGIN      namespace LIBLX_CPP_NAMESPACE {
  #define LIBLX_CPP_NAMESPACE_END        }
  #define LIBLX_CPP_NAMESPACE_USE        using namespace LIBLX_CPP_NAMESPACE;
  #define LIBLX_CPP_NAMESPACE_QUALIFIER  LIBLX_CPP_NAMESPACE::

  namespace LIBLX_CPP_NAMESPACE {}
#else
  #define LIBLX_CPP_NAMESPACE
  #define LIBLX_CPP_NAMESPACE_BEGIN
  #define LIBLX_CPP_NAMESPACE_END
  #define LIBLX_CPP_NAMESPACE_USE
  #define LIBLX_CPP_NAMESPACE_QUALIFIER
#endif


#endif  /*ndef LIBLX_NAMESPACE_H */

