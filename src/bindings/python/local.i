/**
 * @file    local-normal.i
 * @brief   Python-specific SWIG directives for wrapping libLX API
 * @author  Ben Bornstein
 * @author  Ben Kovitz
 * @author  Akiya Jouraku
 *
 *<!---------------------------------------------------------------------------
 * This file is part of libLX.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libLX.
 *
 * Copyright (C) 2020 jointly by the following organizations:
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. University of Heidelberg, Heidelberg, Germany
 *     3. University College London, London, UK
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
 *----------------------------------------------------------------------- -->*/


/**
 * Turn on (minimal) Python docstrings and then append our own.
 */
%feature("autodoc", "1");
%include "pydoc.i"

// There is a copy of the below as libsbml/src/bindings/python/local-contrib.i
//%include "local-contrib.i"


/**
 *  Wraps std::cout, std::cerr, std::clog, std::ostream, and std::ostringstream,
 *
 * (sample code) -----------------------------------------------------
 *
 * 1. wraps std::cout
 *
 *    xos = liblx.XMLOutputStream(liblx.cout)
 *
 * 2. wraps std::cerr
 *
 *    d = liblx.readLX("foo.xml")
 *    if d.getNumErrors() > 0 :
 *       d.printErrors(liblx.cerr)
 *
 *
 * 3. wraps std::ostringstream
 *
 *    oss = liblx.ostringstream()
 *    xos = liblx.XMLOutputStream(oss)
 *    ...
 *    liblx.endl(oss)
 *    s = oss.str()
 *
 */

// ignores C++ specific methods in std::string.
%ignore std::basic_string<char>::begin;
%ignore std::basic_string<char>::end;
%ignore std::basic_string<char>::rbegin;
%ignore std::basic_string<char>::rend;
%ignore std::basic_string<char>::get_allocator;
%ignore std::basic_string<char>::capacity;
%ignore std::basic_string<char>::reserve;

%include <std_alloc.i>
%include <std_basic_string.i>
%include <std_string.i>

#pragma SWIG nowarn=509
%warnfilter(401) basic_ios<char>;

namespace std
{
  // Template class basic ios
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
  class basic_ios : public ios_base {};

  // Template class basic_ostream
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
  class basic_ostream : virtual public basic_ios<_CharT, _Traits>
  {
    public:
      explicit
      basic_ostream(std::basic_streambuf<_CharT, _Traits>* __sb);
      virtual
      ~basic_ostream();
  };

  // Template class basic_ostringstream
  template<typename _CharT, typename _Traits = char_traits<_CharT>,
           typename _Alloc = allocator<_CharT> >
  class basic_ostringstream : public basic_ostream<_CharT, _Traits>
  {
    public:
      explicit
      basic_ostringstream(std::ios_base::openmode __mode = std::ios_base::out);
      ~basic_ostringstream();

      basic_string<_CharT, _Traits, _Alloc>
      str() const;

      void
      str(const basic_string<_CharT, _Traits, _Alloc>& __s);
  };


  /**
   * Insert a newline character into the given C++ stream.
   *
   * This is a wrapper around the underlying C++ OStream method
   * <code>endl</code>.  It inserts a newline into the stream
   * passed as argument.  Additionally, it flushes buffered
   * streams.
   */
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
  basic_ostream<_CharT, _Traits>&
  endl(basic_ostream<_CharT, _Traits>&);


  /**
   * Flush the given C++ stream.
   *
   * This is a wrapper around the underlying C++ OStream method
   * <code>flush</code>.  It flush any pending output in the stream
   * passed as argument.
   */
  template<typename _CharT, typename _Traits = char_traits<_CharT> >
  basic_ostream<_CharT, _Traits>&
  flush(basic_ostream<_CharT, _Traits>&);
}

namespace std
{
  /**
   *  std::ostream and std::ostringstream
   *  (std::ios is not wrapped)
   */
  typedef basic_ios<char>           ios;
  typedef basic_ostream<char>       ostream ;
  typedef basic_ostringstream<char> ostringstream ;

  %template()              basic_ios<char>;
  %template(ostream)       basic_ostream<char>;
  %template(ostringstream) basic_ostringstream<char>;

  /**
   *  output manipulators
   */
  %template(endl)  endl<char, char_traits<char> >;
  %template(flush) flush<char, char_traits<char> >;

  /**
   *  std::cout, std::cerr, and std::clog.
   */
  %immutable;
  extern std::ostream cout;
  extern std::ostream cerr;
  extern std::ostream clog;
  %mutable;
}


