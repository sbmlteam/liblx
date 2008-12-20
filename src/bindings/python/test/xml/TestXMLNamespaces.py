#
# @file    TestXMLNamespaces.py
# @brief   XMLNamespaces unit tests
#
# @author  Akiya Jouraku (Python conversion)
# @author  Michael Hucka <mhucka@caltech.edu> 
#
# $Id:$
# $HeadURL:$
#
# This test file was converted from src/sbml/test/TestXMLNamespaces.c
# with the help of conversion sciprt (ctest_converter.pl).
#
#<!---------------------------------------------------------------------------
# This file is part of libSBML.  Please visit http://sbml.org for more
# information about SBML, and the latest version of libSBML.
#
# Copyright 2005-2008 California Institute of Technology.
# Copyright 2002-2005 California Institute of Technology and
#                     Japan Science and Technology Corporation.
# 
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation.  A copy of the license agreement is provided
# in the file named "LICENSE.txt" included with this software distribution
# and also available online as http://sbml.org/software/libsbml/license.html
#--------------------------------------------------------------------------->*/
import sys
import unittest
import libsbml

class TestXMLNamespaces(unittest.TestCase):

  NS = None

  def setUp(self):
    self.NS = libsbml.XMLNamespaces()
    if (self.NS == None):
      pass    
    pass  

  def tearDown(self):
    self.NS = None
    pass  

  def test_XMLNamespaces_add(self):
    self.assert_( self.NS.getLength() == 0 )
    self.assert_( self.NS.isEmpty() == True )
    self.NS.add( "http://test1.org/", "test1")
    self.assert_( self.NS.getLength() == 1 )
    self.assert_( self.NS.isEmpty() == False )
    self.NS.add( "http://test2.org/", "test2")
    self.assert_( self.NS.getLength() == 2 )
    self.assert_( self.NS.isEmpty() == False )
    self.NS.add( "http://test1.org/", "test1a")
    self.assert_( self.NS.getLength() == 3 )
    self.assert_( self.NS.isEmpty() == False )
    self.NS.add( "http://test1.org/", "test1a")
    self.assert_( self.NS.getLength() == 3 )
    self.assert_( self.NS.isEmpty() == False )
    self.assertFalse( self.NS.getIndex( "http://test1.org/") == -1 )
    pass  

  def test_XMLNamespaces_baseline(self):
    self.assert_( self.NS.getLength() == 0 )
    self.assert_( self.NS.isEmpty() == True )
    pass  

  def test_XMLNamespaces_get(self):
    self.NS.add( "http://test1.org/", "test1")
    self.NS.add( "http://test2.org/", "test2")
    self.NS.add( "http://test3.org/", "test3")
    self.NS.add( "http://test4.org/", "test4")
    self.NS.add( "http://test5.org/", "test5")
    self.NS.add( "http://test6.org/", "test6")
    self.NS.add( "http://test7.org/", "test7")
    self.NS.add( "http://test8.org/", "test8")
    self.NS.add( "http://test9.org/", "test9")
    self.assert_( self.NS.getLength() == 9 )
    self.assert_( self.NS.getIndex( "http://test1.org/") == 0 )
    self.assert_( (  "test2" != self.NS.getPrefix(1) ) == False )
    self.assert_( ( 		      "test1" != self.NS.getPrefix( "http://test1.org/") ) == False )
    self.assert_( (  "http://test2.org/" != self.NS.getURI(1) ) == False )
    self.assert_( ( 		      "http://test2.org/" != self.NS.getURI( "test2") ) == False )
    self.assert_( self.NS.getIndex( "http://test1.org/") == 0 )
    self.assert_( self.NS.getIndex( "http://test2.org/") == 1 )
    self.assert_( self.NS.getIndex( "http://test5.org/") == 4 )
    self.assert_( self.NS.getIndex( "http://test9.org/") == 8 )
    self.assert_( self.NS.getIndex( "http://testX.org/") == -1 )
    self.assert_( self.NS.hasURI( "http://test1.org/") != False )
    self.assert_( self.NS.hasURI( "http://test2.org/") != False )
    self.assert_( self.NS.hasURI( "http://test5.org/") != False )
    self.assert_( self.NS.hasURI( "http://test9.org/") != False )
    self.assert_( self.NS.hasURI( "http://testX.org/") == False )
    self.assert_( self.NS.getIndexByPrefix( "test1") == 0 )
    self.assert_( self.NS.getIndexByPrefix( "test5") == 4 )
    self.assert_( self.NS.getIndexByPrefix( "test9") == 8 )
    self.assert_( self.NS.getIndexByPrefix( "testX") == -1 )
    self.assert_( self.NS.hasPrefix( "test1") != False )
    self.assert_( self.NS.hasPrefix( "test5") != False )
    self.assert_( self.NS.hasPrefix( "test9") != False )
    self.assert_( self.NS.hasPrefix( "testX") == False )
    self.assert_( self.NS.hasNS( "http://test1.org/", "test1") != False )
    self.assert_( self.NS.hasNS( "http://test5.org/", "test5") != False )
    self.assert_( self.NS.hasNS( "http://test9.org/", "test9") != False )
    self.assert_( self.NS.hasNS( "http://testX.org/", "testX") == False )
    pass  

  def test_XMLNamespaces_remove(self):
    self.NS.add( "http://test1.org/", "test1")
    self.NS.add( "http://test2.org/", "test2")
    self.NS.add( "http://test3.org/", "test3")
    self.NS.add( "http://test4.org/", "test4")
    self.NS.add( "http://test5.org/", "test5")
    self.assert_( self.NS.getLength() == 5 )
    self.NS.remove(4)
    self.assert_( self.NS.getLength() == 4 )
    self.NS.remove(3)
    self.assert_( self.NS.getLength() == 3 )
    self.NS.remove(2)
    self.assert_( self.NS.getLength() == 2 )
    self.NS.remove(1)
    self.assert_( self.NS.getLength() == 1 )
    self.NS.remove(0)
    self.assert_( self.NS.getLength() == 0 )
    self.NS.add( "http://test1.org/", "test1")
    self.NS.add( "http://test2.org/", "test2")
    self.NS.add( "http://test3.org/", "test3")
    self.NS.add( "http://test4.org/", "test4")
    self.NS.add( "http://test5.org/", "test5")
    self.assert_( self.NS.getLength() == 5 )
    self.NS.remove(0)
    self.assert_( self.NS.getLength() == 4 )
    self.NS.remove(0)
    self.assert_( self.NS.getLength() == 3 )
    self.NS.remove(0)
    self.assert_( self.NS.getLength() == 2 )
    self.NS.remove(0)
    self.assert_( self.NS.getLength() == 1 )
    self.NS.remove(0)
    self.assert_( self.NS.getLength() == 0 )
    pass  

  def test_XMLNamespaces_remove_by_prefix(self):
    self.NS.add( "http://test1.org/", "test1")
    self.NS.add( "http://test2.org/", "test2")
    self.NS.add( "http://test3.org/", "test3")
    self.NS.add( "http://test4.org/", "test4")
    self.NS.add( "http://test5.org/", "test5")
    self.assert_( self.NS.getLength() == 5 )
    self.NS.remove( "test1")
    self.assert_( self.NS.getLength() == 4 )
    self.NS.remove( "test2")
    self.assert_( self.NS.getLength() == 3 )
    self.NS.remove( "test3")
    self.assert_( self.NS.getLength() == 2 )
    self.NS.remove( "test4")
    self.assert_( self.NS.getLength() == 1 )
    self.NS.remove( "test5")
    self.assert_( self.NS.getLength() == 0 )
    self.NS.add( "http://test1.org/", "test1")
    self.NS.add( "http://test2.org/", "test2")
    self.NS.add( "http://test3.org/", "test3")
    self.NS.add( "http://test4.org/", "test4")
    self.NS.add( "http://test5.org/", "test5")
    self.assert_( self.NS.getLength() == 5 )
    self.NS.remove( "test5")
    self.assert_( self.NS.getLength() == 4 )
    self.NS.remove( "test4")
    self.assert_( self.NS.getLength() == 3 )
    self.NS.remove( "test3")
    self.assert_( self.NS.getLength() == 2 )
    self.NS.remove( "test2")
    self.assert_( self.NS.getLength() == 1 )
    self.NS.remove( "test1")
    self.assert_( self.NS.getLength() == 0 )
    self.NS.add( "http://test1.org/", "test1")
    self.NS.add( "http://test2.org/", "test2")
    self.NS.add( "http://test3.org/", "test3")
    self.NS.add( "http://test4.org/", "test4")
    self.NS.add( "http://test5.org/", "test5")
    self.assert_( self.NS.getLength() == 5 )
    self.NS.remove( "test3")
    self.assert_( self.NS.getLength() == 4 )
    self.NS.remove( "test1")
    self.assert_( self.NS.getLength() == 3 )
    self.NS.remove( "test4")
    self.assert_( self.NS.getLength() == 2 )
    self.NS.remove( "test5")
    self.assert_( self.NS.getLength() == 1 )
    self.NS.remove( "test2")
    self.assert_( self.NS.getLength() == 0 )
    pass  

def suite():
  suite = unittest.TestSuite()
  suite.addTest(unittest.makeSuite(TestXMLNamespaces))

  return suite

if __name__ == "__main__":
  if unittest.TextTestRunner(verbosity=1).run(suite()).wasSuccessful() :
    sys.exit(0)
  else:
    sys.exit(1)
