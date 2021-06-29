#
# @file    TestXMLTriple.py
# @brief   XMLTriple unit tests
#
# @author  Akiya Jouraku (Python conversion)
# @author  Michael Hucka <mhucka@caltech.edu> 
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


class TestXMLTriple(unittest.TestCase):


  def test_XMLTriple_create(self):
    t = liblx.XMLTriple()
    self.assert_( t != None )
    self.assert_( t.isEmpty() != False )
    _dummyList = [ t ]; _dummyList[:] = []; del _dummyList
    t = liblx.XMLTriple("attr", "uri", "prefix")
    self.assert_( (  "attr" != t.getName() ) == False )
    self.assert_( (  "uri" != t.getURI() ) == False )
    self.assert_( (  "prefix" != t.getPrefix() ) == False )
    self.assert_( (  "prefix:attr" != t.getPrefixedName() ) == False )
    self.assert_( t.isEmpty() == False )
    _dummyList = [ t ]; _dummyList[:] = []; del _dummyList
    t = liblx.XMLTriple("attr", "uri", "")
    self.assert_( (  "attr" != t.getName() ) == False )
    self.assert_( (  "uri" != t.getURI() ) == False )
    self.assert_( t.getPrefix() == "" )
    self.assert_( (  "attr" != t.getPrefixedName() ) == False )
    self.assert_( t.isEmpty() == False )
    _dummyList = [ t ]; _dummyList[:] = []; del _dummyList
    pass  

def suite():
  suite = unittest.TestSuite()
  suite.addTest(unittest.makeSuite(TestXMLTriple))

  return suite

if __name__ == "__main__":
  if unittest.TextTestRunner(verbosity=1).run(suite()).wasSuccessful() :
    sys.exit(0)
  else:
    sys.exit(1)