/**
 * Convert an SBase object to a string.
 *
%extend SBase
{
  %pythoncode
  {
    def __str__(self):
      """
      Return a string representation of this object.

      Note that the string will not be a complete LX document.
      """

      return self.toLX()
  }
}*/


/**
 * Allows ListOf objects:
 *
 *   - To be indexed and sliced, e.g. lst[0].
 */
/*
%extend ListOf
{
  int __len__()
  {
    return self->size();
  }

  %pythoncode
  {
    def __getitem__(self, key):

      try:
         keyIsSlice = isinstance(key, slice)
      except:
         keyIsSlice = 0

      if keyIsSlice:
        start = key.start
        if start is None:
          start = 0
        stop = key.stop
        if stop is None:
          stop = self.size()
        return [self[i] for i in range(
          self._fixNegativeIndex(start), self._fixNegativeIndex(stop)
        )]

      key = self._fixNegativeIndex(key)
      if key < 0 or key >= self.size():
        raise IndexError(key)
      return self.get(key)


    def _fixNegativeIndex(self, index):
      if index < 0:
        return index + self.size()
      else:
        return index


    def __iter__(self):
      for i in range(self.size()):
        yield self[i]


    def __repr__(self):
      return "[" + ", ".join([repr(self[i]) for i in range(len(self))]) + "]"


    def __str__(self):
      return repr(self)
  }
}
*/


/**
 * Convert SBase, SimpleSpeciesReference and Rule objects into the most specific type possible.
 */
 /*
%typemap(out) SBase*, SimpleSpeciesReference*, Rule*, SBasePlugin*, LXExtension*, LXNamespaces*, LXConverter*, Reaction*
{
  $result = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigType($1),
                               $owner | %newpointer_flags);
}
*/
%typemap(out) ASTBasePlugin*
{
  $result = SWIG_NewPointerObj(SWIG_as_voidptr($1), GetDowncastSwigType($1),
                               $owner | %newpointer_flags);
}

/*
 * SWIG-generated wrapper code wrongly invokes
 * XMLOutputStream::writeAttribute(.., const unsigned int& value) instead of
 * XMLOutputStream::writeAttribute(.., const bool& value) even if the writeAttribute
 * function invoked with a bool value (True or False) in Python code.
 * It seems that a bool value could be casted to unsigned int, int, or long value
 * in SWIG-generated internal type check code when these types are overloaded in the
 * wrapped function.
 *
 * To avoid this problem, XMLOutputStream::writeAttribute(.., const bool& value)
 * is internally wrapped as XMLOutputStream::writeAttributeBool(.., const bool&)
 * and this function is properly invoked when the writeAttribute function is invoked
 * with a bool value in Python code.
 */

%feature("docstring") XMLOutputStream::writeAttributeBool "@internal";

%extend XMLOutputStream
{
  void writeAttributeBool(const std::string& name, const bool& value)
  {
    $self->writeAttribute(name, value);
  }

  void writeAttributeBool(const XMLTriple& name, const bool& value)
  {
    $self->writeAttribute(name, value);
  }
}

#if SWIG_VERSION > 0x010336
%feature("pythonprepend")
XMLOutputStream::writeAttribute
%{
        if type(args[1]) == type(True): return _liblx.XMLOutputStream_writeAttributeBool(self, *args)
%}
#else
%feature("pythonprepend")
XMLOutputStream::writeAttribute
%{
        if type(args[2]) == type(True): return _liblx.XMLOutputStream_writeAttributeBool(*args)
%}
#endif

/**
 * Add an equality operator to SBase.  All subclasses of SBase
 * will inherit this method.
 *
 * The %extend rewrites __cmp__ such that two objects of
 * disimilar type can be compared without throwing a TypeError.  For
 * example: the following will return false and not throw an exception:
 *
 *   c = liblx.Compartment()
 *   n = 5
 *   c == n
 *
 * For more information, see testEquality() in test/TestPython.py
 */

%define SWIGPYTHON__CMP__(CLASS)
%extend CLASS
{
  %pythoncode
  {
    def __eq__(self, rhs):
      if ((self is None) and (rhs is None)): return True
      if ((self is None) or  (rhs is None)): return False
      if (hasattr(self, 'this') and hasattr(rhs, 'this')):
        if (self.this == rhs.this): return True
      return False

    def __ne__(self, rhs):
      if ((self is None) and (rhs is None)): return False
      if ((self is None) or  (rhs is None)): return True
      if (hasattr(self, 'this') and hasattr(rhs, 'this')):
        if (self.this == rhs.this): return False
      return True
  }
}
%enddef

