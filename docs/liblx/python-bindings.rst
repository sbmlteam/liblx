python
>>> from liblx import *
>>> test_str = "<annotation>\n" + "  <test xmlns=\"http://test.org/\" id=\"test1\">test2</test>\n" + "</annotation>"
>>> y = XMLNode(test_str)    # I don't know if this is correct.
>>> print(y.toString())
<annotation>
  <test xmlns="http://test.org/" id="test1">test2</test>
</annotation>
>>> n = XMLNode_convertStringToXMLNode(test_str)
>>> n
<liblx.XMLNode; proxy of <Swig Object of type 'XMLNode_t *' at 0x7fe154435240> >
>>> n.toString()
'<annotation>'
>>> n.toString()
'<annotation>'
>>> type(n)
<class 'liblx.XMLNode'>
>>> n.equals(y)
False
>>> n.getNumChildren()
1
>>> c = n.getChild(0)
>>> c
<liblx.XMLNode; proxy of <Swig Object of type 'XMLNode_t *' at 0x7fe1543a9870> >
>>> c.toString()
'<test>'
>>> n.hasAttr()
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
  File "/Users/matthewgillman/repos/libLX/liblx/build/src/bindings/python/liblx.py", line 2801, in hasAttr
    return _liblx.XMLToken_hasAttr(self, *args)
TypeError: Wrong number or type of arguments for overloaded function 'XMLToken_hasAttr'.
  Possible C/C++ prototypes are:
    XMLToken::hasAttr(int) const
    XMLToken::hasAttr(std::string const &,std::string const) const
    XMLToken::hasAttr(std::string const &) const
    XMLToken::hasAttr(XMLTriple const &) const

>>>
>>> type(c)
<class 'liblx.XMLNode'>
>>> type(n)
<class 'liblx.XMLNode'>

>>> c2 = c.getChild(0)
>>> c2
<liblx.XMLNode; proxy of <Swig Object of type 'XMLNode_t *' at 0x7fe1543a9930> >
>>> print(c2)
<liblx.XMLNode; proxy of <Swig Object of type 'XMLNode_t *' at 0x7fe1543a9930> >
>>> c2.toString()
'test2'
>>> c.hasAttr("xmlns")    # not sure this is correct!!    A getNumAttributes() fn would be good. (maybe exists in C++) getAttributesLength'??
False
>>> type(c)
<class 'liblx.XMLNode'>
>>> c.getAttributesLength()
1
>>> c.getAttrValue(0)
'test1'
>>> atts = c.getAttributes()
>>> c2.getNumChildren()
0
>>> c.getAttrName(0)
'id'
>>> ns = c.getNamespaces()
>>> ns.getLength()
1
>>> ns.getURI()
'http://test.org/'
>>> type(n)
<class 'liblx.XMLNode'>
>>> z = n.clone()
>>> z.toString()
'<annotation>'
>>> z.equals(n)
True
>>> z is n
False
>>> z.toXMLString()
'<annotation>\n  <test xmlns="http://test.org/" id="test1">test2</test>\n</annotation>'
>>> cat_str = "<cats></cats>"
>>> catsnode = XMLNode(cat_str)
>>> catsnode.toString()
'<cats></cats>'
>>> n.getNumChildren()
1
>>> n.getNumChildren()
2
>>> n.toString()
'<annotation>'
>>> n.toXMLString()
'<annotation>\n  <test xmlns="http://test.org/" id="test1">test2</test>&lt;cats&gt;&lt;/cats&gt;</annotation>'
>>> catsnode.toString()
'<cats></cats>'
>>> catsnode.toXMLString()
'&lt;cats&gt;&lt;/cats&gt;'

