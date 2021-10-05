==============================================
Building and using the Python version of libLX
==============================================

Introduction
============
LibLX is written in C++ (with a little C).

In order to use it with Python, we use SWIG to generate the "Python binding" files. This is done by using the
`-DWITH_PYTHON=TRUE` option in your CMake build.

For example, assuming you are doing a fresh build in a new /build directory, your CMake command might look a little like
this:

.. code-block:: bash

    cmake -DWITH_PYTHON=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DWITH_CHECK=TRUE -G "Unix Makefiles" /Users/matthewgillman/repos/libLX/liblx/

You should find that, as well as the normal liblx libraries built for your OS, there is now a `liblx.py` file in
the `src/bindings/python` subdirectory. This is basically a Python version of libLX. To use it, you need to have it
in your `PYTHONPATH`, e.g. `export PYTHONPATH=.:src/bindings/python`, assuming you currently have an empty `PYTHONPATH`.

Then, in a Python session, you can say `from liblx import *`.


Typical build on Windows
========================
Assuming the dependencies etc are installed, you should be able to do this, in a normal Windows command prompt:

.. code-block:: bash

    git clone https://github.com/sbmlteam/liblx.git
    cd liblx
    git checkout matt-win-build
    git pull --rebase

    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release -DWITH_PYTHON=ON -DLIBLX_DEPENDENCY_DIR=e:/Development/libSBML-dependencies/install_vs15_release_x64 C:\Users\cceagil\repos\CompBioLibs\liblx
    cmake --build . --config Release

with, of course, your own values for the dependency directory and the build location (final item in long cmake command above).
This example assumes you have installed `cmake` directly, rather than using the version which comes with Visual Studio.


Sample Python Session
=====================

Using an XML fragment like:

.. code-block:: bash

    <annotation>
        <test xmlns="http://test.org/" id="test1">test2</test>
    </annotation>

In this example, the namespace URI is http://test.org, and `id` is an attribute with value "test1".
The elements are `annotation` and `test`. The value of the `test` element is "test2".

You will have to set your python path (either PYTHONPATH env var, or within python session) to pick up the built liblx modules.

.. code-block:: python

    >>> from liblx import *
    >>> test_str = "<annotation>\n" + "  <test xmlns=\"http://test.org/\" id=\"test1\">test2</test>\n" + "</annotation>"
    >>> n = XMLNode_convertStringToXMLNode(test_str)
    >>> n
    <liblx.XMLNode; proxy of <Swig Object of type 'XMLNode_t *' at 0x7fe154435240> >
    >>> n.toString()
    '<annotation>'
    >>> type(n)
    <class 'liblx.XMLNode'>
    >>> n.getNumChildren()
    1
    >>> c = n.getChild(0)
    >>> c
    <liblx.XMLNode; proxy of <Swig Object of type 'XMLNode_t *' at 0x7fe1543a9870> >
    >>> c.toString()
    '<test>'
    >>> type(c)
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


Hopefully this gives some idea of how to use the library.

Matthew S. Gillman
University College London
June 2021.




