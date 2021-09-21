/**
 * @file    XMLConstructorException.h
 * @brief   XMLConstructorException an exception thrown by XML classes
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
 * in the file named "LICENSE.txt" included with this software distribution
 * and also available online as http://sbml.org/software/libsbml/license.html
 * ------------------------------------------------------------------------ -->
 *
 * @class XMLConstructorException
 * @sbmlbrief{core} Exceptions thrown by some libLX constructors.
 *
 * @htmlinclude not-sbml-warning.html
 *
 * In some situations, constructors for LX objects may need to indicate
 * to callers that the creation of the object failed.  The failure may be
 * for different reasons, such as an attempt to use invalid parameters or a
 * system condition such as a memory error.  To communicate this to
 * callers, those classes will throw an XMLConstructorException.  @if cpp
 * Callers can use the standard C++ <code>std::exception</code> method
 * <code>what()</code> to extract the diagnostic message stored with the
 * exception.@endif@~
 * <p>
 * In languages that don't have an exception mechanism (e.g., C), the
 * constructors generally try to return an error code instead of throwing
 * an exception.
 *
 * @see LXConstructorException
 */


#ifndef XMLConstructorException_h
#define XMLConstructorException_h

#include <liblx/common/liblxfwd.h>

#ifdef __cplusplus


#include <string>
#include <stdexcept>

LIBLX_CPP_NAMESPACE_BEGIN

class LIBLAX_EXTERN XMLConstructorException : public std::invalid_argument
{
public:

  /** @cond doxygenLibsbmlInternal */
  /* constructor */
  XMLConstructorException (std::string 
                    message="NULL reference in XML constructor");

  /** @endcond */
};


LIBLX_CPP_NAMESPACE_END

#endif  /* __cplusplus */



#ifndef SWIG

LIBLX_CPP_NAMESPACE_BEGIN
BEGIN_C_DECLS


END_C_DECLS
LIBLX_CPP_NAMESPACE_END

#endif  /* !SWIG */

#endif  /* XMLConstructorException_h */
