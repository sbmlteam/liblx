/**
 * \file    liblx.i
 * \brief   Language-independent SWIG directives for wrapping libLX
 * \author  Ben Bornstein and Ben Kovitz
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
 * in the file named "LICENSE.txt" included with this software distribution
 * and also available online as http://libsbml.org/software/libsbml/license.html
 * ---------------------------------------------------------------------- -->*/

%module(directors="1") liblx

//%feature("director") LXValidator;
//%feature("director") LXConverter;
//%feature("director") ElementFilter;
//%feature("director") MathFilter;
//%feature("director") IdentifierTransformer;
//%feature("director") Callback;
//%ignore IdentifierTransformer::transform(const SBase* element);

#pragma SWIG nowarn=473,401,844

#if (!defined (SWIGJAVA) && !defined(SWIGCSHARP))
// apply typemaps for items we manage manually
%include "typemaps.i"

//%apply SWIGTYPE *DISOWN { SBase* disownedItem };
//%apply SWIGTYPE *DISOWN { SBase_t* disownedItem };
%apply SWIGTYPE *DISOWN { XMLNode* disownedAnnotation };
%apply SWIGTYPE *DISOWN { XMLNode_t* disownedAnnotation };
//%apply SWIGTYPE *DISOWN { ASTNode* disownedChild };
//%apply SWIGTYPE *DISOWN { ASTNode_t* disownedChild };
%apply SWIGTYPE *DISOWN { XMLNamespaces* disownedNs };   // ???

#endif 

%pragma(java) moduleclassmodifiers="
/**
  * Wrapper class for global methods and constants defined by libLX.
  * <p>
  * <em style='color: #555'>
  * This class of objects is defined by libLX only and has no direct
  * equivalent in terms of LX components.  This class is not prescribed by
  * the LX specifications, although it is used to implement features
  * defined in LX.
  * </em>
  * <p>
  * In the C++ and C versions of libLX, there exists a small number of
  * methods that are global in scope; in addition, libLX uses a number
  * of enum's to define such things as error codes in a way that can be
  * used by both C++ and C.  This poses a problem in languages such as
  * Java, where there is no concept of global method or global constant.
  * SWIG wraps these global identifiers in the class whose documentation
  * you see before you.
  */
public class"


%{
#include "liblx.h"
#define SWIG_FILE_WITH_INIT
LIBLX_CPP_NAMESPACE_USE

// #include "../swig/liblx-packages.h"
	
#include "local.cpp"
%}

%include "liblx.h"

%import  liblx/xml/common/liblx-namespace.h
%import  liblx/xml/common/extern.h
%import  liblx/xml/common/liblxfwd.h
//%import  lx/xml/XMLExtern.h    // do we still need this? not present in libLX now.

/**
 * Wraps List class by ListWrapper<TYPENAME> template class.
 * TYPENAME is replaced with a corresponding data type which is
 * stored in the List object (e.g. ModelCreator, CVTerm and ASTNode). 
 *
 * ListWrapper<TYPENAME> class is wrapped as TYPENAMEList class
 * (e.g. ListWrapper<CVTerm> -> CVTermList)
 *
 */

//%include "ListWrapper.h"
/*
%template(ModelCreatorList)   ListWrapper<ModelCreator>;
%template(DateList)           ListWrapper<Date>;
%template(CVTermList)         ListWrapper<CVTerm>;
%template(ASTNodeList)        ListWrapper<ASTNode>;
*/
//%template(XMLNamespacesList) ListWrapper<XMLNamespaces>;
/*
%template(SBaseList)          ListWrapper<SBase>;
*/

/**
 *
 * Includes a language specific interface file.
 *
 */

%include local.i

/**
 * Unfortunately, SWIG makes no distinction between const and non-const
 * member functions (SWIG 1.3 Manual, Section 6.25), but in libLX C++ we
 * have both const and non-const versions of most getter methods.  To avoid
 * a ton of warning messages about 'const' methods not being wrapped, we
 * disable Warning(516).
 */
#pragma SWIG nowarn=516

/**
 * Ignore the Visitor pattern accept() method (for now) on all LX
 * objects.
 */
%ignore *::accept;

