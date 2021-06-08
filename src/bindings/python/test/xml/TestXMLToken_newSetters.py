#
# @file    TestXMLToken_newSetters.py
# @brief   XMLToken_newSetters unit tests
#
# @author  Akiya Jouraku (Python conversion)
# @author  Sarah Keating 
# 
# -----------------------------------------------------------------------------
# This file is part of libLX.  Please visit http://sbml.org for more
# information about libLX, and the latest version of libLX.
#
# Copyright 2005-2010 California Institute of Technology.
# Copyright 2002-2005 California Institute of Technology and
#                     Japan Science and Technology Corporation.
# 
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation.  A copy of the license agreement is provided
# in the file named "LICENSE.txt" included with this software distribution
# and also available online as http://lx.org/software/liblx/license.html
# -----------------------------------------------------------------------------

import sys
import unittest
import liblx


class TestXMLToken_newSetters(unittest.TestCase):


  def test_XMLToken_newSetters_addAttributes1(self):
    triple = liblx.XMLTriple("test","","")
    attr = liblx.XMLAttributes()
    token = liblx.XMLToken(triple,attr)
    xt2 = liblx.XMLTriple("name3", "http://name3.org/", "p3")
    i = token.addAttr( "name1", "val1")
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.getAttributesLength() == 1 )
    self.assert_( token.isAttributesEmpty() == False )
    self.assert_( (  "name1" != token.getAttrName(0) ) == False )
    self.assert_( (  "val1"  != token.getAttrValue(0) ) == False )
    i = token.addAttr( "name2", "val2", "http://name1.org/", "p1")
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.getAttributesLength() == 2 )
    self.assert_( token.isAttributesEmpty() == False )
    self.assert_( (  "name2" != token.getAttrName(1) ) == False )
    self.assert_( (  "val2"  != token.getAttrValue(1) ) == False )
    self.assert_( (  "http://name1.org/" != token.getAttrURI(1) ) == False )
    self.assert_( (  "p1"    != token.getAttrPrefix(1) ) == False )
    i = token.addAttr(xt2, "val2")
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.getAttributesLength() == 3 )
    self.assert_( token.isAttributesEmpty() == False )
    self.assert_( (  "name3" != token.getAttrName(2) ) == False )
    self.assert_( (  "val2"  != token.getAttrValue(2) ) == False )
    self.assert_( (  "http://name3.org/" != token.getAttrURI(2) ) == False )
    self.assert_( (  "p3"    != token.getAttrPrefix(2) ) == False )
    _dummyList = [ xt2 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLToken_newSetters_addAttributes2(self):
    triple = liblx.XMLTriple("test","","")
    token = liblx.XMLToken(triple)
    xt2 = liblx.XMLTriple("name3", "http://name3.org/", "p3")
    i = token.addAttr( "name1", "val1")
    self.assert_( i == liblx.LIBLX_INVALID_XML_OPERATION )
    self.assert_( token.getAttributesLength() == 0 )
    self.assert_( token.isAttributesEmpty() == True )
    i = token.addAttr( "name2", "val2", "http://name1.org/", "p1")
    self.assert_( i == liblx.LIBLX_INVALID_XML_OPERATION )
    self.assert_( token.getAttributesLength() == 0 )
    self.assert_( token.isAttributesEmpty() == True )
    i = token.addAttr(xt2, "val2")
    self.assert_( i == liblx.LIBLX_INVALID_XML_OPERATION )
    self.assert_( token.getAttributesLength() == 0 )
    self.assert_( token.isAttributesEmpty() == True )
    _dummyList = [ xt2 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLToken_newSetters_addNamespaces1(self):
    triple = liblx.XMLTriple("test","","")
    attr = liblx.XMLAttributes()
    token = liblx.XMLToken(triple,attr)
    self.assert_( token.getNamespacesLength() == 0 )
    self.assert_( token.isNamespacesEmpty() == True )
    i = token.addNamespace( "http://test1.org/", "test1")
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.getNamespacesLength() == 1 )
    self.assert_( token.isNamespacesEmpty() == False )
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLToken_newSetters_addNamespaces2(self):
    triple = liblx.XMLTriple("test","","")
    token = liblx.XMLToken(triple)
    self.assert_( token.getNamespacesLength() == 0 )
    self.assert_( token.isNamespacesEmpty() == True )
    i = token.addNamespace( "http://test1.org/", "test1")
    self.assert_( i == liblx.LIBLX_INVALID_XML_OPERATION )
    self.assert_( token.getNamespacesLength() == 0 )
    self.assert_( token.isNamespacesEmpty() == True )
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLToken_newSetters_clearAttributes1(self):
    triple = liblx.XMLTriple("test","","")
    attr = liblx.XMLAttributes()
    token = liblx.XMLToken(triple,attr)
    nattr = liblx.XMLAttributes()
    xt1 = liblx.XMLTriple("name1", "http://name1.org/", "p1")
    nattr.add(xt1, "val1")
    i = token.setAttributes(nattr)
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.isAttributesEmpty() == False )
    i = token.clearAttributes()
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.isAttributesEmpty() == True )
    _dummyList = [ nattr ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ xt1 ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLToken_newSetters_clearNamespaces1(self):
    triple = liblx.XMLTriple("test","","")
    attr = liblx.XMLAttributes()
    token = liblx.XMLToken(triple,attr)
    ns = liblx.XMLNamespaces()
    self.assert_( token.getNamespacesLength() == 0 )
    self.assert_( token.isNamespacesEmpty() == True )
    ns.add( "http://test1.org/", "test1")
    i = token.setNamespaces(ns)
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.getNamespacesLength() == 1 )
    self.assert_( token.isNamespacesEmpty() == False )
    i = token.clearNamespaces()
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.getNamespacesLength() == 0 )
    self.assert_( token.isNamespacesEmpty() == True )
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ ns ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLToken_newSetters_removeAttributes1(self):
    triple = liblx.XMLTriple("test","","")
    attr = liblx.XMLAttributes()
    token = liblx.XMLToken(triple,attr)
    xt2 = liblx.XMLTriple("name3", "http://name3.org/", "p3")
    xt1 = liblx.XMLTriple("name5", "http://name5.org/", "p5")
    i = token.addAttr( "name1", "val1")
    i = token.addAttr( "name2", "val2", "http://name1.org/", "p1")
    i = token.addAttr(xt2, "val2")
    i = token.addAttr( "name4", "val4")
    self.assert_( token.getAttributes().getLength() == 4 )
    i = token.removeAttr(7)
    self.assert_( i == liblx.LIBLX_INDEX_EXCEEDS_SIZE )
    i = token.removeAttr( "name7")
    self.assert_( i == liblx.LIBLX_INDEX_EXCEEDS_SIZE )
    i = token.removeAttr( "name7", "namespaces7")
    self.assert_( i == liblx.LIBLX_INDEX_EXCEEDS_SIZE )
    i = token.removeAttr(xt1)
    self.assert_( i == liblx.LIBLX_INDEX_EXCEEDS_SIZE )
    self.assert_( token.getAttributes().getLength() == 4 )
    i = token.removeAttr(3)
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.getAttributes().getLength() == 3 )
    i = token.removeAttr( "name1")
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.getAttributes().getLength() == 2 )
    i = token.removeAttr( "name2", "http://name1.org/")
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.getAttributes().getLength() == 1 )
    i = token.removeAttr(xt2)
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.getAttributes().getLength() == 0 )
    _dummyList = [ xt1 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ xt2 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLToken_newSetters_removeNamespaces(self):
    triple = liblx.XMLTriple("test","","")
    attr = liblx.XMLAttributes()
    token = liblx.XMLToken(triple,attr)
    token.addNamespace( "http://test1.org/", "test1")
    self.assert_( token.getNamespacesLength() == 1 )
    i = token.removeNamespace(4)
    self.assert_( i == liblx.LIBLX_INDEX_EXCEEDS_SIZE )
    self.assert_( token.getNamespacesLength() == 1 )
    i = token.removeNamespace(0)
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.getNamespacesLength() == 0 )
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLToken_newSetters_removeNamespaces1(self):
    triple = liblx.XMLTriple("test","","")
    attr = liblx.XMLAttributes()
    token = liblx.XMLToken(triple,attr)
    token.addNamespace( "http://test1.org/", "test1")
    self.assert_( token.getNamespacesLength() == 1 )
    i = token.removeNamespace( "test2")
    self.assert_( i == liblx.LIBLX_INDEX_EXCEEDS_SIZE )
    self.assert_( token.getNamespacesLength() == 1 )
    i = token.removeNamespace( "test1")
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.getNamespacesLength() == 0 )
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLToken_newSetters_setAttributes1(self):
    triple = liblx.XMLTriple("test","","")
    attr = liblx.XMLAttributes()
    token = liblx.XMLToken(triple,attr)
    nattr = liblx.XMLAttributes()
    xt1 = liblx.XMLTriple("name1", "http://name1.org/", "p1")
    nattr.add(xt1, "val1")
    i = token.setAttributes(nattr)
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.isAttributesEmpty() == False )
    _dummyList = [ nattr ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ xt1 ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLToken_newSetters_setAttributes2(self):
    triple = liblx.XMLTriple("test","","")
    token = liblx.XMLToken(triple)
    nattr = liblx.XMLAttributes()
    xt1 = liblx.XMLTriple("name1", "http://name1.org/", "p1")
    nattr.add(xt1, "val1")
    i = token.setAttributes(nattr)
    self.assert_( i == liblx.LIBLX_INVALID_XML_OPERATION )
    self.assert_( token.isAttributesEmpty() == True )
    _dummyList = [ nattr ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ xt1 ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLToken_newSetters_setEOF(self):
    token = liblx.XMLToken()
    self.assert_( token.isEnd() == False )
    i = token.setEOF()
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.isEnd() == False )
    self.assert_( token.isStart() == False )
    self.assert_( token.isText() == False )
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLToken_newSetters_setEnd(self):
    token = liblx.XMLToken()
    self.assert_( token.isEnd() == False )
    i = token.setEnd()
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.isEnd() == True )
    i = token.unsetEnd()
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.isEnd() == False )
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLToken_newSetters_setNamespaces1(self):
    triple = liblx.XMLTriple("test","","")
    attr = liblx.XMLAttributes()
    token = liblx.XMLToken(triple,attr)
    ns = liblx.XMLNamespaces()
    self.assert_( token.getNamespacesLength() == 0 )
    self.assert_( token.isNamespacesEmpty() == True )
    ns.add( "http://test1.org/", "test1")
    i = token.setNamespaces(ns)
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_( token.getNamespacesLength() == 1 )
    self.assert_( token.isNamespacesEmpty() == False )
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ ns ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLToken_newSetters_setNamespaces2(self):
    triple = liblx.XMLTriple("test","","")
    token = liblx.XMLToken(triple)
    ns = liblx.XMLNamespaces()
    self.assert_( token.getNamespacesLength() == 0 )
    self.assert_( token.isNamespacesEmpty() == True )
    ns.add( "http://test1.org/", "test1")
    i = token.setNamespaces(ns)
    self.assert_( i == liblx.LIBLX_INVALID_XML_OPERATION )
    self.assert_( token.getNamespacesLength() == 0 )
    self.assert_( token.isNamespacesEmpty() == True )
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ ns ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLToken_newSetters_setTriple1(self):
    triple = liblx.XMLTriple("test","","")
    token = liblx.XMLToken()
    i = token.setTriple(triple)
    self.assert_( i == liblx.LIBLX_OPERATION_SUCCESS )
    self.assert_((  "test" == token.getName() ))
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLToken_newSetters_setTriple2(self):
    triple = liblx.XMLTriple("test","","")
    token = liblx.XMLToken("This is text")
    i = token.setTriple(triple)
    self.assert_( i == liblx.LIBLX_INVALID_XML_OPERATION )
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    pass  

def suite():
  suite = unittest.TestSuite()
  suite.addTest(unittest.makeSuite(TestXMLToken_newSetters))

  return suite

if __name__ == "__main__":
  if unittest.TextTestRunner(verbosity=1).run(suite()).wasSuccessful() :
    sys.exit(0)
  else:
    sys.exit(1)
