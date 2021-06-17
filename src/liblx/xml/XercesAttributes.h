/**
 * @cond doxygenLibsbmlInternal
 *
 * @file    XercesAttributes.h
 * @brief   Creates new XMLAttributes from "raw" Xerces-C++ attributes.
 * @author  Ben Bornstein
 * 
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
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
 * ---------------------------------------------------------------------- -->*/

#ifndef XercesAttributes_h
#define XercesAttributes_h

#ifdef __cplusplus

#include <string>

#include <xercesc/sax2/Attributes.hpp>
#include <liblx/xml/XMLAttributes.h>

LIBLX_CPP_NAMESPACE_BEGIN

class XercesAttributes : public XMLAttributes
{
public:

  /**
   * Creates a new XMLAttributes set that wraps the given "raw" Xerces-C++
   * Attributes set.
   */
  XercesAttributes (const xercesc::Attributes& attrs,
		    const std::string elementName);


  /**
   * Destroys this XercesAttributes set.
   */
  virtual ~XercesAttributes ();
};


LIBLX_CPP_NAMESPACE_END

#endif  /* __cplusplus */
#endif  /* XercesAttributes_h */

/** @endcond */