//SWIGPYTHON__CMP__(SBase)
//SWIGPYTHON__CMP__(SBasePlugin)
/*
SWIGPYTHON__CMP__(LXExtension)
SWIGPYTHON__CMP__(LXWriter)
SWIGPYTHON__CMP__(LXReader)
*/
//SWIGPYTHON__CMP__(ASTNode)
//SWIGPYTHON__CMP__(CVTerm)
//SWIGPYTHON__CMP__(Date)
//SWIGPYTHON__CMP__(ModelHistory)
//SWIGPYTHON__CMP__(ModelCreator)
SWIGPYTHON__CMP__(XMLNamespaces)
//SWIGPYTHON__CMP__(LXNamespaces)
SWIGPYTHON__CMP__(XMLAttributes)
SWIGPYTHON__CMP__(XMLToken)
SWIGPYTHON__CMP__(XMLTriple)
SWIGPYTHON__CMP__(XMLError)
SWIGPYTHON__CMP__(XMLErrorLog)
SWIGPYTHON__CMP__(XMLOutputStream)


/**
 *
 * Wraps the LXConstructorException class (C++ exception defined by libLX)
 * as the ValueError class (Python built-in exception).
 *
 * For example, the exception can be catched in Python code as follows:
 *
 * --------------------------------------
 *  try:
 *    s = liblx.CompartmentType(level,version)
 *  except ValueError, inst:
 *    errmsg = inst.args[0]
 * --------------------------------------
 */

%ignore LXConstructorException;


%define LXCONSTRUCTOR_EXCEPTION(SBASE_CLASS_NAME)
%exception SBASE_CLASS_NAME {
  try {
    $action
  }
  catch (XMLConstructorException &e) {
    PyErr_SetString(PyExc_ValueError, const_cast<char*>(e.what()));
    return NULL;
  }
  //catch (XMLExtensionException &e) {
  //  PyErr_SetString(PyExc_ValueError, const_cast<char*>(e.what()));
  //  return NULL;
  //}
}
%enddef

/*
LXCONSTRUCTOR_EXCEPTION(Compartment)
LXCONSTRUCTOR_EXCEPTION(CompartmentType)
LXCONSTRUCTOR_EXCEPTION(Constraint)
LXCONSTRUCTOR_EXCEPTION(Delay)
LXCONSTRUCTOR_EXCEPTION(Event)
LXCONSTRUCTOR_EXCEPTION(EventAssignment)
LXCONSTRUCTOR_EXCEPTION(FunctionDefinition)
LXCONSTRUCTOR_EXCEPTION(InitialAssignment)
LXCONSTRUCTOR_EXCEPTION(KineticLaw)
LXCONSTRUCTOR_EXCEPTION(Model)
LXCONSTRUCTOR_EXCEPTION(Parameter)
LXCONSTRUCTOR_EXCEPTION(Priority)
LXCONSTRUCTOR_EXCEPTION(LocalParameter)
LXCONSTRUCTOR_EXCEPTION(Reaction)
LXCONSTRUCTOR_EXCEPTION(AssignmentRule)
LXCONSTRUCTOR_EXCEPTION(AlgebraicRule)
LXCONSTRUCTOR_EXCEPTION(RateRule)
LXCONSTRUCTOR_EXCEPTION(Species)
LXCONSTRUCTOR_EXCEPTION(SpeciesReference)
LXCONSTRUCTOR_EXCEPTION(ModifierSpeciesReference)
LXCONSTRUCTOR_EXCEPTION(SpeciesType)
LXCONSTRUCTOR_EXCEPTION(StoichiometryMath)
LXCONSTRUCTOR_EXCEPTION(Trigger)
LXCONSTRUCTOR_EXCEPTION(Unit)
LXCONSTRUCTOR_EXCEPTION(UnitDefinition)
LXCONSTRUCTOR_EXCEPTION(LXDocument)
*/
LXCONSTRUCTOR_EXCEPTION(XMLNamespaces)
LXCONSTRUCTOR_EXCEPTION(XMLExtensionNamespaces)
/*
LXCONSTRUCTOR_EXCEPTION(ListOf)
LXCONSTRUCTOR_EXCEPTION(ListOfCompartments)
LXCONSTRUCTOR_EXCEPTION(ListOfCompartmentTypes)
LXCONSTRUCTOR_EXCEPTION(ListOfConstraints)
LXCONSTRUCTOR_EXCEPTION(ListOfEventAssignments)
LXCONSTRUCTOR_EXCEPTION(ListOfEvents)
LXCONSTRUCTOR_EXCEPTION(ListOfFunctionDefinitions)
LXCONSTRUCTOR_EXCEPTION(ListOfInitialAssignments)
LXCONSTRUCTOR_EXCEPTION(ListOfParameters)
LXCONSTRUCTOR_EXCEPTION(ListOfLocalParameters)
LXCONSTRUCTOR_EXCEPTION(ListOfReactions)
LXCONSTRUCTOR_EXCEPTION(ListOfRules)
LXCONSTRUCTOR_EXCEPTION(ListOfSpecies)
LXCONSTRUCTOR_EXCEPTION(ListOfSpeciesReferences)
LXCONSTRUCTOR_EXCEPTION(ListOfSpeciesTypes)
LXCONSTRUCTOR_EXCEPTION(ListOfUnitDefinitions)
LXCONSTRUCTOR_EXCEPTION(ListOfUnits)
*/
/**
 *
 * Wraps the XMLConstructorException class (C++ exception defined by libLX)
 * as the VaueError class (Python built-in exception).
 *
 * For example, the exception can be catched in Python code as follows:
 *
 * --------------------------------------
 *  try:
 *    s = liblx.XMLAttributes(invalid arguments)
 *  except ValueError, inst:
 *    errmsg = inst.args[0]
 * --------------------------------------
 */

