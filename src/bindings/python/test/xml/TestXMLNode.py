#
# @file    TestXMLNode.py
# @brief   XMLNode unit tests
#
# @author  Akiya Jouraku (Python conversion)
# @author  Michael Hucka <mhucka@caltech.edu> 
# 
# -----------------------------------------------------------------------------
# This file is part of libLX.  Please visit http://lx.org for more
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
# and also available online as http://libsbml.org/software/liblx/license.html
# -----------------------------------------------------------------------------

import sys
import unittest
import liblx

def wrapString(s):
  return s
  pass


class TestXMLNode(unittest.TestCase):


  def test_XMLNode_attribute_add_remove(self):
    triple = liblx.XMLTriple("test","","")
    attr = liblx.XMLAttributes()
    node = liblx.XMLNode(triple,attr)
    xt1 = liblx.XMLTriple("name1", "http://name1.org/", "p1")
    xt2 = liblx.XMLTriple("name2", "http://name2.org/", "p2")
    xt3 = liblx.XMLTriple("name3", "http://name3.org/", "p3")
    xt1a = liblx.XMLTriple("name1", "http://name1a.org/", "p1a")
    xt2a = liblx.XMLTriple("name2", "http://name2a.org/", "p2a")
    node.addAttr( "name1", "val1", "http://name1.org/", "p1")
    node.addAttr(xt2, "val2")
    self.assert_( node.getAttributesLength() == 2 )
    self.assert_( node.isAttributesEmpty() == False )
    self.assert_( (  "name1" != node.getAttrName(0) ) == False )
    self.assert_( (  "val1"  != node.getAttrValue(0) ) == False )
    self.assert_( (  "http://name1.org/" != node.getAttrURI(0) ) == False )
    self.assert_( (  "p1"    != node.getAttrPrefix(0) ) == False )
    self.assert_( (  "name2" != node.getAttrName(1) ) == False )
    self.assert_( (  "val2"  != node.getAttrValue(1) ) == False )
    self.assert_( (  "http://name2.org/" != node.getAttrURI(1) ) == False )
    self.assert_( (  "p2"    != node.getAttrPrefix(1) ) == False )
    self.assert_( node.getAttrValue( "name1") == "" )
    self.assert_( node.getAttrValue( "name2") == "" )
    self.assert_( (  "val1"  != node.getAttrValue( "name1", "http://name1.org/") ) == False )
    self.assert_( (  "val2"  != node.getAttrValue( "name2", "http://name2.org/") ) == False )
    self.assert_( (  "val1"  != node.getAttrValue(xt1) ) == False )
    self.assert_( (  "val2"  != node.getAttrValue(xt2) ) == False )
    self.assert_( node.hasAttr(-1) == False )
    self.assert_( node.hasAttr(2) == False )
    self.assert_( node.hasAttr(0) == True )
    self.assert_( node.hasAttr( "name1", "http://name1.org/") == True )
    self.assert_( node.hasAttr( "name2", "http://name2.org/") == True )
    self.assert_( node.hasAttr( "name3", "http://name3.org/") == False )
    self.assert_( node.hasAttr(xt1) == True )
    self.assert_( node.hasAttr(xt2) == True )
    self.assert_( node.hasAttr(xt3) == False )
    node.addAttr( "noprefix", "val3")
    self.assert_( node.getAttributesLength() == 3 )
    self.assert_( node.isAttributesEmpty() == False )
    self.assert_( (  "noprefix" != node.getAttrName(2) ) == False )
    self.assert_( (  "val3"     != node.getAttrValue(2) ) == False )
    self.assert_( node.getAttrURI(2) == "" )
    self.assert_( node.getAttrPrefix(2) == "" )
    self.assert_( (      "val3"  != node.getAttrValue( "noprefix") ) == False )
    self.assert_( (  "val3"  != node.getAttrValue( "noprefix", "") ) == False )
    self.assert_( node.hasAttr( "noprefix"    ) == True )
    self.assert_( node.hasAttr( "noprefix", "") == True )
    node.addAttr(xt1, "mval1")
    node.addAttr( "name2", "mval2", "http://name2.org/", "p2")
    self.assert_( node.getAttributesLength() == 3 )
    self.assert_( node.isAttributesEmpty() == False )
    self.assert_( (  "name1" != node.getAttrName(0) ) == False )
    self.assert_( (  "mval1" != node.getAttrValue(0) ) == False )
    self.assert_( (  "http://name1.org/" != node.getAttrURI(0) ) == False )
    self.assert_( (  "p1"    != node.getAttrPrefix(0) ) == False )
    self.assert_( (  "name2"    != node.getAttrName(1) ) == False )
    self.assert_( (  "mval2"    != node.getAttrValue(1) ) == False )
    self.assert_( (  "http://name2.org/" != node.getAttrURI(1) ) == False )
    self.assert_( (  "p2"       != node.getAttrPrefix(1) ) == False )
    self.assert_( node.hasAttr(xt1) == True )
    self.assert_( node.hasAttr( "name1", "http://name1.org/") == True )
    node.addAttr( "noprefix", "mval3")
    self.assert_( node.getAttributesLength() == 3 )
    self.assert_( node.isAttributesEmpty() == False )
    self.assert_( (  "noprefix" != node.getAttrName(2) ) == False )
    self.assert_( (  "mval3"    != node.getAttrValue(2) ) == False )
    self.assert_( node.getAttrURI(2) == "" )
    self.assert_( node.getAttrPrefix(2) == "" )
    self.assert_( node.hasAttr( "noprefix") == True )
    self.assert_( node.hasAttr( "noprefix", "") == True )
    node.addAttr(xt1a, "val1a")
    node.addAttr(xt2a, "val2a")
    self.assert_( node.getAttributesLength() == 5 )
    self.assert_( (  "name1" != node.getAttrName(3) ) == False )
    self.assert_( (  "val1a" != node.getAttrValue(3) ) == False )
    self.assert_( (  "http://name1a.org/" != node.getAttrURI(3) ) == False )
    self.assert_( (  "p1a" != node.getAttrPrefix(3) ) == False )
    self.assert_( (  "name2" != node.getAttrName(4) ) == False )
    self.assert_( (  "val2a" != node.getAttrValue(4) ) == False )
    self.assert_( (  "http://name2a.org/" != node.getAttrURI(4) ) == False )
    self.assert_( (  "p2a" != node.getAttrPrefix(4) ) == False )
    self.assert_( (  "val1a"  != node.getAttrValue( "name1", "http://name1a.org/") ) == False )
    self.assert_( (  "val2a"  != node.getAttrValue( "name2", "http://name2a.org/") ) == False )
    self.assert_( (  "val1a"  != node.getAttrValue(xt1a) ) == False )
    self.assert_( (  "val2a"  != node.getAttrValue(xt2a) ) == False )
    node.removeAttr(xt1a)
    node.removeAttr(xt2a)
    self.assert_( node.getAttributesLength() == 3 )
    node.removeAttr( "name1", "http://name1.org/")
    self.assert_( node.getAttributesLength() == 2 )
    self.assert_( node.isAttributesEmpty() == False )
    self.assert_( (  "name2" != node.getAttrName(0) ) == False )
    self.assert_( (  "mval2" != node.getAttrValue(0) ) == False )
    self.assert_( (  "http://name2.org/" != node.getAttrURI(0) ) == False )
    self.assert_( (  "p2" != node.getAttrPrefix(0) ) == False )
    self.assert_( (  "noprefix" != node.getAttrName(1) ) == False )
    self.assert_( (  "mval3" != node.getAttrValue(1) ) == False )
    self.assert_( node.getAttrURI(1) == "" )
    self.assert_( node.getAttrPrefix(1) == "" )
    self.assert_( node.hasAttr( "name1", "http://name1.org/") == False )
    node.removeAttr(xt2)
    self.assert_( node.getAttributesLength() == 1 )
    self.assert_( node.isAttributesEmpty() == False )
    self.assert_( (  "noprefix" != node.getAttrName(0) ) == False )
    self.assert_( (  "mval3" != node.getAttrValue(0) ) == False )
    self.assert_( node.getAttrURI(0) == "" )
    self.assert_( node.getAttrPrefix(0) == "" )
    self.assert_( node.hasAttr(xt2) == False )
    self.assert_( node.hasAttr( "name2", "http://name2.org/") == False )
    node.removeAttr( "noprefix")
    self.assert_( node.getAttributesLength() == 0 )
    self.assert_( node.isAttributesEmpty() == True )
    self.assert_( node.hasAttr( "noprefix"    ) == False )
    self.assert_( node.hasAttr( "noprefix", "") == False )
    _dummyList = [ node ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ xt1 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ xt2 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ xt3 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ xt1a ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ xt2a ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLNode_attribute_set_clear(self):
    triple = liblx.XMLTriple("test","","")
    attr = liblx.XMLAttributes()
    node = liblx.XMLNode(triple,attr)
    nattr = liblx.XMLAttributes()
    xt1 = liblx.XMLTriple("name1", "http://name1.org/", "p1")
    xt2 = liblx.XMLTriple("name2", "http://name2.org/", "p2")
    xt3 = liblx.XMLTriple("name3", "http://name3.org/", "p3")
    xt4 = liblx.XMLTriple("name4", "http://name4.org/", "p4")
    xt5 = liblx.XMLTriple("name5", "http://name5.org/", "p5")
    nattr.add(xt1, "val1")
    nattr.add(xt2, "val2")
    nattr.add(xt3, "val3")
    nattr.add(xt4, "val4")
    nattr.add(xt5, "val5")
    node.setAttributes(nattr)
    self.assert_( node.getAttributesLength() == 5 )
    self.assert_( node.isAttributesEmpty() == False )
    self.assert_( (  "name1" != node.getAttrName(0) ) == False )
    self.assert_( (  "val1"  != node.getAttrValue(0) ) == False )
    self.assert_( (  "http://name1.org/" != node.getAttrURI(0) ) == False )
    self.assert_( (  "p1"    != node.getAttrPrefix(0) ) == False )
    self.assert_( (  "name2" != node.getAttrName(1) ) == False )
    self.assert_( (  "val2"  != node.getAttrValue(1) ) == False )
    self.assert_( (  "http://name2.org/" != node.getAttrURI(1) ) == False )
    self.assert_( (  "p2"    != node.getAttrPrefix(1) ) == False )
    self.assert_( (  "name3" != node.getAttrName(2) ) == False )
    self.assert_( (  "val3"  != node.getAttrValue(2) ) == False )
    self.assert_( (  "http://name3.org/" != node.getAttrURI(2) ) == False )
    self.assert_( (  "p3"    != node.getAttrPrefix(2) ) == False )
    self.assert_( (  "name4" != node.getAttrName(3) ) == False )
    self.assert_( (  "val4"  != node.getAttrValue(3) ) == False )
    self.assert_( (  "http://name4.org/" != node.getAttrURI(3) ) == False )
    self.assert_( (  "p4"    != node.getAttrPrefix(3) ) == False )
    self.assert_( (  "name5" != node.getAttrName(4) ) == False )
    self.assert_( (  "val5"  != node.getAttrValue(4) ) == False )
    self.assert_( (  "http://name5.org/" != node.getAttrURI(4) ) == False )
    self.assert_( (  "p5"    != node.getAttrPrefix(4) ) == False )
    ntriple = liblx.XMLTriple("test2","http://test2.org/","p2")
    node.setTriple(ntriple)
    self.assert_( (    "test2" != node.getName() ) == False )
    self.assert_( (     "http://test2.org/" != node.getURI() ) == False )
    self.assert_( (  "p2" != node.getPrefix() ) == False )
    node.clearAttributes()
    self.assert_( node.getAttributesLength() == 0 )
    self.assert_( node.isAttributesEmpty() != False )
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ ntriple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ node ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ nattr ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ xt1 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ xt2 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ xt3 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ xt4 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ xt5 ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLNode_convert(self):
    xmlstr = wrapString("<annotation>\n" + "  <test xmlns=\"http://test.org/\" id=\"test\">test</test>\n" + "</annotation>")
    node = liblx.XMLNode.convertStringToXMLNode(xmlstr,None)
    child = node.getChild(0)
    gchild = child.getChild(0)
    attr = child.getAttributes()
    ns = child.getNamespaces()
    self.assert_( (  "annotation" != node.getName() ) == False )
    self.assert_( ( "test"  != child.getName() ) == False )
    self.assert_( ( "test"  != gchild.getCharacters() ) == False )
    self.assert_( (  "id"    != attr.getName(0) ) == False )
    self.assert_( (  "test"  != attr.getValue(0) ) == False )
    self.assert_( (  "http://test.org/"  != ns.getURI(0) ) == False )
    self.assert_( ns.getPrefix(0) == "" )
    toxmlstring = node.toXMLString()
    self.assert_( ( xmlstr != toxmlstring ) == False )
    _dummyList = [ node ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLNode_convert_dummyroot(self):
    xmlstr_nodummy1 = wrapString("<notes>\n" + "  <p>test</p>\n" + "</notes>")
    xmlstr_nodummy2 = wrapString("<html>\n" + "  <p>test</p>\n" + "</html>")
    xmlstr_nodummy3 = wrapString("<body>\n" + "  <p>test</p>\n" + "</body>")
    xmlstr_nodummy4 =  "<p>test</p>";
    xmlstr_nodummy5 = wrapString("<test1>\n" + "  <test2>test</test2>\n" + "</test1>")
    xmlstr_dummy1 =  "<p>test1</p><p>test2</p>";
    xmlstr_dummy2 =  "<test1>test1</test1><test2>test2</test2>";
    rootnode = liblx.XMLNode.convertStringToXMLNode(xmlstr_nodummy1,None)
    self.assert_( rootnode.getNumChildren() == 1 )
    child = rootnode.getChild(0)
    gchild = child.getChild(0)
    self.assert_( (  "notes" != rootnode.getName() ) == False )
    self.assert_( ( "p"  != child.getName() ) == False )
    self.assert_( ( "test"  != gchild.getCharacters() ) == False )
    toxmlstring = rootnode.toXMLString()
    self.assert_( ( xmlstr_nodummy1 != toxmlstring ) == False )
    _dummyList = [ rootnode ]; _dummyList[:] = []; del _dummyList
    rootnode = liblx.XMLNode.convertStringToXMLNode(xmlstr_nodummy2,None)
    self.assert_( rootnode.getNumChildren() == 1 )
    child = rootnode.getChild(0)
    gchild = child.getChild(0)
    self.assert_( (  "html" != rootnode.getName() ) == False )
    self.assert_( ( "p"  != child.getName() ) == False )
    self.assert_( ( "test"  != gchild.getCharacters() ) == False )
    toxmlstring = rootnode.toXMLString()
    self.assert_( ( xmlstr_nodummy2 != toxmlstring ) == False )
    _dummyList = [ rootnode ]; _dummyList[:] = []; del _dummyList
    rootnode = liblx.XMLNode.convertStringToXMLNode(xmlstr_nodummy3,None)
    self.assert_( rootnode.getNumChildren() == 1 )
    child = rootnode.getChild(0)
    gchild = child.getChild(0)
    self.assert_( (  "body" != rootnode.getName() ) == False )
    self.assert_( ( "p"  != child.getName() ) == False )
    self.assert_( ( "test"  != gchild.getCharacters() ) == False )
    toxmlstring = rootnode.toXMLString()
    self.assert_( ( xmlstr_nodummy3 != toxmlstring ) == False )
    _dummyList = [ rootnode ]; _dummyList[:] = []; del _dummyList
    rootnode = liblx.XMLNode.convertStringToXMLNode(xmlstr_nodummy4,None)
    self.assert_( rootnode.getNumChildren() == 1 )
    child = rootnode.getChild(0)
    self.assert_( (  "p" != rootnode.getName() ) == False )
    self.assert_( ( "test"  != child.getCharacters() ) == False )
    toxmlstring = rootnode.toXMLString()
    self.assert_( ( xmlstr_nodummy4 != toxmlstring ) == False )
    _dummyList = [ rootnode ]; _dummyList[:] = []; del _dummyList
    rootnode = liblx.XMLNode.convertStringToXMLNode(xmlstr_nodummy5,None)
    self.assert_( rootnode.getNumChildren() == 1 )
    child = rootnode.getChild(0)
    gchild = child.getChild(0)
    self.assert_( (  "test1" != rootnode.getName() ) == False )
    self.assert_( ( "test2"  != child.getName() ) == False )
    self.assert_( ( "test"  != gchild.getCharacters() ) == False )
    toxmlstring = rootnode.toXMLString()
    self.assert_( ( xmlstr_nodummy5 != toxmlstring ) == False )
    _dummyList = [ rootnode ]; _dummyList[:] = []; del _dummyList
    rootnode = liblx.XMLNode.convertStringToXMLNode(xmlstr_dummy1,None)
    self.assert_( rootnode.isEOF() == True )
    self.assert_( rootnode.getNumChildren() == 2 )
    child = rootnode.getChild(0)
    gchild = child.getChild(0)
    self.assert_( (  "p" != child.getName() ) == False )
    self.assert_( ( "test1"  != gchild.getCharacters() ) == False )
    child = rootnode.getChild(1)
    gchild = child.getChild(0)
    self.assert_( (  "p" != child.getName() ) == False )
    self.assert_( ( "test2"  != gchild.getCharacters() ) == False )
    toxmlstring = rootnode.toXMLString()
    self.assert_( ( xmlstr_dummy1 != toxmlstring ) == False )
    _dummyList = [ rootnode ]; _dummyList[:] = []; del _dummyList
    rootnode = liblx.XMLNode.convertStringToXMLNode(xmlstr_dummy2,None)
    self.assert_( rootnode.isEOF() == True )
    self.assert_( rootnode.getNumChildren() == 2 )
    child = rootnode.getChild(0)
    gchild = child.getChild(0)
    self.assert_( (  "test1" != child.getName() ) == False )
    self.assert_( ( "test1"  != gchild.getCharacters() ) == False )
    child = rootnode.getChild(1)
    gchild = child.getChild(0)
    self.assert_( (  "test2" != child.getName() ) == False )
    self.assert_( ( "test2"  != gchild.getCharacters() ) == False )
    toxmlstring = rootnode.toXMLString()
    self.assert_( ( xmlstr_dummy2 != toxmlstring ) == False )
    _dummyList = [ rootnode ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLNode_create(self):
    node = liblx.XMLNode()
    self.assert_( node != None )
    self.assert_( node.getNumChildren() == 0 )
    _dummyList = [ node ]; _dummyList[:] = []; del _dummyList
    node = liblx.XMLNode()
    self.assert_( node != None )
    node2 = liblx.XMLNode()
    self.assert_( node2 != None )
    node.addChild(node2)
    self.assert_( node.getNumChildren() == 1 )
    node3 = liblx.XMLNode()
    self.assert_( node3 != None )
    node.addChild(node3)
    self.assert_( node.getNumChildren() == 2 )
    _dummyList = [ node ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ node2 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ node3 ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLNode_createElement(self):
    name =  "test";
    uri =  "http://test.org/";
    prefix =  "p";
    text =  "text node";
    triple = liblx.XMLTriple(name,uri,prefix)
    ns = liblx.XMLNamespaces()
    attr = liblx.XMLAttributes()
    ns.add(uri,prefix)
    attr.add("id", "value",uri,prefix)
    snode = liblx.XMLNode(triple,attr,ns)
    self.assert_( snode != None )
    self.assert_( snode.getNumChildren() == 0 )
    self.assert_( ( name != snode.getName() ) == False )
    self.assert_( ( prefix != snode.getPrefix() ) == False )
    self.assert_( ( uri != snode.getURI() ) == False )
    self.assert_( snode.isElement() == True )
    self.assert_( snode.isStart() == True )
    self.assert_( snode.isEnd() == False )
    self.assert_( snode.isText() == False )
    snode.setEnd()
    self.assert_( snode.isEnd() == True )
    snode.unsetEnd()
    self.assert_( snode.isEnd() == False )
    cattr = snode.getAttributes()
    self.assert_( cattr != None )
    self.assert_( (  "id"    != cattr.getName(0) ) == False )
    self.assert_( (  "value" != cattr.getValue(0) ) == False )
    self.assert_( ( prefix != cattr.getPrefix(0) ) == False )
    self.assert_( ( uri != cattr.getURI(0) ) == False )
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ ns ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ snode ]; _dummyList[:] = []; del _dummyList
    attr = liblx.XMLAttributes()
    attr.add("id", "value")
    triple = liblx.XMLTriple(name, "", "")
    snode = liblx.XMLNode(triple,attr)
    self.assert_( snode != None )
    self.assert_( snode.getNumChildren() == 0 )
    self.assert_( (  "test" != snode.getName() ) == False )
    self.assert_( snode.getPrefix() == "" )
    self.assert_( snode.getURI() == "" )
    self.assert_( snode.isElement() == True )
    self.assert_( snode.isStart() == True )
    self.assert_( snode.isEnd() == False )
    self.assert_( snode.isText() == False )
    cattr = snode.getAttributes()
    self.assert_( cattr != None )
    self.assert_( (  "id"    != cattr.getName(0) ) == False )
    self.assert_( (  "value" != cattr.getValue(0) ) == False )
    self.assert_( cattr.getPrefix(0) == "" )
    self.assert_( cattr.getURI(0) == "" )
    enode = liblx.XMLNode(triple)
    self.assert_( enode != None )
    self.assert_( enode.getNumChildren() == 0 )
    self.assert_( (  "test" != enode.getName() ) == False )
    self.assert_( enode.getPrefix() == "" )
    self.assert_( enode.getURI() == "" )
    self.assert_( enode.isElement() == True )
    self.assert_( enode.isStart() == False )
    self.assert_( enode.isEnd() == True )
    self.assert_( enode.isText() == False )
    tnode = liblx.XMLNode(text)
    self.assert_( tnode != None )
    self.assert_( ( text != tnode.getCharacters() ) == False )
    self.assert_( tnode.getNumChildren() == 0 )
    self.assert_( tnode.getName() == "" )
    self.assert_( tnode.getPrefix() == "" )
    self.assert_( tnode.getURI() == "" )
    self.assert_( tnode.isElement() == False )
    self.assert_( tnode.isStart() == False )
    self.assert_( tnode.isEnd() == False )
    self.assert_( tnode.isText() == True )
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ snode ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ enode ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ tnode ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLNode_createFromToken(self):
    triple = liblx.XMLTriple("attr", "uri", "prefix")
    token = liblx.XMLToken(triple)
    node = liblx.XMLNode(token)
    self.assert_( node != None )
    self.assert_( node.getNumChildren() == 0 )
    self.assert_( (  "attr" != node.getName() ) == False )
    self.assert_( (  "prefix" != node.getPrefix() ) == False )
    self.assert_( (  "uri" != node.getURI() ) == False )
    self.assert_( node.getChild(1) != None )
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ node ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLNode_getters(self):
    NS = liblx.XMLNamespaces()
    NS.add( "http://test1.org/", "test1")
    token = liblx.XMLToken("This is a test")
    node = liblx.XMLNode(token)
    self.assert_( node != None )
    self.assert_( node.getNumChildren() == 0 )
    self.assert_( (  "This is a test" != node.getCharacters() ) == False )
    self.assert_( node.getChild(1) != None )
    attr = liblx.XMLAttributes()
    self.assert_( attr != None )
    attr.add( "attr2", "value")
    triple = liblx.XMLTriple("attr", "uri", "prefix")
    token = liblx.XMLToken(triple,attr)
    self.assert_( token != None )
    node = liblx.XMLNode(token)
    self.assert_( (  "attr" != node.getName() ) == False )
    self.assert_( (  "uri" != node.getURI() ) == False )
    self.assert_( (  "prefix" != node.getPrefix() ) == False )
    returnattr = node.getAttributes()
    self.assert_( (  "attr2" != returnattr.getName(0) ) == False )
    self.assert_( (  "value" != returnattr.getValue(0) ) == False )
    token = liblx.XMLToken(triple,attr,NS)
    node = liblx.XMLNode(token)
    returnNS = node.getNamespaces()
    self.assert_( returnNS.getLength() == 1 )
    self.assert_( returnNS.isEmpty() == False )
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ token ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ node ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLNode_insert(self):
    attr = liblx.XMLAttributes()
    trp_p = liblx.XMLTriple("parent","","")
    trp_c1 = liblx.XMLTriple("child1","","")
    trp_c2 = liblx.XMLTriple("child2","","")
    trp_c3 = liblx.XMLTriple("child3","","")
    trp_c4 = liblx.XMLTriple("child4","","")
    trp_c5 = liblx.XMLTriple("child5","","")
    p = liblx.XMLNode(trp_p,attr)
    c1 = liblx.XMLNode(trp_c1,attr)
    c2 = liblx.XMLNode(trp_c2,attr)
    c3 = liblx.XMLNode(trp_c3,attr)
    c4 = liblx.XMLNode(trp_c4,attr)
    c5 = liblx.XMLNode(trp_c5,attr)
    p.addChild(c2)
    p.addChild(c4)
    p.insertChild(0,c1)
    p.insertChild(2,c3)
    p.insertChild(4,c5)
    self.assert_( p.getNumChildren() == 5 )
    self.assert_( (  "child1" != p.getChild(0).getName() ) == False )
    self.assert_( (  "child2" != p.getChild(1).getName() ) == False )
    self.assert_( (  "child3" != p.getChild(2).getName() ) == False )
    self.assert_( (  "child4" != p.getChild(3).getName() ) == False )
    self.assert_( (  "child5" != p.getChild(4).getName() ) == False )
    p.removeChildren()
    p.insertChild(0,c1)
    p.insertChild(0,c2)
    p.insertChild(0,c3)
    p.insertChild(0,c4)
    p.insertChild(0,c5)
    self.assert_( p.getNumChildren() == 5 )
    self.assert_( (  "child5" != p.getChild(0).getName() ) == False )
    self.assert_( (  "child4" != p.getChild(1).getName() ) == False )
    self.assert_( (  "child3" != p.getChild(2).getName() ) == False )
    self.assert_( (  "child2" != p.getChild(3).getName() ) == False )
    self.assert_( (  "child1" != p.getChild(4).getName() ) == False )
    p.removeChildren()
    p.insertChild(1,c1)
    p.insertChild(2,c2)
    p.insertChild(3,c3)
    p.insertChild(4,c4)
    p.insertChild(5,c5)
    self.assert_( p.getNumChildren() == 5 )
    self.assert_( (  "child1" != p.getChild(0).getName() ) == False )
    self.assert_( (  "child2" != p.getChild(1).getName() ) == False )
    self.assert_( (  "child3" != p.getChild(2).getName() ) == False )
    self.assert_( (  "child4" != p.getChild(3).getName() ) == False )
    self.assert_( (  "child5" != p.getChild(4).getName() ) == False )
    p.removeChildren()
    tmp = p.insertChild(0,c1)
    self.assert_( ( "child1" != tmp.getName() ) == False )
    tmp = p.insertChild(0,c2)
    self.assert_( ( "child2" != tmp.getName() ) == False )
    tmp = p.insertChild(0,c3)
    self.assert_( ( "child3" != tmp.getName() ) == False )
    tmp = p.insertChild(0,c4)
    self.assert_( ( "child4" != tmp.getName() ) == False )
    tmp = p.insertChild(0,c5)
    self.assert_( ( "child5" != tmp.getName() ) == False )
    p.removeChildren()
    tmp = p.insertChild(1,c1)
    self.assert_( ( "child1" != tmp.getName() ) == False )
    tmp = p.insertChild(2,c2)
    self.assert_( ( "child2" != tmp.getName() ) == False )
    tmp = p.insertChild(3,c3)
    self.assert_( ( "child3" != tmp.getName() ) == False )
    tmp = p.insertChild(4,c4)
    self.assert_( ( "child4" != tmp.getName() ) == False )
    tmp = p.insertChild(5,c5)
    self.assert_( ( "child5" != tmp.getName() ) == False )
    _dummyList = [ p ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ c1 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ c2 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ c3 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ c4 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ c5 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ trp_p ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ trp_c1 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ trp_c2 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ trp_c3 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ trp_c4 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ trp_c5 ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLNode_namespace_add(self):
    triple = liblx.XMLTriple("test","","")
    attr = liblx.XMLAttributes()
    node = liblx.XMLNode(triple,attr)
    self.assert_( node.getNamespacesLength() == 0 )
    self.assert_( node.isNamespacesEmpty() == True )
    node.addNamespace( "http://test1.org/", "test1")
    self.assert_( node.getNamespacesLength() == 1 )
    self.assert_( node.isNamespacesEmpty() == False )
    node.addNamespace( "http://test2.org/", "test2")
    self.assert_( node.getNamespacesLength() == 2 )
    self.assert_( node.isNamespacesEmpty() == False )
    node.addNamespace( "http://test1.org/", "test1a")
    self.assert_( node.getNamespacesLength() == 3 )
    self.assert_( node.isNamespacesEmpty() == False )
    node.addNamespace( "http://test1.org/", "test1a")
    self.assert_( node.getNamespacesLength() == 3 )
    self.assert_( node.isNamespacesEmpty() == False )
    self.assert_( (node.getNamespaceIndex( "http://test1.org/") == -1) == False )
    _dummyList = [ node ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLNode_namespace_get(self):
    triple = liblx.XMLTriple("test","","")
    attr = liblx.XMLAttributes()
    node = liblx.XMLNode(triple,attr)
    node.addNamespace( "http://test1.org/", "test1")
    node.addNamespace( "http://test2.org/", "test2")
    node.addNamespace( "http://test3.org/", "test3")
    node.addNamespace( "http://test4.org/", "test4")
    node.addNamespace( "http://test5.org/", "test5")
    node.addNamespace( "http://test6.org/", "test6")
    node.addNamespace( "http://test7.org/", "test7")
    node.addNamespace( "http://test8.org/", "test8")
    node.addNamespace( "http://test9.org/", "test9")
    self.assert_( node.getNamespacesLength() == 9 )
    self.assert_( node.getNamespaceIndex( "http://test1.org/") == 0 )
    self.assert_( (  "test2" != node.getNamespacePrefix(1) ) == False )
    self.assert_( ( 		      "test1" != node.getNamespacePrefix( "http://test1.org/") ) == False )
    self.assert_( (  "http://test2.org/" != node.getNamespaceURI(1) ) == False )
    self.assert_( ( 		      "http://test2.org/" != node.getNamespaceURI( "test2") ) == False )
    self.assert_( node.getNamespaceIndex( "http://test1.org/") == 0 )
    self.assert_( node.getNamespaceIndex( "http://test2.org/") == 1 )
    self.assert_( node.getNamespaceIndex( "http://test5.org/") == 4 )
    self.assert_( node.getNamespaceIndex( "http://test9.org/") == 8 )
    self.assert_( node.getNamespaceIndex( "http://testX.org/") == -1 )
    self.assert_( node.hasNamespaceURI( "http://test1.org/") != False )
    self.assert_( node.hasNamespaceURI( "http://test2.org/") != False )
    self.assert_( node.hasNamespaceURI( "http://test5.org/") != False )
    self.assert_( node.hasNamespaceURI( "http://test9.org/") != False )
    self.assert_( node.hasNamespaceURI( "http://testX.org/") == False )
    self.assert_( node.getNamespaceIndexByPrefix( "test1") == 0 )
    self.assert_( node.getNamespaceIndexByPrefix( "test5") == 4 )
    self.assert_( node.getNamespaceIndexByPrefix( "test9") == 8 )
    self.assert_( node.getNamespaceIndexByPrefix( "testX") == -1 )
    self.assert_( node.hasNamespacePrefix( "test1") != False )
    self.assert_( node.hasNamespacePrefix( "test5") != False )
    self.assert_( node.hasNamespacePrefix( "test9") != False )
    self.assert_( node.hasNamespacePrefix( "testX") == False )
    self.assert_( node.hasNamespaceNS( "http://test1.org/", "test1") != False )
    self.assert_( node.hasNamespaceNS( "http://test5.org/", "test5") != False )
    self.assert_( node.hasNamespaceNS( "http://test9.org/", "test9") != False )
    self.assert_( node.hasNamespaceNS( "http://testX.org/", "testX") == False )
    _dummyList = [ node ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLNode_namespace_remove(self):
    triple = liblx.XMLTriple("test","","")
    attr = liblx.XMLAttributes()
    node = liblx.XMLNode(triple,attr)
    node.addNamespace( "http://test1.org/", "test1")
    node.addNamespace( "http://test2.org/", "test2")
    node.addNamespace( "http://test3.org/", "test3")
    node.addNamespace( "http://test4.org/", "test4")
    node.addNamespace( "http://test5.org/", "test5")
    self.assert_( node.getNamespacesLength() == 5 )
    node.removeNamespace(4)
    self.assert_( node.getNamespacesLength() == 4 )
    node.removeNamespace(3)
    self.assert_( node.getNamespacesLength() == 3 )
    node.removeNamespace(2)
    self.assert_( node.getNamespacesLength() == 2 )
    node.removeNamespace(1)
    self.assert_( node.getNamespacesLength() == 1 )
    node.removeNamespace(0)
    self.assert_( node.getNamespacesLength() == 0 )
    node.addNamespace( "http://test1.org/", "test1")
    node.addNamespace( "http://test2.org/", "test2")
    node.addNamespace( "http://test3.org/", "test3")
    node.addNamespace( "http://test4.org/", "test4")
    node.addNamespace( "http://test5.org/", "test5")
    self.assert_( node.getNamespacesLength() == 5 )
    node.removeNamespace(0)
    self.assert_( node.getNamespacesLength() == 4 )
    node.removeNamespace(0)
    self.assert_( node.getNamespacesLength() == 3 )
    node.removeNamespace(0)
    self.assert_( node.getNamespacesLength() == 2 )
    node.removeNamespace(0)
    self.assert_( node.getNamespacesLength() == 1 )
    node.removeNamespace(0)
    self.assert_( node.getNamespacesLength() == 0 )
    _dummyList = [ node ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLNode_namespace_remove_by_prefix(self):
    triple = liblx.XMLTriple("test","","")
    attr = liblx.XMLAttributes()
    node = liblx.XMLNode(triple,attr)
    node.addNamespace( "http://test1.org/", "test1")
    node.addNamespace( "http://test2.org/", "test2")
    node.addNamespace( "http://test3.org/", "test3")
    node.addNamespace( "http://test4.org/", "test4")
    node.addNamespace( "http://test5.org/", "test5")
    self.assert_( node.getNamespacesLength() == 5 )
    node.removeNamespace( "test1")
    self.assert_( node.getNamespacesLength() == 4 )
    node.removeNamespace( "test2")
    self.assert_( node.getNamespacesLength() == 3 )
    node.removeNamespace( "test3")
    self.assert_( node.getNamespacesLength() == 2 )
    node.removeNamespace( "test4")
    self.assert_( node.getNamespacesLength() == 1 )
    node.removeNamespace( "test5")
    self.assert_( node.getNamespacesLength() == 0 )
    node.addNamespace( "http://test1.org/", "test1")
    node.addNamespace( "http://test2.org/", "test2")
    node.addNamespace( "http://test3.org/", "test3")
    node.addNamespace( "http://test4.org/", "test4")
    node.addNamespace( "http://test5.org/", "test5")
    self.assert_( node.getNamespacesLength() == 5 )
    node.removeNamespace( "test5")
    self.assert_( node.getNamespacesLength() == 4 )
    node.removeNamespace( "test4")
    self.assert_( node.getNamespacesLength() == 3 )
    node.removeNamespace( "test3")
    self.assert_( node.getNamespacesLength() == 2 )
    node.removeNamespace( "test2")
    self.assert_( node.getNamespacesLength() == 1 )
    node.removeNamespace( "test1")
    self.assert_( node.getNamespacesLength() == 0 )
    node.addNamespace( "http://test1.org/", "test1")
    node.addNamespace( "http://test2.org/", "test2")
    node.addNamespace( "http://test3.org/", "test3")
    node.addNamespace( "http://test4.org/", "test4")
    node.addNamespace( "http://test5.org/", "test5")
    self.assert_( node.getNamespacesLength() == 5 )
    node.removeNamespace( "test3")
    self.assert_( node.getNamespacesLength() == 4 )
    node.removeNamespace( "test1")
    self.assert_( node.getNamespacesLength() == 3 )
    node.removeNamespace( "test4")
    self.assert_( node.getNamespacesLength() == 2 )
    node.removeNamespace( "test5")
    self.assert_( node.getNamespacesLength() == 1 )
    node.removeNamespace( "test2")
    self.assert_( node.getNamespacesLength() == 0 )
    _dummyList = [ node ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLNode_namespace_set_clear(self):
    triple = liblx.XMLTriple("test","","")
    attr = liblx.XMLAttributes()
    node = liblx.XMLNode(triple,attr)
    ns = liblx.XMLNamespaces()
    self.assert_( node.getNamespacesLength() == 0 )
    self.assert_( node.isNamespacesEmpty() == True )
    ns.add( "http://test1.org/", "test1")
    ns.add( "http://test2.org/", "test2")
    ns.add( "http://test3.org/", "test3")
    ns.add( "http://test4.org/", "test4")
    ns.add( "http://test5.org/", "test5")
    node.setNamespaces(ns)
    self.assert_( node.getNamespacesLength() == 5 )
    self.assert_( node.isNamespacesEmpty() == False )
    self.assert_( (  "test1" != node.getNamespacePrefix(0) ) == False )
    self.assert_( (  "test2" != node.getNamespacePrefix(1) ) == False )
    self.assert_( (  "test3" != node.getNamespacePrefix(2) ) == False )
    self.assert_( (  "test4" != node.getNamespacePrefix(3) ) == False )
    self.assert_( (  "test5" != node.getNamespacePrefix(4) ) == False )
    self.assert_( (  "http://test1.org/" != node.getNamespaceURI(0) ) == False )
    self.assert_( (  "http://test2.org/" != node.getNamespaceURI(1) ) == False )
    self.assert_( (  "http://test3.org/" != node.getNamespaceURI(2) ) == False )
    self.assert_( (  "http://test4.org/" != node.getNamespaceURI(3) ) == False )
    self.assert_( (  "http://test5.org/" != node.getNamespaceURI(4) ) == False )
    node.clearNamespaces()
    self.assert_( node.getNamespacesLength() == 0 )
    self.assert_( node.isAttributesEmpty() != False )
    _dummyList = [ ns ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ node ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ triple ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    pass  

  def test_XMLNode_remove(self):
    attr = liblx.XMLAttributes()
    trp_p = liblx.XMLTriple("parent","","")
    trp_c1 = liblx.XMLTriple("child1","","")
    trp_c2 = liblx.XMLTriple("child2","","")
    trp_c3 = liblx.XMLTriple("child3","","")
    trp_c4 = liblx.XMLTriple("child4","","")
    trp_c5 = liblx.XMLTriple("child5","","")
    p = liblx.XMLNode(trp_p,attr)
    c1 = liblx.XMLNode(trp_c1,attr)
    c2 = liblx.XMLNode(trp_c2,attr)
    c3 = liblx.XMLNode(trp_c3,attr)
    c4 = liblx.XMLNode(trp_c4,attr)
    c5 = liblx.XMLNode(trp_c5,attr)
    p.addChild(c1)
    p.addChild(c2)
    p.addChild(c3)
    p.addChild(c4)
    p.addChild(c5)
    r = p.removeChild(5)
    self.assert_( r == None )
    r = p.removeChild(1)
    self.assert_( p.getNumChildren() == 4 )
    self.assert_( ( "child2" != r.getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    r = p.removeChild(3)
    self.assert_( p.getNumChildren() == 3 )
    self.assert_( ( "child5" != r.getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    r = p.removeChild(0)
    self.assert_( p.getNumChildren() == 2 )
    self.assert_( ( "child1" != r.getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    r = p.removeChild(1)
    self.assert_( p.getNumChildren() == 1 )
    self.assert_( ( "child4" != r.getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    r = p.removeChild(0)
    self.assert_( p.getNumChildren() == 0 )
    self.assert_( ( "child3" != r.getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    p.addChild(c1)
    p.addChild(c2)
    p.addChild(c3)
    p.addChild(c4)
    p.addChild(c5)
    r = p.removeChild(4)
    self.assert_( p.getNumChildren() == 4 )
    self.assert_( ( "child5" != r.getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    r = p.removeChild(3)
    self.assert_( p.getNumChildren() == 3 )
    self.assert_( ( "child4" != r.getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    r = p.removeChild(2)
    self.assert_( p.getNumChildren() == 2 )
    self.assert_( ( "child3" != r.getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    r = p.removeChild(1)
    self.assert_( p.getNumChildren() == 1 )
    self.assert_( ( "child2" != r.getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    r = p.removeChild(0)
    self.assert_( p.getNumChildren() == 0 )
    self.assert_( ( "child1" != r.getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    p.addChild(c1)
    p.addChild(c2)
    p.addChild(c3)
    p.addChild(c4)
    p.addChild(c5)
    r = p.removeChild(0)
    self.assert_( p.getNumChildren() == 4 )
    self.assert_( ( "child1" != r.getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    r = p.removeChild(0)
    self.assert_( p.getNumChildren() == 3 )
    self.assert_( ( "child2" != r.getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    r = p.removeChild(0)
    self.assert_( p.getNumChildren() == 2 )
    self.assert_( ( "child3" != r.getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    r = p.removeChild(0)
    self.assert_( p.getNumChildren() == 1 )
    self.assert_( ( "child4" != r.getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    r = p.removeChild(0)
    self.assert_( p.getNumChildren() == 0 )
    self.assert_( ( "child5" != r.getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    p.addChild(c1)
    p.addChild(c2)
    p.addChild(c3)
    p.addChild(c4)
    p.addChild(c5)
    r = p.removeChild(0)
    self.assert_( ( "child1" != r.getName() ) == False )
    p.insertChild(0,r)
    self.assert_( p.getNumChildren() == 5 )
    self.assert_( ( "child1" != p.getChild(0).getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    r = p.removeChild(1)
    self.assert_( ( "child2" != r.getName() ) == False )
    p.insertChild(1,r)
    self.assert_( p.getNumChildren() == 5 )
    self.assert_( ( "child2" != p.getChild(1).getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    r = p.removeChild(2)
    self.assert_( ( "child3" != r.getName() ) == False )
    p.insertChild(2,r)
    self.assert_( p.getNumChildren() == 5 )
    self.assert_( ( "child3" != p.getChild(2).getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    r = p.removeChild(3)
    self.assert_( ( "child4" != r.getName() ) == False )
    p.insertChild(3,r)
    self.assert_( p.getNumChildren() == 5 )
    self.assert_( ( "child4" != p.getChild(3).getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    r = p.removeChild(4)
    self.assert_( ( "child5" != r.getName() ) == False )
    p.insertChild(4,r)
    self.assert_( p.getNumChildren() == 5 )
    self.assert_( ( "child5" != p.getChild(4).getName() ) == False )
    _dummyList = [ r ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ p ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ c1 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ c2 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ c3 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ c4 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ c5 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ attr ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ trp_p ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ trp_c1 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ trp_c2 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ trp_c3 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ trp_c4 ]; _dummyList[:] = []; del _dummyList
    _dummyList = [ trp_c5 ]; _dummyList[:] = []; del _dummyList
    pass  

def suite():
  suite = unittest.TestSuite()
  suite.addTest(unittest.makeSuite(TestXMLNode))

  return suite

if __name__ == "__main__":
  if unittest.TextTestRunner(verbosity=1).run(suite()).wasSuccessful() :
    sys.exit(0)
  else:
    sys.exit(1)

