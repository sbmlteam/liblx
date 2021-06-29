/**
 * \file    liblx.h
 * \brief   Language-independent SWIG includes for wrapping libLX
 * \author  Ben Bornstein
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
 * in the file named "LICENSE.txt" included with this software distribution
 * and also available online as http://sbml.org/software/libsbml/license.html
 * ---------------------------------------------------------------------- -->*/

#include <sstream>

#include <liblx/xml/common/common.h>
#include <liblx/xml/common/extern.h>
#include <liblx/xml/common/liblx-config.h>
#include <liblx/xml/common/liblx-namespace.h>
#include <liblx/xml/common/liblx-version.h>
#include <liblx/xml/common/liblxfwd.h>

#include <liblx/xml/compress/CompressCommon.h>
#include <liblx/xml/compress/InputDecompressor.h>
#include <liblx/xml/compress/OutputCompressor.h>
#include <liblx/xml/compress/bzfstream.h>
#include <liblx/xml/compress/crypt.h>
#include <liblx/xml/compress/ioapi.h>
#include <liblx/xml/compress/ioapi_mem.h>

#ifdef WIN32
    #include <liblx/xml/compress/iowin32.h>   // I guess we need this for Windows builds - it includes <windows.h>
#endif

#include <liblx/xml/compress/unzip.h>
#include <liblx/xml/compress/zfstream.h>
#include <liblx/xml/compress/zip.h>
#include <liblx/xml/compress/zipfstream.h>

#include <liblx/xml/LibLXError.h>

#include <liblx/xml/operationReturnValues.h>
#include <liblx/xml/sbmlStubs.h>

#include <liblx/xml/XMLAttributes.h>
#include <liblx/xml/XMLBuffer.h>
#include <liblx/xml/XMLConstructorException.h>
#include <liblx/xml/XMLError.h>
#include <liblx/xml/XMLErrorLog.h>
#include <liblx/xml/XMLFileBuffer.h>
#include <liblx/xml/XMLHandler.h>
#include <liblx/xml/XMLInputStream.h>
#include <liblx/xml/XMLLogOverride.h>
#include <liblx/xml/XMLMemoryBuffer.h>
#include <liblx/xml/XMLNamespaces.h>
#include <liblx/xml/XMLNode.h>
#include <liblx/xml/XMLOutputStream.h>
#include <liblx/xml/XMLParser.h>
#include <liblx/xml/XMLToken.h>
#include <liblx/xml/XMLTokenizer.h>
#include <liblx/xml/XMLTriple.h>

/*
The default XML library used is WITH_LIBXML
Want conditional compilation
*/
//#ifdef WITH_LIBXML // <-- not getting picked up for some reason (with cmake -DWITH_LIBXML=TRUE)
#if !defined(WITH_XERCES) && !defined(WITH_EXPAT)
    #include <liblx/xml/LibXMLAttributes.h>
    #include <liblx/xml/LibXMLHandler.h>
    #include <liblx/xml/LibXMLNamespaces.h>
    #include <liblx/xml/LibXMLParser.h>
    #include <liblx/xml/LibXMLTranscode.h>
#endif
#ifdef WITH_XERCES
    #include <liblx/xml/XercesAttributes.h>
    #include <liblx/xml/XercesHandler.h>
    #include <liblx/xml/XercesNamespaces.h>
    #include <liblx/xml/XercesParser.h>
    #include <liblx/xml/XercesTranscode.h>
#endif
#ifdef WITH_EXPAT
    #include <liblx/xml/ExpatAttributes.h>
    #include <liblx/xml/ExpatHandler.h>
    #include <liblx/xml/ExpatParser.h>
#endif