%ignore XMLConstructorException;

%define XMLCONSTRUCTOR_EXCEPTION(SBASE_CLASS_NAME)
%exception SBASE_CLASS_NAME {
  try {
    $action
  }
  catch (XMLConstructorException &e) {
    PyErr_SetString(PyExc_ValueError, const_cast<char*>(e.what()));
    return NULL;
  }
}
%enddef

XMLCONSTRUCTOR_EXCEPTION(XMLAttributes)
XMLCONSTRUCTOR_EXCEPTION(XMLError)
XMLCONSTRUCTOR_EXCEPTION(XMLNamespaces)
XMLCONSTRUCTOR_EXCEPTION(XMLNode)
XMLCONSTRUCTOR_EXCEPTION(XMLOutputStream)
XMLCONSTRUCTOR_EXCEPTION(XMLToken)
XMLCONSTRUCTOR_EXCEPTION(XMLTripple)


// ----------------------------------------------------------------------
// LXReader
// ----------------------------------------------------------------------

/*
 * A note about how our documentation production interacts with this file.
 *
 * Our Doxygen-based documentation pipeline currently only uses
 * ../swig/liblx.i; it does not read this file for producing the API docs.
 * This file is only used by SWIG itself, to produce a liblx.py file that
 * becomes what users see with Python 'help'.  Thus, the documentation in
 * *this* file has to be the final version of the text we want in front of
 * users when they type help on a method.  This is why the doc strings in
 * methods below are formatted plain text and not Doxygen-style annotated
 * text.
 *
 * The GENERATING_DOCS conditional is used to make SWIG ignore much of this
 * content during a certain phase of the documentation-generation process.
 * It's done so that when we are generating Doxygen-based HTML docs, SWIG
 * does not override the definitions from the original libLX source code
 * files with the modified versions below.
 */

#ifndef GENERATING_DOCS

%pythoncode
%{
import sys
import os.path

# @cond doxygenLiblxInternal

def conditional_abspath (filename):
  """conditional_abspath (filename) -> filename

  Returns filename with an absolute path prepended, if necessary.
  Some combinations of platforms and underlying XML parsers *require*
  an absolute path to a filename while others do not.  This function
  encapsulates the appropriate logic.  It is used by readLX() and
  LXReader.readLX().
  """
  if sys.platform.find('cygwin') != -1:
    return filename
  else:
    return os.path.abspath(filename)

# @endcond
%}


