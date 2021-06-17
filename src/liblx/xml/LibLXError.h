/**
 * @file    LibLXError.h
 * @brief   Represents LibLX errors and other diagnostics
 * @author  Michael Hucka
 * @author  Sarah Keating
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
 * ------------------------------------------------------------------------ -->
 *
 * @class SBMLError
 * @sbmlbrief{core} An error, warning or other diagnostic.
 *
 * @htmlinclude not-sbml-warning.html
 *
 * When a libSBML operation on SBML content results in an error, or when
 * there is something wrong with the SBML content, the problems are
 * reported as SBMLError objects.  These are generally stored in an
 * SBMLErrorLog object; this log object, in turn, is kept in the
 * SBMLDocument object containing the SBML content.  Applications can
 * obtain the list of logged errors using SBMLDocument::getErrorLog() and
 * then use the methods provided by SBMLErrorLog to access individual
 * SBMLError objects.  (Note that despite the word "error" in the name,
 * SBMLError objects are used to represent not only "true" errors, but also
 * warnings and some informational diagnostics.  The name is a historical
 * hold-over from early versions of libSBML, in which the object really was
 * only used to report errors.)
 *
 * @if clike
 * Each SBMLError object instance has an identification number that
 * identifies the nature of the problem.  This "error id" number will be up
 * to five digits long, and it will be listed in one of two enumerations:
 * <a class="el" href="#SBMLErrorCode_t"> SBMLErrorCode_t</a> (described <a
 * class="el" href="#SBMLErrorCode_t"> below</a>) or @link
 * XMLError::XMLErrorCode_t XMLErrorCode_t@endlink (described in the
 * documentation for the class XMLError).  The former enumeration contains
 * all the SBML validation rule numbers listed in the appendices of the
 * SBML specification documents, as well as some additional
 * libSBML-specific error codes.
 * @endif@if java
 * Each SBMLError object instance has an identification number that
 * identifies the nature of the problem.  This "error id" number will be up
 * to five digits long, and it will come from one of two sets of static
 * integer constants defined in the interface class <code><a
 * href="libsbmlConstants.html"> libsbmlConstants</a></code>: either the
 * SBML error identifiers <a class="el" href="#SBMLErrorCode_t"> (described
 * below)</a> or the XML error identifiers (described in the documentation
 * for the class <code><a href="XMLError.html"> XMLError</a></code>).  The
 * former set of constants includes all the SBML validation rule numbers
 * listed in the appendices of the SBML specification documents, as well as
 * some additional libSBML-specific error codes.
 * @endif@if python
 * Each SBMLError object instance has an identification number that
 * identifies the nature of the problem.  This "error id" number will be up
 * to five digits long, and it will come from one
 * of two sets of static integer constants defined in
 * the interface class @link libsbml libsbml@endlink: either the SBML
 * error identifiers <a
 * class="el" href="#SBMLErrorCode_t"> (described below)</a> or the XML
 * error identifiers (described in the documentation for the class XMLError).
 * The former set of constants
 * includes all the SBML validation rule numbers listed in the appendices
 * of the SBML specification documents, as well as some additional
 * libSBML-specific error codes.
 * @endif@~
 *
 * Error codes are useful mainly for software.  For human readers,
 * SBMLError also includes text messages that describe the nature of a
 * given problem.  The messages can be accessed using
 * SBMLError::getShortMessage() and SBMLError::getMessage().  The former
 * provides a brief one-line description of the issue, while
 * SBMLError::getMessage() provides a more detailed text, including (if
 * appropriate) references to sections of the SBML specifications where
 * relevant topics are discussed.  These text strings are suitable for
 * displaying to human users.
 *
 * @if clike
 * An SBMLError object also contains a category code; its value may be
 * retrieved using the method SBMLError::getCategory().  Category values
 * are drawn from the enumeration <a class="el"
 * href="#SBMLErrorCategory_t">SBMLErrorCategory_t</a> described below.
 * Categories are used to partition errors into distinct conceptual groups.
 * This is principally used by the libSBML validation system to group
 * classes of validation checks.  For example,
 * @sbmlconstant{LIBLX_CAT_IDENTIFIER_CONSISTENCY, SBMLErrorCategory_t}
 * is the category for tests that check identifier consistency;
 * @sbmlconstant{LIBLX_CAT_MATHML_CONSISTENCY, SBMLErrorCategory_t}
 * is the category for MathML consistency checking; and
 * so on.
 * @endif@if java
 * An SBMLError object also contains a category code; its value may be
 * retrieved using the method SBMLError::getCategory().  Category values
 * are drawn from a set of static integer constants
 * defined in <code><a href="libsbmlConstants.html">libsbmlConstants</a></code>,
 * and having names beginning with the characters
 * <code>LIBLX_CAT_</code>.  The list of possible codes is described in a
 * separate section below.  Categories are used to partition errors into
 * distinct conceptual groups.  This is principally used by the libSBML
 * validation system to group classes of validation checks.  For example,
 * @sbmlconstant{LIBLX_CAT_IDENTIFIER_CONSISTENCY, SBMLErrorCategory_t}
 * is the category for tests that check identifier consistency;
 * @sbmlconstant{LIBLX_CAT_MATHML_CONSISTENCY, SBMLErrorCategory_t}
 * is the category for MathML consistency checking; and
 * so on.
 * @endif@if python
 * An SBMLError object also contains a category code; its value may be
 * retrieved using the method SBMLError::getCategory().  Category values
 * are drawn from a set of static integer constants
 * defined in @link libsbml libsbml@endlink and having names beginning with the characters
 * <code>LIBLX_CAT_</code>.  The list of possible codes is described in a
 * separate section below.  Categories are used to partition errors into
 * distinct conceptual groups.  This is principally used by the libSBML
 * validation system to group classes of validation checks.  For example,
 * @sbmlconstant{LIBLX_CAT_IDENTIFIER_CONSISTENCY, SBMLErrorCategory_t}
 * is the category for tests that check identifier consistency;
 * @sbmlconstant{LIBLX_CAT_MATHML_CONSISTENCY, SBMLErrorCategory_t}
 * is the category for MathML consistency checking; and
 * so on.
 * @endif@~
 *
 * In addition, SBMLError also has a severity code.  Its value may be
 * retrieved using the method SBMLError::getSeverity().  The possible
 * severity values are the same as those reported by @if clike XMLError.@endif@if python XMLError.@endif@if java <code><a href="XMLError.html">XMLError</a></code>.@endif@~
 * Severity levels currently range from informational
 * (@sbmlconstant{LIBLX_SEV_INFO, XMLErrorSeverity_t})
 * to fatal errors
 * (@sbmlconstant{LIBLX_SEV_FATAL, XMLErrorSeverity_t}).
 * They can be
 * used by an application to evaluate how serious a given problem
 * is.
 *
 * SBMLError also tracks the Level&nbsp;3 package extension, if any, was
 * responsible for a given warning or error.  Each diagnostic code logged by
 * an libSBML extension for SBML Level&nbsp;3 packages includes a record of
 * the package that logged it.  It can be retrieved using
 * SBMLError::getPackage().  The information is a simple text string; the
 * string will be the nickname of the package, such as @c "comp" for the
 * Hierarchical %Model Composition package, @c "fbc" for the Flux Balance
 * Constraints package, and so on.  If the value returned by
 * SBMLError::getPackage() is an empty string or has the value @c "core",
 * then the error came from libSBML core.
 *
 * Finally, SBMLError records the line and column near where the problem
 * occurred in the SBML content.  The values may be retrieved using the
 * methods SBMLError::getLine() and SBMLError::getColumn().  We say "near",
 * because a lot of factors affect how accurate the line/column information
 * ultimately is.  For example, different XML parsers have different
 * conventions for which line and column number they report for a
 * particular problem (which makes a difference when a problem involves an
 * opening XML tag on one line and a closing tag on another line).  In some
 * situations, some parsers report invalid line and/or column numbers
 * altogether.  If this occurs, libSBML sets the line and/or column number
 * in the SBMLError object to the the value of the maximum unsigned long
 * integer representable on the platform where libSBML is running.  (This
 * is equal to the constant named <code>ULONG_MAX</code> in C and C++.)
 * The probability that a true line or column number in an SBML model would
 * equal this value is vanishingly small; thus, if an application
 * encounters these values in an XMLError object, it can assume no valid
 * line/column number could be provided by libSBML in that situation.
 *
 * @if clike
 * <h3><a class="anchor" name="SBMLErrorCode_t">SBMLErrorCode_t</a></h3>
 *
 * #SBMLErrorCode_t is an enumeration of all SBML-level error, warning and
 * informational diagnostic codes.  Every SBMLError object has an error
 * code value that can be either a value from this enumeration, or a value
 * from the #XMLErrorCode_t
 * enumeration (see the documentation for XMLError).  The latter values
 * apply when the error or warning signifies a basic XML issue rather than
 * an SBML issue per se.  The values of #SBMLErrorCode_t are distinguished
 * from those of #XMLErrorCode_t by
 * being numbered 10000 and higher, while the XML layer's codes are 9999 and
 * lower.  The method SBMLError::getErrorId() returns the error code of a
 * given SBMLError object instance.
 *
 * The following is a table of the symbolic names of #SBMLErrorCode_t values
 * and the meaning of each code.  In this table, the right-hand columns
 * titled "L1V1", "L1V2", etc. refer to Levels and Versions of the SBML
 * specifications, and the entries in each column refer to whether the
 * severity of the condition in that particular Level+Version of SBML.
 * The codes stand for the following:
 *
 * @endif@if java <h3><a class="anchor"
 * name="SBMLErrorCode_t">Error codes associated with SBMLError objects</a></h3>
 *
 * The error and warning codes returned by libSBML are listed in the table
 * below.  The method SBMLError::getErrorId() returns the error code of a
 * given SBMLError object instance.  In the libSBML Java language
 * interface, these error identifiers are currently
 * implemented as static integer constants defined in the interface class
 * <code><a href="libsbmlConstants.html">libsbmlConstants</a></code>.  This
 * is admittedly not an ideal approach from the standpoint of modern Java
 * programming, but it was necessary to work around the lack of
 * enumerations in Java prior to JDK 1.5.  Future versions of libSBML may
 * use a proper Java enumeration type to define the error identifiers.
 *
 * In this table, the right-hand columns titled "L1V1", "L1V2", etc. refer
 * to Levels and Versions of the SBML specifications, and the entries in
 * each column refer to whether the severity of the condition in that
 * particular Level+Version of SBML.  The codes stand for the following:
 *
 * @endif@if python <h3><a class="anchor"
 * name="SBMLErrorCode_t">Error codes associated with SBMLError objects</a></h3>
 *
 * The error and warning codes returned by libSBML are listed in the table
 * below.  The method SBMLError::getErrorId() returns the error code of a
 * given SBMLError object instance.  In the libSBML Python language
 * interface, these error identifiers are currently
 * implemented as static integer constants defined in the interface class
 * @link libsbml libsbml@endlink.
 *
 * In this table, the right-hand columns titled "L1V1", "L1V2", etc. refer
 * to Levels and Versions of the SBML specifications, and the entries in
 * each column refer to whether the severity of the condition in that
 * particular Level+Version of SBML.  The codes stand for the following:
 *
 * @endif@~
 *
 * <table cellspacing="1" cellpadding="2" border="0" class="normal-font">
 * <tr><td class="s-na"></td><td>= Not applicable</td></tr>
 * <tr><td class="s-warning"></td><td>= Warning</td></tr>
 * <tr><td class="s-error"></td><td>= Error</td></tr>
 * <tr><td class="s-fatal"></td><td>= Fatal</td></tr>
 * </table>
 *
 * The text shown in the "Meaning" is the text returned by the
 * SBMLError::getShortMessage() method on a given SBMLError object.  A
 * longer and (hopefully) clearer explanation of the issue is returned by
 * SBMLError::getMessage().
 *
 * The error codes come from different lists depending on whether they're
 * from libSBML core or from an SBML Level&nbsp;3 package extension.
 * @if clike The errors below come from #XMLErrorCode_t and #SBMLErrorCode_t
 * (for core), and #CompSBMLErrorCode_t, #FbcSBMLErrorCode_t,
 * #LayoutSBMLErrorCode_t, and #QualSBMLErrorCode_t (for packages).@endif
 * @ifnot clike However, in the language interfaces other than C++, all
 * libSBML error codes are ultimately represented as integer constants rather
 * than separate enumerations lists, and they are all stored in a single
 * interface class.  Codes from different libSBML extensions have names that
 * begin with the package's nickname, such as <code>Qual</code> for
 * the Qualitative Models package, <code>Layout</code> for the Layout
 * package, and so on.  If the name of a code does not begin with one of
 * the package nicknames (<code>%Layout</code>, <code>Fbc</code>,
 * <code>Comp</code>, <code>Qual</code>, etc.), then it is a code
 * from libSBML core.@endif
 *
 * @copydetails doc_sbml_error_table
 *
 * @if clike <h3><a class="anchor" name="SBMLErrorCategory_t">SBMLErrorCategory_t</a></h3>
 *
 * #SBMLErrorCategory_t is an enumeration of category codes for SBMLError
 * diagnostics.  The category can be retrieved from an SBMLError object
 * using the method SBMLError::getCategory().  These enumeration values are
 * distinct from (and in addition to) the
 * #XMLErrorCategory_t codes used by
 * the parent XMLError object.  User programs receiving an SBMLError object
 * can use this distinction to check whether the error represents a
 * low-level XML problem or an SBML problem.
 *
 * The following table lists each possible value and a brief description of
 * its meaning.
 *
 * @endif@if python <h3><a class="anchor" name="SBMLErrorCategory_t">Category codes associated with SBMLError objects</a></h3>
 *
 * As discussed above, each SBMLError object contains a value for a
 * category identifier, describing the type of issue that the SBMLError
 * object represents.  The category can be retrieved from an SBMLError
 * object using the method SBMLError::getCategory().  The following table
 * lists each possible value and a brief description of its meaning.
 *
 * As is the case with the error codes, in the libSBML Python language
 * interface, the category identifiers are currently implemented as static
 * integer constants defined in the interface class
 * @link libsbml libsbml@endlink.
 *
 * The following table lists each possible value and a brief description of
 * its meaning.
 *
 * @endif@if java <h3><a class="anchor"
 * name="SBMLErrorCategory_t">Category codes associated with SBMLError objects</a></h3>
 *
 * As discussed above, each SBMLError object contains a value for a
 * category identifier, describing the type of issue that the SBMLError
 * object represents.  The category can be retrieved from an SBMLError
 * object using the method SBMLError::getCategory().  The following table
 * lists each possible value and a brief description of its meaning.
 *
 * As is the case with the error codes, in the libSBML Java language
 * interface, the category identifiers are currently implemented as static
 * integer constants defined in the interface class
 * {@link libsbmlConstants}.
 *
 * The following table lists each possible value and a brief description of
 * its meaning.
 *
 * @endif@if csharp <h3><a class="anchor"
 * name="SBMLErrorCategory_t">Category codes associated with SBMLError objects</a></h3>
 *
 * As discussed above, each SBMLError object contains a value for a
 * category identifier, describing the type of issue that the SBMLError
 * object represents.  The category can be retrieved from an SBMLError
 * object using the method SBMLError::getCategory().  The following table
 * lists each possible value and a brief description of its meaning.
 *
 * As is the case with the error codes, in the libSBML C# language
 * interface, the category identifiers are currently implemented as static
 * integer constants defined in the interface class
 * {@link libsbmlcs.libsbml}.
 *
 * The following table lists each possible value and a brief description of
 * its meaning.
 *
 * @endif@~
 *
 * <center>
 * <table width="90%" cellspacing="1" cellpadding="4" border="0"  class="text-table normal-font alt-row-colors">
 *  <tr style="background: lightgray" class="normal-font">
 *      <th>Enumerator</td>
 *      <th>Meaning</td>
 *  </tr>
 * <tr><td>@sbmlconstant{LIBLX_CAT_SBML, XMLErrorCategory_t}</td><td>General error not falling into
 * another category below.</td></tr>
 * <tr><td>@sbmlconstant{LIBLX_CAT_SBML_L1_COMPAT, XMLErrorCategory_t}</td><td>Category of errors
 * that can only occur during attempted translation from one Level/Version
 * of SBML to another.  This particular category applies to errors
 * encountered while trying to convert a model from SBML Level&nbsp;2 to SBML
 * Level&nbsp;1.</td></tr>
 * <tr><td>@sbmlconstant{LIBLX_CAT_SBML_L2V1_COMPAT, XMLErrorCategory_t}</td><td>Category of errors
 * that can only occur during attempted translation from one Level/Version
 * of SBML to another.  This particular category applies to errors
 * encountered while trying to convert a model to SBML Level&nbsp;2
 * Version&nbsp;1.</td></tr>
 * <tr><td>@sbmlconstant{LIBLX_CAT_SBML_L2V2_COMPAT, XMLErrorCategory_t}</td><td>Category of errors
 * that can only occur during attempted translation from one Level/Version
 * of SBML to another.  This particular category applies to errors
 * encountered while trying to convert a model to SBML Level&nbsp;2
 * Version&nbsp;2.</td></tr>
 * <tr><td>@sbmlconstant{LIBLX_CAT_GENERAL_CONSISTENCY, XMLErrorCategory_t}</td><td>Category of
 * errors that can occur while validating general SBML constructs.  With
 * respect to the SBML specification, these concern failures in applying
 * the validation rules numbered 2xxxx in the Level&nbsp;2 Versions&nbsp;2&ndash;4
 * and Level&nbsp;3 Versions&nbsp;1&ndash;2 specifications.</td></tr>
 * <tr><td>@sbmlconstant{LIBLX_CAT_IDENTIFIER_CONSISTENCY, XMLErrorCategory_t}</td><td>Category of
 * errors that can occur while validating symbol identifiers in a model.
 * With respect to the SBML specification, these concern failures in
 * applying the validation rules numbered 103xx in the Level&nbsp;2 Versions&nbsp;2&ndash;4
 * and Level&nbsp;3 Versions&nbsp;1&ndash;2 specifications.</td></tr>
 * <tr><td>@sbmlconstant{LIBLX_CAT_UNITS_CONSISTENCY, XMLErrorCategory_t}</td><td>Category of
 * errors that can occur while validating the units of measurement on
 * quantities in a model.  With respect to the SBML specification, these
 * concern failures in applying the validation rules numbered 105xx in the
 * Level&nbsp;2 Versions&nbsp;2&ndash;4
 * and Level&nbsp;3 Versions&nbsp;1&ndash;2 specifications.</td></tr>
 * <tr><td>@sbmlconstant{LIBLX_CAT_MATHML_CONSISTENCY, XMLErrorCategory_t}</td><td>Category of
 * errors that can occur while validating MathML formulas in a model.  With
 * respect to the SBML specification, these concern failures in applying
 * the validation rules numbered 102xx in the Level&nbsp;2 Versions&nbsp;2&ndash;4
 * and Level&nbsp;3 Versions&nbsp;1&ndash;2 specifications.</td></tr>
 * <tr><td>@sbmlconstant{LIBLX_CAT_SBO_CONSISTENCY, XMLErrorCategory_t}</td><td>Category of errors
 * that can occur while validating SBO identifiers in a model.  With
 * respect to the SBML specification, these concern failures in applying
 * the validation rules numbered 107xx in the Level&nbsp;2 Versions&nbsp;2&ndash;4
 * and Level&nbsp;3 Versions&nbsp;1&ndash;2 specifications.</td></tr>
 * <tr><td>@sbmlconstant{LIBLX_CAT_OVERDETERMINED_MODEL, XMLErrorCategory_t}</td><td>Error in the
 * system of equations in the model: the system is overdetermined,
 * therefore violating a tenet of proper SBML.  With respect to the SBML
 * specification, this is validation rule #10601 in the SBML Level&nbsp;2 Versions&nbsp;2&ndash;4
 * and Level&nbsp;3 Versions&nbsp;1&ndash;2 specifications.</td></tr>
 * <tr><td>@sbmlconstant{LIBLX_CAT_SBML_L2V3_COMPAT, XMLErrorCategory_t}</td><td>Category of errors
 * that can only occur during attempted translation from one Level/Version
 * of SBML to another.  This particular category applies to errors
 * encountered while trying to convert a model to SBML Level&nbsp;2
 * Version&nbsp;3.</td></tr>
 * <tr><td>@sbmlconstant{LIBLX_CAT_MODELING_PRACTICE, XMLErrorCategory_t}</td><td>Category of
 * warnings about recommended good practices involving SBML and
 * computational modeling.  (These are tests performed by libSBML and do
 * not have equivalent SBML validation rules.)</td></tr>
 * <tr><td>@sbmlconstant{LIBLX_CAT_INTERNAL_CONSISTENCY, XMLErrorCategory_t}</td><td>Category of
 * errors that can occur while validating libSBML's internal representation
 * of SBML constructs. (These are tests performed by libSBML and do
 * not have equivalent SBML validation rules.)</td></tr>
 * <tr><td>@sbmlconstant{LIBLX_CAT_SBML_L2V4_COMPAT, XMLErrorCategory_t}</td><td>Category of errors
 * that can only occur during attempted translation from one Level/Version
 * of SBML to another.  This particular category applies to errors
 * encountered while trying to convert a model to SBML Level&nbsp;2
 * Version&nbsp;4.</td></tr>
 * <tr><td>@sbmlconstant{LIBLX_CAT_SBML_L3V1_COMPAT, XMLErrorCategory_t}</td><td>Category of errors
 * that can only occur during attempted translation from one Level/Version
 * of SBML to another.  This particular category applies to errors
 * encountered while trying to convert a model to SBML Level&nbsp;3
 * Version&nbsp;1.</td></tr>
 *
 * </table>
 * </center>
 *
 * @if clike
 * <h3><a class="anchor" name="SBMLErrorSeverity_t">SBMLErrorSeverity_t</a></h3>
 *
 * This is an enumeration of severity codes for SBMLError diagnostics.
 * User programs receiving an SBMLError object can use this distinction to
 * check whether the error represents a low-level XML problem or an SBML
 * problem.
 *
 * In libSBML version @htmlinclude libsbml-version.html
 * there are no additional severity codes in
 * #SBMLErrorSeverity_t beyond those defined in #XMLErrorSeverity_t.
 *
 * <hr>
 * @endif@if java <h3><a class="anchor"
 * name="SBMLErrorSeverity_t">Severity codes associated with SBMLError
 * objects</h3>
 *
 * In libSBML version @htmlinclude libsbml-version.html
 * there are no additional severity codes beyond those defined by XMLError.
 * They are implemented as static integer constants defined in the interface
 * class <code><a href="libsbmlConstants.html">libsbmlConstants</a></code>,
 * and have names beginning with <code>LIBLX_SEV_</code>.
 * @endif@if python <h3><a class="anchor"
 * name="SBMLErrorSeverity_t">Severity codes associated with SBMLError
 * objects</h3>
 *
 * In libSBML version @htmlinclude libsbml-version.html
 * there are no additional severity codes beyond those defined by XMLError.
 * They are implemented as static integer constants defined in the
 * interface class @link libsbml libsbml@endlink, and have names beginning
 * with <code>LIBLX_SEV_</code>.
 * @endif@~
 */

#ifndef LIBLXERROR_H
#define LIBLXERROR_H

#include "liblx/xml/XMLError.h"

#define SEVERITY_OFFSET 3

/**
 * @enum LibLXErrorSeverity_t
 * Severity codes for LibLXError diagnostics.
 *
 * The only publicly-reported values of this type are the four from #XMLErrorSeverity_t.
 *
 * @see XMLErrorSeverity_t
 */
typedef enum
{
  /** @cond doxygenLibsbmlInternal **/

  /* The following is used in initializing the XMLError class   */

  LIBLX_SEV_UNKNOWN = (LIBLX_SEV_FATAL + SEVERITY_OFFSET)
  /*!< This error code is used as the default argument to the XMLError constructor, so the constructor can know if the caller deliberately set the severity or not. */

  /** @endcond **/
} LibLXErrorSeverity_t;

#endif /* LIBLXERROR_H */