/**
 * Ignore internal implementation methods in ASTNode.h
 */
 /*
%ignore ASTNode(Token_t*);
%ignore ASTNode::getListOfNodes(ASTNodePredicate predicate) const;
%ignore ASTNode::fillListOfNodes;
%ignore ASTNode::setSemanticsFlag;
%ignore ASTNode::unsetSemanticsFlag;
%ignore ASTNode::getSemanticsFlag;
*/
/**
 * Ignore the list that can't be wrapped
 */
//%ignore LXExtensionRegistry::getRegisteredPackageNames;

/**
 * SWIG makes no distinction between int and long arguments.
 * (SWIG 1.3 Manual, Section 6.15.2)
 */
//%ignore ASTNode::setValue(int);

/**
 * Ignore operator= and operator<< on all LX objects.
 */
%ignore *::operator=;
%ignore *::operator<<;
%ignore operator==;
%ignore operator!=;

/**
 * Ignore certain internal implementation methods on all objects.
 */
%ignore *::writeElements;
%ignore *::getElementPosition;
%ignore *::setLXDocument;
%ignore *::setParentLXObject;
%ignore *::setInternalId;
%ignore *::getInternalId;

/**
 * Ignore internal implementation methods in MathML.h
 */
//%ignore readMathML;
//%ignore writeMathML;

/**
 * Ignore methods whose pointer argument serves as both input and output
 */
%ignore XMLAttributes::readInto;

/**
 * Ignore methods which receive std::list.
 */
%ignore XMLErrorLog::add(const std::list<XMLError>& errors);
//%ignore LXErrorLog::add(const std::list<LXError>& errors);
%ignore XMLErrorLog::add(const std::vector<XMLError>& errors);

/**
 * Ignore methods from LX Validator that can't be wrapped
 */
//%ignore LXValidator::getFailures;
//%ignore LXExternalValidator::getArguments;
//%ignore LXExternalValidator::setArguments;

/**
 * Ignore 'static ParentMap mParent;' in SBO.h
 */
//%ignore mParent;

/**
 * Ignore 'struct xmlErrorTableEntry' in XMLError.h.
 */
%ignore xmlErrorTableEntry;

/**
 * Both "const std::string& SBase::getMetaId() const" and
 * "std:string& SBase::getMetaId()" are defined in SBase.cpp.
 * By default, SWIG doesn't convert non-const std:string& to and from
 * target language string.
 * So we ignore the non-const version.
 */
//%ignore SBase::getMetaId();

/**
 * Ignore internal methods on SBase
 */
//ignore SBase::removeDuplicateAnnotations;
//%ignore SBase::setLXNamespaces;
//%ignore SBase::getLXNamespaces;
//%ignore SBase::read;
%catches(XMLConstructorException) XMLInputStream::XMLInputStream;  // ???
//%ignore SBase::write;
//%catches(XMLConstructorException) SBase::write; // ???

/**
 * Ignore internal methods on Model
 */
 /*
%ignore Model::addFormulaUnitsData;
%ignore Model::createFormulaUnitsData;
%ignore Model::getFormulaUnitsData;
%ignore Model::getListFormulaUnitsData;
%ignore Model::getNumFormulaUnitsData;
%ignore Model::isBoolean;
%ignore Model::removeMetaId;
%ignore Model::removeSBOTerms;
%ignore Model::removeHasOnlySubstanceUnits;
%ignore Model::removeSBOTermsNotInL2V2;
%ignore Model::removeDuplicateTopLevelAnnotations;
%ignore Model::convertToL1;
%ignore Model::convertToL2;
%ignore Model::convertToL2V1;
%ignore Model::convertToL2V2;
%ignore Model::convertToL2Strict;
*/
/**
 * Ignore internal implementation methods in Rule
 */
/*
%ignore Rule::setInternalIdOnly;
%ignore Rule::getInternalIdOnly;
*/
/**
 * Ignore internal implementation methods in SpeciesReference
 */
//%ignore SpeciesReference::sortMath;

/**
 * Ignore internal implementation methods in UnitDefinition
 */
//%ignore UnitDefinition::areIdenticalSIUnits;

/**
 * Ignore internal implementation methods in XMLAttributes
 */
%ignore XMLAttributes::addResource;
%ignore XMLAttributes::write;
%ignore XMLAttributes::setErrorLog;

/**
 * Ignore internal implementation methods in Event
 */
//%ignore Event::setInternalIdOnly;

/**
 * Ignore internal implementation methods in SBO
 */
//%ignore SBO::readTerm;
//%ignore SBO::writeTerm;