%feature("shadow")
LXReader::readLX(const std::string&)
%{
  def readLX(*args):
    """
    readLX(self, string filename) -> LXDocument

    Reads an LX document from a file.

    This method is identical to readLXFromFile().

    If the file named 'filename' does not exist or its content is not
    valid LX, one or more errors will be logged with the LXDocument
    object returned by this method.  Callers can use the methods on
    LXDocument such as LXDocument.getNumErrors() and
    LXDocument.getError() to get the errors.  The object returned by
    LXDocument.getError() is an LXError object, and it has methods to
    get the error code, category, and severity level of the problem, as
    well as a textual description of the problem.  The possible severity
    levels range from informational messages to fatal errors; see the
    documentation for LXError for more information.

    If the file 'filename' could not be read, the file-reading error will
    appear first.  The error code can provide a clue about what happened.
    For example, a file might be unreadable (either because it does not
    actually exist or because the user does not have the necessary access
    priviledges to read it) or some sort of file operation error may have
    been reported by the underlying operating system.  Callers can check
    for these situations using a program fragment such as the following:

     reader = LXReader()
     doc    = reader.readLX(filename)

     if doc.getNumErrors() > 0:
       if doc.getError(0).getErrorId() == liblx.XMLFileUnreadable:
         # Handle case of unreadable file here.
       elif doc.getError(0).getErrorId() == liblx.XMLFileOperationError:
         # Handle case of other file error here.
       else:
         # Handle other error cases here.

    If the given filename ends with the suffix \".gz\" (for example,
    \"myfile.xml.gz\"), the file is assumed to be compressed in gzip format
    and will be automatically decompressed upon reading.  Similarly, if the
    given filename ends with \".zip\" or \".bz2\", the file is assumed to be
    compressed in zip or bzip2 format (respectively).  Files whose names
    lack these suffixes will be read uncompressed.  Note that if the file
    is in zip format but the archive contains more than one file, only the
    first file in the archive will be read and the rest ignored.

    To read a gzip/zip file, libLX needs to be configured and linked with
    the zlib library at compile time.  It also needs to be linked with the
    bzip2 library to read files in bzip2 format.  (Both of these are the
    default configurations for libLX.)  Errors about unreadable files
    will be logged if a compressed filename is given and libLX was not
    linked with the corresponding required library.

    Parameter 'filename is the name or full pathname of the file to be
    read.

    Returns a pointer to the LXDocument created from the LX content.

    See also LXError.

    Note:

    LibLX versions 2.x and later versions behave differently in
    error handling in several respects.  One difference is how early some
    errors are caught and whether libLX continues processing a file in
    the face of some early errors.  In general, libLX versions after 2.x
    stop parsing LX inputs sooner than libLX version 2.x in the face
    of XML errors, because the errors may invalidate any further LX
    content.  For example, a missing XML declaration at the beginning of
    the file was ignored by libLX 2.x but in version 3.x and later, it
    will cause libLX to stop parsing the rest of the input altogether.
    While this behavior may seem more severe and intolerant, it was
    necessary in order to provide uniform behavior regardless of which
    underlying XML parser (Expat, Xerces, libxml2) is being used by
    libLX.  The XML parsers themselves behave differently in their error
    reporting, and sometimes libLX has to resort to the lowest common
    denominator.
    """
    args_copy    = list(args)
    args_copy[1] = conditional_abspath(args[1])
    return _liblx.LXReader_readLX(*args_copy)
%}

%feature("shadow")
LXReader::readLXFromFile(const std::string&)
%{
  def readLXFromFile(*args):
    """
    Reads an LX document from the given file.

    If the file named 'filename' does not exist or its content is not
    valid LX, one or more errors will be logged with the LXDocument
    object returned by this method.  Callers can use the methods on
    LXDocument such as LXDocument.getNumErrors() and
    LXDocument.getError() to get the errors.  The object returned by
    LXDocument.getError() is an LXError object, and it has methods to
    get the error code, category, and severity level of the problem, as
    well as a textual description of the problem.  The possible severity
    levels range from informational messages to fatal errors; see the
    documentation for LXError for more information.

    If the file 'filename' could not be read, the file-reading error will
    appear first.  The error code  can provide a clue about what happened.
    For example, a file might be unreadable (either because it does not
    actually exist or because the user does not have the necessary access
    privileges to read it) or some sort of file operation error may have
    been reported by the underlying operating system.  Callers can check
    for these situations using a program fragment such as the following:

      reader = LXReader()
      if reader == None:
        # Handle the truly exceptional case of no object created here.

      doc = reader.readLXFromFile(filename)
      if doc.getNumErrors() > 0:
        if doc.getError(0).getErrorId() == XMLFileUnreadable:
          # Handle case of unreadable file here.
        elif doc.getError(0).getErrorId() == XMLFileOperationError:
          # Handle case of other file error here.
        else:
          # Handle other error cases here.

    If the given filename ends with the suffix '.gz' (for example,
    'myfile.xml.gz'), the file is assumed to be compressed in gzip format
    and will be automatically decompressed upon reading. Similarly, if the
    given filename ends with '.zip' or '.bz2', the file is assumed to be
    compressed in zip or bzip2 format (respectively).  Files whose names
    lack these suffixes will be read uncompressed.  Note that if the file
    is in zip format but the archive contains more than one file, only the
    first file in the archive will be read and the rest ignored.

    To read a gzip/zip file, libLX needs to be configured and linked
    with the zlib library at compile time.  It also needs to be linked
    with the bzip2 library to read files in bzip2 format.  (Both of these
    are the default configurations for libLX.)  Errors about unreadable
    files will be logged if a compressed filename is given and libLX was
    not linked with the corresponding required library.

    Parameter 'filename' is the name or full pathname of the file to be
    read.

    Returns a pointer to the LXDocument structure created from the LX
    content in 'filename'.
    """
    args_copy    = list(args)
    args_copy[1] = conditional_abspath(args[1])
    return _liblx.LXReader_readLX(*args_copy)
%}


