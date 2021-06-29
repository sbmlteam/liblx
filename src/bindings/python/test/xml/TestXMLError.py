#
# @file    TestXMLError.py
# @brief   XMLError unit tests, C++ version
#
# @author  Akiya Jouraku (Python conversion)
# @author  Michael Hucka 
#
# -----------------------------------------------------------------------------
# This file is part of libLX.  Please visit http://sbml.org for more
# information about LX, and the latest version of libLX.
#
# Copyright 2005-2010 California Institute of Technology.
# Copyright 2002-2005 California Institute of Technology and
#                     Japan Science and Technology Corporation.
# 
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation.  A copy of the license agreement is provided
# in the file named "LICENSE.txt" included with this software distribution
# and also available online as http://sbml.org/software/libsbml/license.html
# -----------------------------------------------------------------------------

import sys
import unittest
import liblx


class TestXMLError(unittest.TestCase):


  def test_XMLError_create(self):
    error = liblx.XMLError()
    self.assert_( error != None )
    error = None
    error = liblx.XMLError(liblx.DuplicateXMLAttribute)
    self.assert_( error.getErrorId() == liblx.DuplicateXMLAttribute )
    self.assert_( error.getSeverity() == liblx.LIBLX_SEV_ERROR )
    self.assert_( error.getSeverityAsString() ==  "Error"  )
    self.assert_( error.getCategory() == liblx.LIBLX_CAT_XML )
    self.assert_( error.getCategoryAsString() ==  "XML content" )
#   self.assert_( error.getMessage() ==  "Duplicate XML attribute.\n"  )
    self.assert_( error.getShortMessage() ==  "Duplicate attribute"  )
    error = None
    error = liblx.XMLError(12345, "My message")
    self.assert_( error.getErrorId() == 12345 )
    self.assert_( error.getMessage() ==  "My message"  )
    self.assert_( error.getSeverity() == liblx.LIBLX_SEV_FATAL )
    self.assert_( error.getSeverityAsString() ==  "Fatal"  )
    self.assert_( error.getCategory() == liblx.LIBLX_CAT_INTERNAL )
    self.assert_( error.getCategoryAsString() ==  "Internal" )
    error = None
    error = liblx.XMLError(12345, "My message",0,0,liblx.LIBLX_SEV_INFO,liblx.LIBLX_CAT_SYSTEM)
    self.assert_( error.getErrorId() == 12345 )
    self.assert_( error.getMessage() ==  "My message"  )
    self.assert_( error.getSeverity() == liblx.LIBLX_SEV_INFO )
    self.assert_( error.getSeverityAsString() ==  "Informational"  )
    self.assert_( error.getCategory() == liblx.LIBLX_CAT_SYSTEM )
    self.assert_( error.getCategoryAsString() ==  "Operating system" )
    self.assertEqual( True, error.isInfo() )
    self.assertEqual( True, error.isSystem() )
    error = None
    error = liblx.XMLError(10000, "Another message",0,0,liblx.LIBLX_SEV_FATAL,liblx.LIBLX_CAT_XML)
    self.assert_( error.getErrorId() == 10000 )
    self.assert_( error.getMessage() ==  "Another message"  )
    self.assert_( error.getSeverity() == liblx.LIBLX_SEV_FATAL )
    self.assert_( error.getSeverityAsString() ==  "Fatal"  )
    self.assert_( error.getCategory() == liblx.LIBLX_CAT_XML )
    self.assert_( error.getCategoryAsString() ==  "XML content" )
    self.assertEqual( True, error.isFatal() )
    self.assertEqual( True, error.isXML() )
    error = None
    pass  

  def test_XMLError_setters(self):
    error = liblx.XMLError()
    self.assert_( error != None )
    i = error.setLine(23)
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( error.getLine() == 23 )
    i = error.setColumn(45)
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( error.getColumn() == 45 )
    error = None
    pass  

def suite():
  suite = unittest.TestSuite()
  suite.addTest(unittest.makeSuite(TestXMLError))

  return suite

if __name__ == "__main__":
  if unittest.TextTestRunner(verbosity=1).run(suite()).wasSuccessful() :
    sys.exit(0)
  else:
    sys.exit(1)