/**
 * With the new Validator API we no longer exclude the following 
 * methods:
 */ 
//%ignore LXErrorLog::logError;
//%ignore LXErrorLog::add;
//%ignore LXErrorLog::remove;
//%ignore LXErrorLog::LXErrorLog;
//%ignore XMLErrorLog::XMLErrorLog;
//%ignore XMLErrorLog::add;


/**
 * Ignore internal implementation methods in XMLErrorLog
 */
%ignore XMLErrorLog::setParser;


/**
 * Ignore internal implementation methods in ModelCreator
 */
//%ignore ModelCreator::getAdditionalRDF;

/**
 * Ignore internal implementation methods in RDFAnnotationParser
 */
/*
%ignore RDFAnnotationParser::hasRDFAnnotation;
%ignore RDFAnnotationParser::hasAdditionalRDFAnnotation;
%ignore RDFAnnotationParser::hasCVTermRDFAnnotation;
%ignore RDFAnnotationParser::hasHistoryRDFAnnotation;
%ignore RDFAnnotationParser::createRDFDescription;
%ignore RDFAnnotationParser::createRDFDescriptionWithCVTerms;
%ignore RDFAnnotationParser::createRDFDescriptionWithHistory;
%ignore RDFAnnotationParser::deriveCVTermsFromAnnotation;
%ignore RDFAnnotationParser::deriveHistoryFromAnnotation;
*/
/**
 * Ignore internal implementation methods in SyntaxChecker
 */
/*
%ignore SyntaxChecker::isAllowedElement;
%ignore SyntaxChecker::hasDeclaredNS;
%ignore SyntaxChecker::isCorrectHTMLNode;
*/
/** 
 * Ignore some const versions of methods
 */
//%ignore LXConverter::setDocument(LXDocument const *);
//%ignore LXReactionConverter::setDocument(LXDocument const *);


/**
 * Ignore internal implementation methods and some other methods
 * on LXNamespces.
 */
//%ignore LXNamespaces::setLevel;
//%ignore LXNamespaces::setVersion;
//%ignore LXNamespaces::setNamespaces;

/**
 * Ignore internal implementation methods and some other methods
 * on LXTransforms.
 */
//%ignore LXTransforms::evaluateASTNode(const ASTNode * node, const IdValueMap& values, const Model * m = NULL);
//%ignore LXTransforms::evaluateASTNode(const ASTNode * node, const std::map<std::string, double>& values, const Model * m = NULL);
//%ignore LXTransforms::getComponentValuesForModel(const Model * m, IdValueMap& values);

/**
 * Ignore internal implementation methods in XMLToken
 */
%ignore XMLToken::write;

/**
 * Ignore internal implementation methods in XMLNode
 */
%ignore XMLNode::XMLNode(XMLInputStream&);  // ???
%ignore XMLNode::write;

/**
 * Ignore internal implementation methods in XMLOutputStream
 */
%ignore XMLOutputStream::getStringStream;

/**
 * Ignore internal implementation classes
 */
%ignore XMLOutputStringStream;
%ignore XMLOutputFileStream;

/**
 * Ignore the unsigned int version of XMLOutputStream::writeAttribute method
 * in order to properly wrap the long version of XMLOutputStream::writeAttribute 
 * method which should be used instead of the unsigned int version.
 */
%ignore XMLOutputStream::writeAttribute(const std::string&, const unsigned int&);
%ignore XMLOutputStream::writeAttribute(const XMLTriple&,   const unsigned int&);

/**
 * The following methods will create new objects.  To prevent memory
 * leaks we must inform SWIG of this.
 */