/**
 * Since we cannot seem to "shadow" readLX() (maybe because it's
 * not a method of some object, but rather a top-level function, we
 * employ the following HACK: Tell SWIG to ignore readLX and just
 * define it in terms of LXReader.readLX().  This is less than
 * ideal, because the libLX C/C++ core does essentially the same
 * thing, so now we're repeating ourselves.
 */

%ignore readLX(const char*);

%pythoncode
%{
def readLX(*args):
  """
  readLX(self, string filename) -> LXDocument

  Reads an LX document from a file.

  This method is identical to readLXFromFile().

  If the file named 'filename' does not exist or its content is not
  valid LX, one or more errors will be logged with the LXDocument
  object returned by this method.  Callers can use the methods on
  LXDocument such as LXDocument.getNumErrors() and
  LXDocument.getError() to get the errors.  The object returned by
  LXDocument.getError() is an LXError object, and it has methods to
  get the error code, category, and severity level of the problem, as
  well as a textual description of the problem.  The possible severity
  levels range from informational messages to fatal errors; see the
  documentation for LXError for more information.

  If the file 'filename' could not be read, the file-reading error will
  appear first.  The error code can provide a clue about what happened.
  For example, a file might be unreadable (either because it does not
  actually exist or because the user does not have the necessary access
  priviledges to read it) or some sort of file operation error may have
  been reported by the underlying operating system.  Callers can check
  for these situations using a program fragment such as the following:

   reader = LXReader()
   doc    = reader.readLX(filename)

   if doc.getNumErrors() > 0:
     if doc.getError(0).getErrorId() == liblx.XMLFileUnreadable:
       # Handle case of unreadable file here.
     elif doc.getError(0).getErrorId() == liblx.XMLFileOperationError:
       # Handle case of other file error here.
     else:
       # Handle other error cases here.

  If the given filename ends with the suffix \".gz\" (for example,
  \"myfile.xml.gz\"), the file is assumed to be compressed in gzip format
  and will be automatically decompressed upon reading.  Similarly, if the
  given filename ends with \".zip\" or \".bz2\", the file is assumed to be
  compressed in zip or bzip2 format (respectively).  Files whose names
  lack these suffixes will be read uncompressed.  Note that if the file
  is in zip format but the archive contains more than one file, only the
  first file in the archive will be read and the rest ignored.

  To read a gzip/zip file, libLX needs to be configured and linked with
  the zlib library at compile time.  It also needs to be linked with the
  bzip2 library to read files in bzip2 format.  (Both of these are the
  default configurations for libLX.)  Errors about unreadable files
  will be logged if a compressed filename is given and libLX was not
  linked with the corresponding required library.

  Parameter 'filename is the name or full pathname of the file to be
  read.

  Returns a pointer to the LXDocument created from the LX content.

  See also LXError.

  Note:

  LibLX versions 2.x and later versions behave differently in
  error handling in several respects.  One difference is how early some
  errors are caught and whether libLX continues processing a file in
  the face of some early errors.  In general, libLX versions after 2.x
  stop parsing LX inputs sooner than libLX version 2.x in the face
  of XML errors, because the errors may invalidate any further LX
  content.  For example, a missing XML declaration at the beginning of
  the file was ignored by libLX 2.x but in version 3.x and later, it
  will cause libLX to stop parsing the rest of the input altogether.
  While this behavior may seem more severe and intolerant, it was
  necessary in order to provide uniform behavior regardless of which
  underlying XML parser (Expat, Xerces, libxml2) is being used by
  libLX.  The XML parsers themselves behave differently in their error
  reporting, and sometimes libLX has to resort to the lowest common
  denominator.
  """
  reader = LXReader()
  return reader.readLX(args[0])
%}




/**
 * Allows ListOf objects:
 *
 *   - To be indexed and sliced, e.g. lst[0].
 */

%define WRAP_LISTWRAPPER(CLASS)

