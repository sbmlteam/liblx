/**
 * @file    operationReturnValues.h
 * @brief   Enumeration of values returned by operations within libLX.
 * @author  Sarah Keating
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
 * ---------------------------------------------------------------------- -->*/

#ifndef LIBLX_OPERATION_RETURN_VALUES_H
#define LIBLX_OPERATION_RETURN_VALUES_H

/**
 * @enum OperationReturnValues_t
 * LibLX diagnostic return codes.
 *
 * Many methods in libLX return a status code to indicate whether the
 * operation requested by the caller succeeded or failed.  This enumeration
 * lists all the possible return codes from any libLX methods.
 */
typedef enum
{
    LIBLX_OPERATION_SUCCESS       = 0
    /*!< The operation was successful. */

  , LIBLX_INDEX_EXCEEDS_SIZE      = -1
    /*!< An index parameter exceeded the bounds of a data array or other
     * collection used in the operation.  This return value is typically
     * returned by methods that take index numbers to refer to lists
     * of objects, when the caller has provided an index that exceeds
     * the bounds of the list.  LibLX provides methods for checking the
     * size of list/sequence/collection structures, and callers should
     * verify the sizes before calling methods that take index numbers. */

  , LIBLX_UNEXPECTED_ATTRIBUTE    = -2
    /*!< The attribute that is the subject of this operation is not valid
     * for the combination of LX Level and Version for the underlying
     * object.  This can happen because libLX strives to offer a uniform
     * API for all LX Levels and Versions, but some object attributes and
     * elements are not defined for all LX Levels and Versions.  Calling
     * programs are expected to be aware of which object structures they
     * are working with, but when errors of this kind occur, they are
     * reported using this return value. */

  , LIBLX_OPERATION_FAILED        = -3
    /*!< The requested action could not be performed.  This can occur in
     * a variety of contexts, such as passing a null object as a parameter
     * in a situation where it does not make sense to permit a null object.
     */

  , LIBLX_INVALID_ATTRIBUTE_VALUE = -4
    /*!< A value passed as an argument to the method is not of a type that
     * is valid for the operation or kind of object involved.  For example,
     * this return code is used when a calling program attempts to set an
     * LX object identifier to a string whose syntax does not conform to
     * the LX identifier syntax. */

  , LIBLX_INVALID_OBJECT          = -5
    /*!< The object passed as an argument to the method is not of a type
     * that is valid for the operation or kind of object involved.  For
     * example, handing an invalidly-constructed ASTNode to a method
     * expecting an ASTNode will result in this error. */

  , LIBLX_INVALID_XML_OPERATION   = -9
    /*!< The XML operation attempted is not valid for the object or context
     * involved.  This error is typically returned by the XML interface layer
     * of libLX, when a calling program attempts to construct or manipulate
     * XML in an invalid way.  */

  , LIBLX_NAMESPACES_MISMATCH   = -10
    /*!< The LX Namespaces associated with the object
     * do not match the LX Namespaces of the parent object.  This error can
     * happen when an LX component such as a species or compartment object
     * is created outside of a model and a calling program then attempts to
     * add the object to a model that has a different LX Namespaces
     * combination. */

     , LIBLX_DEPRECATED_ATTRIBUTE   = -15
    /*!< The attribute that is the subject of this operation has been deprecated
     * for the combination of LX Level and Version for the underlying
     * object. */

} OperationReturnValues_t;


#endif  /*ndef LIBLX_OPERATION_RETURN_VALUES_H */