%typemap(newfree) char * "free($1);";
/*
%newobject *::clone;
%newobject removeChildObject;
%newobject SBase::toLX;
%newobject LXReader::readLXFromString;
%newobject LXReader::readLXFromFile;
%newobject LXReader::readLX;
%newobject readLX(const char *);
%newobject readLXFromString(const char *);
%newobject readLXFromFile(const char *);
%newobject LXWriter::writeToString;
%newobject writeLXToString;
%newobject readMathMLFromString;
%newobject writeMathMLToString;
%newobject LX_formulaToString;
%newobject LX_formulaToL3String;
%newobject LX_formulaToL3StringWithSettings;
%newobject LX_parseFormula;
%newobject LX_parseL3Formula;
%newobject LX_parseL3FormulaWithModel;
%newobject LX_parseL3FormulaWithSettings;
%newobject LX_getDefaultL3ParserSettings;
%newobject LX_getLastParseL3Error;
%newobject ASTNode::deepCopy;
%newobject ASTNode::getListOfNodes();
%newobject *::remove;
%newobject CVTerm::removeNestedCVTerm;
%newobject ConversionProperties::removeOption
%newobject Event::removeEventAssignment;
%newobject KineticLaw::removeParameter;
%newobject KineticLaw::removeLocalParameter;
%newobject Model::removeFunctionDefinition;
%newobject Model::removeUnitDefinition;
%newobject Model::removeCompartmentType;
%newobject Model::removeCompartment;
%newobject Model::removeSpeciesType;
%newobject Model::removeSpecies;
%newobject Model::removeCompartment;
%newobject Model::removeParameter;
%newobject Model::removeInitialAssignment;
%newobject Model::removeRule;
%newobject Model::removeRuleByVariable;
%newobject Model::removeConstraint;
%newobject Model::removeReaction;
%newobject Model::removeEvent;
%newobject Reaction::removeReactant;
%newobject Reaction::removeProduct;
%newobject Reaction::removeModifier;
%newobject Event::removeEventAssignment;
%newobject UnitDefinition::removeUnit;
%newobject KineticLaw::removeParameter;
%newobject KineticLaw::removeLocalParameter;
%newobject RDFAnnotationParser::parseRDFAnnotation(XMLNode *);
%newobject RDFAnnotationParser::deleteRDFAnnotation;
%newobject RDFAnnotationParser::parseCVTerms;
%newobject RDFAnnotationParser::parseModelHistory;
%newobject RDFAnnotationParser::createRDFAnnotation;
%newobject RDFAnnotationParser::createAnnotation;
%newobject RDFAnnotationParser::createRDFDescription;
%newobject RDFAnnotationParser::createCVTerms;
*/
%newobject XMLNode::removeChild;
%newobject XMLNode::convertStringToXMLNode;


/*
%newobject Unit::convertToSI;
%newobject UnitDefinition::convertToSI;
%newobject UnitDefinition::combine;
*/
/**
 * We can't currently support attaching arbitrary user data to
 * libLX objects.
 */
%ignore *::setUserData;
%ignore *::getUserData;

/**
 * In the wrapped languages, these methods will appear as:
 *
 *  - liblx.formulaToString()
 *  - liblx.parseFormula()
 */
/*
%rename(formulaToL3String) LX_formulaToL3String;
%rename(formulaToL3StringWithSettings) LX_formulaToL3StringWithSettings;
%rename(formulaToString) LX_formulaToString;
%rename(parseFormula)    LX_parseFormula;
%rename(parseL3Formula)    LX_parseL3Formula;
%rename(parseL3FormulaWithModel)    LX_parseL3FormulaWithModel;
%rename(parseL3FormulaWithSettings)    LX_parseL3FormulaWithSettings;
%rename(getDefaultL3ParserSettings)    LX_getDefaultL3ParserSettings;
%rename(getLastParseL3Error)    LX_getLastParseL3Error;
*/
/**
 *
 * wraps "List* ASTNode::getListOfNodes(ASTNodePredicate)" function
 * as "ListWrapper<ASTNode>* ASTNode::getListOfNodes()" function
 * which returns a list of all ASTNodes.
 *
 */
/*
%ignore SBase::getAllElementsFromPlugins;
%ignore SBasePlugin::getAllElements;
%ignore SBase::getAllElements;
%ignore Model::renameIDs(List* elements, IdentifierTransformer* idTransformer);
*/
/*
%extend Model
{
   void renameIDs(ListWrapper<SBase>* elements, IdentifierTransformer *idTransformer)
   {
		if (!elements) return;

		List *list = elements->getList();
		$self->renameIDs(list, idTransformer);
   }
}
*/

/*
 * Docstring additions using SWIG's %feature("docstring") have to come before
 * the method definitions.  I have no idea why.  I don't think it's
 * documented that way, and it's backwards, and I would never have figured it
 * out except for the fact that I found a comment in someone else's code on
 * GitHub where they had problems with missing doc strings.
 */