%template ( ListWrapper ## CLASS ) ListWrapper<CLASS>;

%extend ListWrapper<CLASS>
{
  int __len__()
  {
    return self->getSize();
  }

  %pythoncode
  {
    def __getitem__(self, key):

      try:
         keyIsSlice = isinstance(key, slice)
      except:
         keyIsSlice = 0

      if keyIsSlice:
        start = key.start
        if start is None:
          start = 0
        stop = key.stop
        if stop is None:
          stop = self.getSize()
        return [self[i] for i in range(
          self._fixNegativeIndex(start), self._fixNegativeIndex(stop)
        )]

      key = self._fixNegativeIndex(key)
      if key < 0 or key >= self.getSize():
        raise IndexError(key)
      return self.get(key)


    def _fixNegativeIndex(self, index):
      if index < 0:
        return index + self.getSize()
      else:
        return index


    def __iter__(self):
      for i in range(self.getSize()):
        yield self[i]


    def __repr__(self):
      return "[" + ", ".join([repr(self[i]) for i in range(len(self))]) + "]"


    def __str__(self):
      return repr(self)
  }
}

%enddef
/*
WRAP_LISTWRAPPER(LXNamespaces)
WRAP_LISTWRAPPER(CVTerm)
WRAP_LISTWRAPPER(Date)
WRAP_LISTWRAPPER(ModelCreator)
WRAP_LISTWRAPPER(SBase)
*/

/**
 *  Wraps the following functions by using the corresponding
 *  ListWrapper<TYPENAME> class.
 *
 *  - List* ModelHistory::getListCreators()
 *  - List* ModelHistory::getListModifiedDates()
 *  - List* SBase::getCVTerms()
 *  - List* LXNamespaces::getSupportedNamespaces()
 *
 *  ListWrapper<TYPENAME> class is wrapped as TYPENAMEList class.
 *  So, the above functions are wrapped as follows:
 *
 *  - ModelCreatorList ModelHistory.getListCreators()
 *  - DateList         ModelHistory.getListModifiedDates()
 *  - CVTermList       SBase.getCVTerms()
 *  - LXNamespacesList LXNamespaces::getSupportedNamespaces()
 *
 */



%feature("shadow")
LXNamespaces::getSupportedNamespaces
%{
  def getSupportedNamespaces(self):
    """
    getSupportedNamespaces(self) -> LXNamespaceList

    Get the List of supported LXNamespaces for this
    version of LibLX.

    Returns the supported list of LXNamespaces.


    """
    return _liblx.LXNamespaces_getSupportedNamespaces(self)
%}

%typemap(out) List* LXNamespaces::getSupportedNamespaces
{
  ListWrapper<LXNamespaces> *listw = ($1 != 0) ? new ListWrapper<LXNamespaces>($1) : 0;
  $result = SWIG_NewPointerObj(SWIG_as_voidptr(listw),
#if SWIG_VERSION > 0x010333
                               SWIGTYPE_p_ListWrapperT_LXNamespaces_t,
#else
                               SWIGTYPE_p_ListWrapperTLXNamespaces_t,
#endif
                               SWIG_POINTER_OWN |  0 );
}



%feature("shadow")
ModelHistory::getListCreators
%{
  def getListCreators(self):
    """
    getListCreators(self) -> ModelCreatorList

    Get the List of ModelCreator objects in this
    ModelHistory.

    Returns the ModelCreatorList for this ModelHistory.


    """
    return _liblx.ModelHistory_getListCreators(self)
%}

%typemap(out) List* ModelHistory::getListCreators
{
  ListWrapper<ModelCreator> *listw = ($1 != 0) ? new ListWrapper<ModelCreator>($1) : 0;
  $result = SWIG_NewPointerObj(SWIG_as_voidptr(listw),
#if SWIG_VERSION > 0x010333
                               SWIGTYPE_p_ListWrapperT_ModelCreator_t,
#else
                               SWIGTYPE_p_ListWrapperTModelCreator_t,
#endif
                               SWIG_POINTER_OWN |  0 );
}


%feature("shadow")
ModelHistory::getListModifiedDates
%{
  def getListModifiedDates(self):
    """
    getListModifiedDates(self) -> DateList

    Get the List of Date objects in this ModelHistory.

    Returns the DateList for this ModelHistory.


    """
    return _liblx.ModelHistory_getListModifiedDates(self)
%}

%typemap(out) List* ModelHistory::getListModifiedDates
{
  ListWrapper<Date> *listw = ($1 != 0) ? new ListWrapper<Date>($1) : 0;
  $result = SWIG_NewPointerObj(SWIG_as_voidptr(listw),
#if SWIG_VERSION > 0x010333
                               SWIGTYPE_p_ListWrapperT_Date_t,
#else
                               SWIGTYPE_p_ListWrapperTDate_t,
#endif
                               SWIG_POINTER_OWN |  0 );
}

%feature("shadow")
SBase::getCVTerms
%{
  def getCVTerms(self):
    """
    getCVTerms(self) -> CVTermList

    Get the List of CVTerm objects in this element.

    Returns the CVTermList for this element.


    """
    
    cvlist = _liblx.SBase_getCVTerms(self)
    if cvlist is None:
      return []
    else:
      return cvlist
%}

%typemap(out) List* SBase::getCVTerms
{
  ListWrapper<CVTerm> *listw = ($1 != 0) ? new ListWrapper<CVTerm>($1) : 0;
  $result = SWIG_NewPointerObj(SWIG_as_voidptr(listw),
#if SWIG_VERSION > 0x010333
                               SWIGTYPE_p_ListWrapperT_CVTerm_t,
#else
                               SWIGTYPE_p_ListWrapperTCVTerm_t,
#endif
                               SWIG_POINTER_OWN |  0 );
}


%feature("shadow")
SBase::getListOfAllElements
%{
  def getListOfAllElements(self, *args):
    """
    getListOfAllElements(self) -> SBaseList

    Get the List of all SBase objects in this element.

    Returns the List of all child elements.


    """
    return _liblx.SBase_getListOfAllElements(self, *args)
%}

%typemap(out) List* SBase::getListOfAllElements
{
  ListWrapper<SBase> *listw = ($1 != 0) ? new ListWrapper<SBase>($1) : 0;
  $result = SWIG_NewPointerObj(SWIG_as_voidptr(listw),
#if SWIG_VERSION > 0x010333
                               SWIGTYPE_p_ListWrapperT_SBase_t,
#else
                               SWIGTYPE_p_ListWrapperTSBase_t,
#endif
                               SWIG_POINTER_OWN |  0 );
}


%feature("shadow")
SBase::getListOfAllElementsFromPlugins
%{
  def getListOfAllElementsFromPlugins(self, *args):
    """
    getListOfAllElementsFromPlugins(self) -> SBaseList

    Get the List of SBase objects in this elements plugins.

    Returns the SBaseList of all plugins for this element.


    """
    return _liblx.SBase_getListOfAllElementsFromPlugins(self, *args)
%}

%typemap(out) List* SBase::getListOfAllElementsFromPlugins
{
  ListWrapper<SBase> *listw = ($1 != 0) ? new ListWrapper<SBase>($1) : 0;
  $result = SWIG_NewPointerObj(SWIG_as_voidptr(listw),
#if SWIG_VERSION > 0x010333
                               SWIGTYPE_p_ListWrapperT_SBase_t,
#else
                               SWIGTYPE_p_ListWrapperTSBase_t,
#endif
                               SWIG_POINTER_OWN |  0 );
}

%feature("shadow")
SBasePlugin::getListOfAllElements
%{
  def getListOfAllElements(self, *args):
    """
    getListOfAllElements(self) -> SBaseList

    Get the List of SBase objects in this plugin.

    Returns the SBaseList of all element for this plugin.


    """
    return _liblx.SBasePlugin_getListOfAllElements(self, *args)
%}

%typemap(out) List* SBasePlugin::getListOfAllElements
{
  ListWrapper<SBase> *listw = ($1 != 0) ? new ListWrapper<SBase>($1) : 0;
  $result = SWIG_NewPointerObj(SWIG_as_voidptr(listw),
#if SWIG_VERSION > 0x010333
                               SWIGTYPE_p_ListWrapperT_SBase_t,
#else
                               SWIGTYPE_p_ListWrapperTSBase_t,
#endif
                               SWIG_POINTER_OWN |  0 );
}

/***
 * Add a document reference to the returned model to keep it alive
*/
%feature("shadow")
LXDocument::getModel
%{
  def getModel(self, *args):
    """
    getModel(LXDocument self) -> Model
    getModel(LXDocument self) -> Model


    Returns the Model object stored in this LXDocument.

    It is important to note that this method does not create a Model
    instance.  The model in the LXDocument must have been created at
    some prior time, for example using LXDocument.createModel()  or
    LXDocument.setModel(). This method returns 'None' if a model does
    not yet exist.

    Returns the Model contained in this LXDocument, or 'None' if no such
    model exists.

    See also createModel().

    """
    model = _liblx.LXDocument_getModel(self, *args)
    if model is not None:
      model.__parent_ref__ = self
    return model
%}


#endif

%include "local-packages.i"