#ifndef SWIGRUBY
/*
%feature("docstring") SBasePlugin::getListOfAllElements "
Returns an SBaseList of all child SBase objects, including those
nested to an arbitrary depth.

@return a list of all objects that are children of this object.
";
*/
#endif
/*
%extend SBasePlugin
{
	ListWrapper<SBase>* getListOfAllElements(ElementFilter* filter=NULL)
	{
		List* list = $self->getAllElements(filter);
		return new ListWrapper<SBase>(list);
	}
}
*/
#ifndef SWIGRUBY
/*
%feature("docstring") SBase::getListOfAllElements "
Returns an SBaseList of all child SBase objects, including those
nested to an arbitrary depth.

@return a list of all objects that are children of this object.
";
*/
#endif
/*
%extend SBase
{
	ListWrapper<SBase>* getListOfAllElements(ElementFilter* filter=NULL)
	{
		List* list = $self->getAllElements(filter);
		return new ListWrapper<SBase>(list);
	}
}
*/

#ifndef SWIGRUBY
/*
%feature("docstring") SBase::getListOfAllElementsFromPlugins "
Returns a List of all child SBase objects contained in LX package
plug-ins.

@copydetails doc_what_are_plugins

This method walks down the list of all LX Level&nbsp;3 packages used
by this object and returns all child objects defined by those packages.

@return a pointer to a List of pointers to all children objects from
plug-ins.

@ifnot hasDefaultArgs @htmlinclude warn-default-args-in-docs.html @endif@~
";
*/
#endif
/*
%extend SBase
{
	ListWrapper<SBase>* getListOfAllElementsFromPlugins(ElementFilter* filter=NULL)
	{
		List* list = $self->getAllElementsFromPlugins(filter);
		return new ListWrapper<SBase>(list);
	}
}
*/
#ifndef SWIGRUBY
/*
%feature("docstring") ASTNode::getListOfNodes "
Returns a list of nodes.

Unlike the equivalent method in the libLX C/C++ interface, this method does
not offer the ability to pass a predicate as an argument.  The method always
returns the list of all ASTNode objects.

@return the ASTNodeList of nodes.

@warning The list returned is owned by the caller and should be deleted after
the caller is done using it.  The ASTNode objects in the list; however, are
<strong>not</strong> owned by the caller (as they still belong to the tree
itself), and therefore should not be deleted.
";
*/
#endif
/*
%extend ASTNode
{
  ListWrapper<ASTNode>* getListOfNodes()
  {
    List *list = $self->getListOfNodes(ASTNode_true);
    return new ListWrapper<ASTNode>(list);
  }
}
*/

/*
 * Wraps "static void RDFAnnotationParser::parseRDFAnnotation(const XMLNode *annotation, 
 * List *CVTerms)" function as 
 * "static void RDFAnnotationParser::parseRDFAnnotation(const XMLNode *annotation, 
 *  ListWrapper<CVTerm> *CVTerms);
 *
 */

//%ignore RDFAnnotationParser::parseRDFAnnotation(const XMLNode * annotation, List * CVTerms);
//%ignore RDFAnnotationParser::parseRDFAnnotation(const XMLNode * annotation, List * CVTerms, const char* metaId = NULL, XMLInputStream* stream = NULL);

#ifndef SWIGRUBY
/*
%feature("docstring") RDFAnnotationParser::parseRDFAnnotation "
Parses an annotation (given as an XMLNode tree) into a list of
CVTerm objects.

This is used to take an annotation that has been read into an LX
model, identify the RDF elements within it, and create a list of
corresponding CVTerm (controlled vocabulary term) objects.

@param annotation XMLNode containing the annotation.
@param CVTerms list of CVTerm objects to be created.
@param metaId optional metaId, if set only the RDF annotation for this metaId will be returned.
@param stream optional XMLInputStream that facilitates error logging.

@copydetails doc_note_static_methods

@htmlinclude warn-default-args-in-docs.html
";
*/
#endif

/*
%extend RDFAnnotationParser
{
  static void parseRDFAnnotation(const XMLNode *annotation, ListWrapper<CVTerm> *CVTerms)
  {
    if (!CVTerms) return;

    List *list = CVTerms->getList();
    RDFAnnotationParser::parseRDFAnnotation(annotation,list);
  }

  static void parseRDFAnnotation(const XMLNode *annotation, ListWrapper<CVTerm> *CVTerms, const char* metaId = NULL, XMLInputStream* stream = NULL)
  {
    if (!CVTerms) return;

    List *list = CVTerms->getList();
    RDFAnnotationParser::parseRDFAnnotation(annotation,list, metaId, stream);
  }
}
*/

/**
 * For reasons I cannot fathom, SWIG refuses to incorporate the comment for
 * this method into the liblx_wrap.cpp file, even though there is nothing
 * special about this method and it looks for all the world like other
 * methods in SBase.h.  So, this next item is simply to duplicate the method
 * comment from SBase.h to here.
 */

#ifndef SWIGRUBY
/*
%feature("docstring") SBase::hasValidLevelVersionNamespaceCombination "
Predicate returning @c true if this object's level/version and namespace
values correspond to a valid LX specification.

The valid combinations of LX Level, Version and Namespace as of this
release of libLX are the following:
<ul>
<li> Level&nbsp;1 Version&nbsp;2: <code style='margin-right:0; padding-right:0'>http</code><code style='margin-left:0; padding-left:0'>://www.lx.org/lx/level1</code>
<li> Level&nbsp;2 Version&nbsp;1: <code style='margin-right:0; padding-right:0'>http</code><code style='margin-left:0; padding-left:0'>://www.lx.org/lx/level2</code>
<li> Level&nbsp;2 Version&nbsp;2: <code style='margin-right:0; padding-right:0'>http</code><code style='margin-left:0; padding-left:0'>://www.lx.org/lx/level2/version2</code>
<li> Level&nbsp;2 Version&nbsp;3: <code style='margin-right:0; padding-right:0'>http</code><code style='margin-left:0; padding-left:0'>://www.lx.org/lx/level2/version3</code>
<li> Level&nbsp;2 Version&nbsp;4: <code style='margin-right:0; padding-right:0'>http</code><code style='margin-left:0; padding-left:0'>://www.lx.org/lx/level2/version4</code>
<li> Level&nbsp;3 Version&nbsp;1 Core: <code style='margin-right:0; padding-right:0'>http</code><code style='margin-left:0; padding-left:0'>://www.lx.org/lx/level3/version1/core</code>
</ul>

@return @c true if the level, version and namespace values of this 
LX object correspond to a valid set of values, @c false otherwise.
";
*/

/*
 * If left as-is, the method descriptions for the constructors for
 * XMLInputStream and XMLOutputStream end up on our "Core libLX" page in
 * the API docs rather than on the pages for the individual classes
 * themselves.  This is another case of unfathomable behavior of either
 * Doxygen or SWIG (not sure which one is to blame for this).  Adding
 * explicit docstrings declarations here solves this problem.
 */

%feature("docstring") XMLInputStream::XMLInputStream "
Creates a new XMLInputStream.

@param content the source of the stream.

@param isFile a boolean flag to indicate whether @p content is a file
name.  If @c true, @p content is assumed to be the file from which the
XML content is to be read.  If @c false, @p content is taken to be a
string that @em is the content to be read.

@param library the name of the parser library to use.

@param errorLog the XMLErrorLog object to use.

@htmlinclude warn-default-args-in-docs.html
";

%feature("docstring") XMLOutputStream::XMLOutputStream "
Creates a new XMLOutputStream that wraps the given @p stream.

The functionality associated with the @p programName and @p
programVersion arguments concerns an optional comment that libLX can
write at the beginning of the output stream.  The comment is intended
for human readers of the XML file, and has the following form:
@verbatim
<!-- Created by <program name> version <program version>
on yyyy-MM-dd HH:mm with libLX version <liblx version>. -->
@endverbatim

This program information comment is a separate item from the XML
declaration that this method can also write to this output stream.  The
comment is also not mandated by any LX specification.  This libLX
functionality is provided for the convenience of calling programs, and to
help humans trace the origin of LX files.

LibLX tries to produce human-readable XML output by automatically
indenting the bodies of elements.  Callers can manually control
indentation further by using the XMLOutputStream::upIndent()
and XMLOutputStream::downIndent() methods to increase and
decrease, respectively, the current level of indentation in the
XML output.

@param stream the input stream to wrap.

@param encoding the XML encoding to declare in the output. This value should
be <code>&quot;UTF-8&quot;</code> for LX documents.  The default value is
<code>&quot;UTF-8&quot;</code> if no value is supplied for this parameter.

@param writeXMLDecl whether to write a standard XML declaration at
the beginning of the content written on @p stream.  The default is
@c true.

@param programName an optional program name to write as a comment
in the output stream.

@param programVersion an optional version identification string to write
as a comment in the output stream.

@htmlinclude warn-default-args-in-docs.html
";

#endif

/** 
 * Enable unicode input in Python 2 if Swig version is > 3.0.8
 */

#ifdef USE_SWIG_PYTHON_2_UNICODE

%begin %{

#define SWIG_PYTHON_2_UNICODE

%}

#endif


/**
 * Wrap these files.
 */

%include "std_string.i"     // ???

%include liblx/xml/common/liblx-version.h
%include liblx/xml/operationReturnValues.h
//%include lx/common/common-documentation.h
//%include lx/common/common-lxerror-codes.h

/*
%include <lx/util/IdList.h>
%include <lx/util/IdentifierTransformer.h>
%include <lx/util/ElementFilter.h>
*/
/*
%include <lx/LXReader.h>
%include lx/LXWriter.h
%include lx/LXTypeCodes.h
%include lx/SBase.h
%include lx/ListOf.h
%include lx/Model.h
%include lx/LXDocument.h
%include lx/FunctionDefinition.h
%include lx/UnitKind.h
%include lx/Unit.h
%include lx/UnitDefinition.h
%include lx/CompartmentType.h
%include lx/SpeciesType.h
%include lx/Compartment.h
%include lx/Species.h
%include lx/Parameter.h
%include lx/LocalParameter.h
%include lx/InitialAssignment.h
%include lx/Rule.h
%include lx/AlgebraicRule.h
%include lx/AssignmentRule.h
%include lx/RateRule.h
%include lx/Constraint.h
%include lx/Reaction.h
%include lx/KineticLaw.h
%include lx/SimpleSpeciesReference.h
%include lx/SpeciesReference.h
%include lx/ModifierSpeciesReference.h
%include lx/Event.h
%include lx/EventAssignment.h
%include lx/Trigger.h
%include lx/Delay.h
%include lx/Priority.h
%include lx/SBO.h
%include lx/SyntaxChecker.h
%include lx/StoichiometryMath.h
*/
/////%include liblx/xml/LibXMLNamespaces.h
//%include lx/LXTransforms.h
%include liblx/xml/XMLConstructorException.h

/*
%include lx/conversion/ConversionOption.h
%include lx/conversion/ConversionProperties.h
%include lx/conversion/LXConverter.h
%include lx/conversion/LXConverterRegistry.h
%include lx/conversion/LXFunctionDefinitionConverter.h
%include lx/conversion/LXIdConverter.h
%include lx/conversion/LXInferUnitsConverter.h
%include lx/conversion/LXInitialAssignmentConverter.h
%include lx/conversion/LXLevelVersionConverter.h
%include lx/conversion/LXLevel1Version1Converter.h
%include lx/conversion/LXLocalParameterConverter.h
%include lx/conversion/LXReactionConverter.h
%include lx/conversion/LXRuleConverter.h
%include lx/conversion/LXStripPackageConverter.h
%include lx/conversion/LXUnitsConverter.h
*/
/*
%include lx/validator/LXValidator.h
%include lx/validator/LXExternalValidator.h
*/
%include liblx/xml/XMLAttributes.h
%include liblx/xml/XMLConstructorException.h
%include liblx/xml/XMLNamespaces.h
%include liblx/xml/XMLToken.h
%include liblx/xml/XMLNode.h
%include liblx/xml/XMLTriple.h
%include liblx/xml/XMLOutputStream.h
%include liblx/xml/XMLInputStream.h
%include liblx/xml/XMLError.h
%include liblx/xml/XMLErrorLog.h

//%include liblx/LXErrorLog.h
%include liblx/xml/LibLXError.h

/*
%include lx/annotation/CVTerm.h
%include lx/annotation/Date.h
%include lx/annotation/ModelCreator.h
%include lx/annotation/ModelHistory.h
%include lx/annotation/RDFAnnotationParser.h
*/
/*
%include lx/extension/ILXExtensionNamespaces.h
%include lx/extension/SBaseExtensionPoint.h
%include lx/extension/SBasePlugin.h
%include lx/extension/LXDocumentPlugin.h
%include lx/extension/LXExtension.h
%include lx/extension/LXExtensionException.h
%include lx/extension/LXExtensionNamespaces.h
%include lx/extension/LXExtensionRegistry.h
*/
/*
%include lx/util/CallbackRegistry.h
*/

//%include ASTNodes.i

//%include "../swig/liblx-packages.i"
