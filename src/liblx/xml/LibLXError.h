/**
 * @file    LibLXError.h
 * @brief   Represents LibLX errors and other diagnostics
 * @author  Michael Hucka
 * @author  Sarah Keating
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
 * and also available online as http://lx.org/software/liblx/license.html
 * ------------------------------------------------------------------------ -->
 *
 * @class LXError
 * @lxbrief{core} An error, warning or other diagnostic.
 *
 * @htmlinclude not-lx-warning.html
 *
 * When a libLX operation on LX content results in an error, or when
 * there is something wrong with the LX content, the problems are
 * reported as LXError objects.  These are generally stored in an
 * LXErrorLog object; this log object, in turn, is kept in the
 * LXDocument object containing the LX content.  Applications can
 * obtain the list of logged errors using LXDocument::getErrorLog() and
 * then use the methods provided by LXErrorLog to access individual
 * LXError objects.  (Note that despite the word "error" in the name,
 * LXError objects are used to represent not only "true" errors, but also
 * warnings and some informational diagnostics.  The name is a historical
 * hold-over from early versions of libLX, in which the object really was
 * only used to report errors.)
 *
 * @if clike
 * Each LXError object instance has an identification number that
 * identifies the nature of the problem.  This "error id" number will be up
 * to five digits long, and it will be listed in one of two enumerations:
 * <a class="el" href="#LXErrorCode_t"> LXErrorCode_t</a> (described <a
 * class="el" href="#LXErrorCode_t"> below</a>) or @link
 * XMLError::XMLErrorCode_t XMLErrorCode_t@endlink (described in the
 * documentation for the class XMLError).  The former enumeration contains
 * all the LX validation rule numbers listed in the appendices of the
 * LX specification documents, as well as some additional
 * libLX-specific error codes.
 * @endif@if java
 * Each LXError object instance has an identification number that
 * identifies the nature of the problem.  This "error id" number will be up
 * to five digits long, and it will come from one of two sets of static
 * integer constants defined in the interface class <code><a
 * href="liblxConstants.html"> liblxConstants</a></code>: either the
 * LX error identifiers <a class="el" href="#LXErrorCode_t"> (described
 * below)</a> or the XML error identifiers (described in the documentation
 * for the class <code><a href="XMLError.html"> XMLError</a></code>).  The
 * former set of constants includes all the LX validation rule numbers
 * listed in the appendices of the LX specification documents, as well as
 * some additional libLX-specific error codes.
 * @endif@if python
 * Each LXError object instance has an identification number that
 * identifies the nature of the problem.  This "error id" number will be up
 * to five digits long, and it will come from one
 * of two sets of static integer constants defined in
 * the interface class @link liblx liblx@endlink: either the LX
 * error identifiers <a
 * class="el" href="#LXErrorCode_t"> (described below)</a> or the XML
 * error identifiers (described in the documentation for the class XMLError).
 * The former set of constants
 * includes all the LX validation rule numbers listed in the appendices
 * of the LX specification documents, as well as some additional
 * libLX-specific error codes.
 * @endif@~
 *
 * Error codes are useful mainly for software.  For human readers,
 * LXError also includes text messages that describe the nature of a
 * given problem.  The messages can be accessed using
 * LXError::getShortMessage() and LXError::getMessage().  The former
 * provides a brief one-line description of the issue, while
 * LXError::getMessage() provides a more detailed text, including (if
 * appropriate) references to sections of the LX specifications where
 * relevant topics are discussed.  These text strings are suitable for
 * displaying to human users.
 *
 * @if clike
 * An LXError object also contains a category code; its value may be
 * retrieved using the method LXError::getCategory().  Category values
 * are drawn from the enumeration <a class="el"
 * href="#LXErrorCategory_t">LXErrorCategory_t</a> described below.
 * Categories are used to partition errors into distinct conceptual groups.
 * This is principally used by the libLX validation system to group
 * classes of validation checks.  For example,
 * @lxconstant{LIBLX_CAT_IDENTIFIER_CONSISTENCY, LXErrorCategory_t}
 * is the category for tests that check identifier consistency;
 * @lxconstant{LIBLX_CAT_MATHML_CONSISTENCY, LXErrorCategory_t}
 * is the category for MathML consistency checking; and
 * so on.
 * @endif@if java
 * An LXError object also contains a category code; its value may be
 * retrieved using the method LXError::getCategory().  Category values
 * are drawn from a set of static integer constants
 * defined in <code><a href="liblxConstants.html">liblxConstants</a></code>,
 * and having names beginning with the characters
 * <code>LIBLX_CAT_</code>.  The list of possible codes is described in a
 * separate section below.  Categories are used to partition errors into
 * distinct conceptual groups.  This is principally used by the libLX
 * validation system to group classes of validation checks.  For example,
 * @lxconstant{LIBLX_CAT_IDENTIFIER_CONSISTENCY, LXErrorCategory_t}
 * is the category for tests that check identifier consistency;
 * @lxconstant{LIBLX_CAT_MATHML_CONSISTENCY, LXErrorCategory_t}
 * is the category for MathML consistency checking; and
 * so on.
 * @endif@if python
 * An LXError object also contains a category code; its value may be
 * retrieved using the method LXError::getCategory().  Category values
 * are drawn from a set of static integer constants
 * defined in @link liblx liblx@endlink and having names beginning with the characters
 * <code>LIBLX_CAT_</code>.  The list of possible codes is described in a
 * separate section below.  Categories are used to partition errors into
 * distinct conceptual groups.  This is principally used by the libLX
 * validation system to group classes of validation checks.  For example,
 * @lxconstant{LIBLX_CAT_IDENTIFIER_CONSISTENCY, LXErrorCategory_t}
 * is the category for tests that check identifier consistency;
 * @lxconstant{LIBLX_CAT_MATHML_CONSISTENCY, LXErrorCategory_t}
 * is the category for MathML consistency checking; and
 * so on.
 * @endif@~
 *
 * In addition, LXError also has a severity code.  Its value may be
 * retrieved using the method LXError::getSeverity().  The possible
 * severity values are the same as those reported by @if clike XMLError.@endif@if python XMLError.@endif@if java <code><a href="XMLError.html">XMLError</a></code>.@endif@~
 * Severity levels currently range from informational
 * (@lxconstant{LIBLX_SEV_INFO, XMLErrorSeverity_t})
 * to fatal errors
 * (@lxconstant{LIBLX_SEV_FATAL, XMLErrorSeverity_t}).
 * They can be
 * used by an application to evaluate how serious a given problem
 * is.
 *
 * LXError also tracks the Level&nbsp;3 package extension, if any, was
 * responsible for a given warning or error.  Each diagnostic code logged by
 * an libLX extension for LX Level&nbsp;3 packages includes a record of
 * the package that logged it.  It can be retrieved using
 * LXError::getPackage().  The information is a simple text string; the
 * string will be the nickname of the package, such as @c "comp" for the
 * Hierarchical %Model Composition package, @c "fbc" for the Flux Balance
 * Constraints package, and so on.  If the value returned by
 * LXError::getPackage() is an empty string or has the value @c "core",
 * then the error came from libLX core.
 *
 * Finally, LXError records the line and column near where the problem
 * occurred in the LX content.  The values may be retrieved using the
 * methods LXError::getLine() and LXError::getColumn().  We say "near",
 * because a lot of factors affect how accurate the line/column information
 * ultimately is.  For example, different XML parsers have different
 * conventions for which line and column number they report for a
 * particular problem (which makes a difference when a problem involves an
 * opening XML tag on one line and a closing tag on another line).  In some
 * situations, some parsers report invalid line and/or column numbers
 * altogether.  If this occurs, libLX sets the line and/or column number
 * in the LXError object to the the value of the maximum unsigned long
 * integer representable on the platform where libLX is running.  (This
 * is equal to the constant named <code>ULONG_MAX</code> in C and C++.)
 * The probability that a true line or column number in an LX model would
 * equal this value is vanishingly small; thus, if an application
 * encounters these values in an XMLError object, it can assume no valid
 * line/column number could be provided by libLX in that situation.
 *
 * @if clike
 * <h3><a class="anchor" name="LXErrorCode_t">LXErrorCode_t</a></h3>
 *
 * #LXErrorCode_t is an enumeration of all LX-level error, warning and
 * informational diagnostic codes.  Every LXError object has an error
 * code value that can be either a value from this enumeration, or a value
 * from the #XMLErrorCode_t
 * enumeration (see the documentation for XMLError).  The latter values
 * apply when the error or warning signifies a basic XML issue rather than
 * an LX issue per se.  The values of #LXErrorCode_t are distinguished
 * from those of #XMLErrorCode_t by
 * being numbered 10000 and higher, while the XML layer's codes are 9999 and
 * lower.  The method LXError::getErrorId() returns the error code of a
 * given LXError object instance.
 *
 * The following is a table of the symbolic names of #LXErrorCode_t values
 * and the meaning of each code.  In this table, the right-hand columns
 * titled "L1V1", "L1V2", etc. refer to Levels and Versions of the LX
 * specifications, and the entries in each column refer to whether the
 * severity of the condition in that particular Level+Version of LX.
 * The codes stand for the following:
 *
 * @endif@if java <h3><a class="anchor"
 * name="LXErrorCode_t">Error codes associated with LXError objects</a></h3>
 *
 * The error and warning codes returned by libLX are listed in the table
 * below.  The method LXError::getErrorId() returns the error code of a
 * given LXError object instance.  In the libLX Java language
 * interface, these error identifiers are currently
 * implemented as static integer constants defined in the interface class
 * <code><a href="liblxConstants.html">liblxConstants</a></code>.  This
 * is admittedly not an ideal approach from the standpoint of modern Java
 * programming, but it was necessary to work around the lack of
 * enumerations in Java prior to JDK 1.5.  Future versions of libLX may
 * use a proper Java enumeration type to define the error identifiers.
 *
 * In this table, the right-hand columns titled "L1V1", "L1V2", etc. refer
 * to Levels and Versions of the LX specifications, and the entries in
 * each column refer to whether the severity of the condition in that
 * particular Level+Version of LX.  The codes stand for the following:
 *
 * @endif@if python <h3><a class="anchor"
 * name="LXErrorCode_t">Error codes associated with LXError objects</a></h3>
 *
 * The error and warning codes returned by libLX are listed in the table
 * below.  The method LXError::getErrorId() returns the error code of a
 * given LXError object instance.  In the libLX Python language
 * interface, these error identifiers are currently
 * implemented as static integer constants defined in the interface class
 * @link liblx liblx@endlink.
 *
 * In this table, the right-hand columns titled "L1V1", "L1V2", etc. refer
 * to Levels and Versions of the LX specifications, and the entries in
 * each column refer to whether the severity of the condition in that
 * particular Level+Version of LX.  The codes stand for the following:
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
 * LXError::getShortMessage() method on a given LXError object.  A
 * longer and (hopefully) clearer explanation of the issue is returned by
 * LXError::getMessage().
 *
 * The error codes come from different lists depending on whether they're
 * from libLX core or from an LX Level&nbsp;3 package extension.
 * @if clike The errors below come from #XMLErrorCode_t and #LXErrorCode_t
 * (for core), and #CompLXErrorCode_t, #FbcLXErrorCode_t,
 * #LayoutLXErrorCode_t, and #QualLXErrorCode_t (for packages).@endif
 * @ifnot clike However, in the language interfaces other than C++, all
 * libLX error codes are ultimately represented as integer constants rather
 * than separate enumerations lists, and they are all stored in a single
 * interface class.  Codes from different libLX extensions have names that
 * begin with the package's nickname, such as <code>Qual</code> for
 * the Qualitative Models package, <code>Layout</code> for the Layout
 * package, and so on.  If the name of a code does not begin with one of
 * the package nicknames (<code>%Layout</code>, <code>Fbc</code>,
 * <code>Comp</code>, <code>Qual</code>, etc.), then it is a code
 * from libLX core.@endif
 *
 * @copydetails doc_lx_error_table
 *
 * @if clike <h3><a class="anchor" name="LXErrorCategory_t">LXErrorCategory_t</a></h3>
 *
 * #LXErrorCategory_t is an enumeration of category codes for LXError
 * diagnostics.  The category can be retrieved from an LXError object
 * using the method LXError::getCategory().  These enumeration values are
 * distinct from (and in addition to) the
 * #XMLErrorCategory_t codes used by
 * the parent XMLError object.  User programs receiving an LXError object
 * can use this distinction to check whether the error represents a
 * low-level XML problem or an LX problem.
 *
 * The following table lists each possible value and a brief description of
 * its meaning.
 *
 * @endif@if python <h3><a class="anchor" name="LXErrorCategory_t">Category codes associated with LXError objects</a></h3>
 *
 * As discussed above, each LXError object contains a value for a
 * category identifier, describing the type of issue that the LXError
 * object represents.  The category can be retrieved from an LXError
 * object using the method LXError::getCategory().  The following table
 * lists each possible value and a brief description of its meaning.
 *
 * As is the case with the error codes, in the libLX Python language
 * interface, the category identifiers are currently implemented as static
 * integer constants defined in the interface class
 * @link liblx liblx@endlink.
 *
 * The following table lists each possible value and a brief description of
 * its meaning.
 *
 * @endif@if java <h3><a class="anchor"
 * name="LXErrorCategory_t">Category codes associated with LXError objects</a></h3>
 *
 * As discussed above, each LXError object contains a value for a
 * category identifier, describing the type of issue that the LXError
 * object represents.  The category can be retrieved from an LXError
 * object using the method LXError::getCategory().  The following table
 * lists each possible value and a brief description of its meaning.
 *
 * As is the case with the error codes, in the libLX Java language
 * interface, the category identifiers are currently implemented as static
 * integer constants defined in the interface class
 * {@link liblxConstants}.
 *
 * The following table lists each possible value and a brief description of
 * its meaning.
 *
 * @endif@if csharp <h3><a class="anchor"
 * name="LXErrorCategory_t">Category codes associated with LXError objects</a></h3>
 *
 * As discussed above, each LXError object contains a value for a
 * category identifier, describing the type of issue that the LXError
 * object represents.  The category can be retrieved from an LXError
 * object using the method LXError::getCategory().  The following table
 * lists each possible value and a brief description of its meaning.
 *
 * As is the case with the error codes, in the libLX C# language
 * interface, the category identifiers are currently implemented as static
 * integer constants defined in the interface class
 * {@link liblxcs.liblx}.
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
 * <tr><td>@lxconstant{LIBLX_CAT_LX, XMLErrorCategory_t}</td><td>General error not falling into
 * another category below.</td></tr>
 * <tr><td>@lxconstant{LIBLX_CAT_LX_L1_COMPAT, XMLErrorCategory_t}</td><td>Category of errors
 * that can only occur during attempted translation from one Level/Version
 * of LX to another.  This particular category applies to errors
 * encountered while trying to convert a model from LX Level&nbsp;2 to LX
 * Level&nbsp;1.</td></tr>
 * <tr><td>@lxconstant{LIBLX_CAT_LX_L2V1_COMPAT, XMLErrorCategory_t}</td><td>Category of errors
 * that can only occur during attempted translation from one Level/Version
 * of LX to another.  This particular category applies to errors
 * encountered while trying to convert a model to LX Level&nbsp;2
 * Version&nbsp;1.</td></tr>
 * <tr><td>@lxconstant{LIBLX_CAT_LX_L2V2_COMPAT, XMLErrorCategory_t}</td><td>Category of errors
 * that can only occur during attempted translation from one Level/Version
 * of LX to another.  This particular category applies to errors
 * encountered while trying to convert a model to LX Level&nbsp;2
 * Version&nbsp;2.</td></tr>
 * <tr><td>@lxconstant{LIBLX_CAT_GENERAL_CONSISTENCY, XMLErrorCategory_t}</td><td>Category of
 * errors that can occur while validating general LX constructs.  With
 * respect to the LX specification, these concern failures in applying
 * the validation rules numbered 2xxxx in the Level&nbsp;2 Versions&nbsp;2&ndash;4
 * and Level&nbsp;3 Versions&nbsp;1&ndash;2 specifications.</td></tr>
 * <tr><td>@lxconstant{LIBLX_CAT_IDENTIFIER_CONSISTENCY, XMLErrorCategory_t}</td><td>Category of
 * errors that can occur while validating symbol identifiers in a model.
 * With respect to the LX specification, these concern failures in
 * applying the validation rules numbered 103xx in the Level&nbsp;2 Versions&nbsp;2&ndash;4
 * and Level&nbsp;3 Versions&nbsp;1&ndash;2 specifications.</td></tr>
 * <tr><td>@lxconstant{LIBLX_CAT_UNITS_CONSISTENCY, XMLErrorCategory_t}</td><td>Category of
 * errors that can occur while validating the units of measurement on
 * quantities in a model.  With respect to the LX specification, these
 * concern failures in applying the validation rules numbered 105xx in the
 * Level&nbsp;2 Versions&nbsp;2&ndash;4
 * and Level&nbsp;3 Versions&nbsp;1&ndash;2 specifications.</td></tr>
 * <tr><td>@lxconstant{LIBLX_CAT_MATHML_CONSISTENCY, XMLErrorCategory_t}</td><td>Category of
 * errors that can occur while validating MathML formulas in a model.  With
 * respect to the LX specification, these concern failures in applying
 * the validation rules numbered 102xx in the Level&nbsp;2 Versions&nbsp;2&ndash;4
 * and Level&nbsp;3 Versions&nbsp;1&ndash;2 specifications.</td></tr>
 * <tr><td>@lxconstant{LIBLX_CAT_SBO_CONSISTENCY, XMLErrorCategory_t}</td><td>Category of errors
 * that can occur while validating SBO identifiers in a model.  With
 * respect to the LX specification, these concern failures in applying
 * the validation rules numbered 107xx in the Level&nbsp;2 Versions&nbsp;2&ndash;4
 * and Level&nbsp;3 Versions&nbsp;1&ndash;2 specifications.</td></tr>
 * <tr><td>@lxconstant{LIBLX_CAT_OVERDETERMINED_MODEL, XMLErrorCategory_t}</td><td>Error in the
 * system of equations in the model: the system is overdetermined,
 * therefore violating a tenet of proper LX.  With respect to the LX
 * specification, this is validation rule #10601 in the LX Level&nbsp;2 Versions&nbsp;2&ndash;4
 * and Level&nbsp;3 Versions&nbsp;1&ndash;2 specifications.</td></tr>
 * <tr><td>@lxconstant{LIBLX_CAT_LX_L2V3_COMPAT, XMLErrorCategory_t}</td><td>Category of errors
 * that can only occur during attempted translation from one Level/Version
 * of LX to another.  This particular category applies to errors
 * encountered while trying to convert a model to LX Level&nbsp;2
 * Version&nbsp;3.</td></tr>
 * <tr><td>@lxconstant{LIBLX_CAT_MODELING_PRACTICE, XMLErrorCategory_t}</td><td>Category of
 * warnings about recommended good practices involving LX and
 * computational modeling.  (These are tests performed by libLX and do
 * not have equivalent LX validation rules.)</td></tr>
 * <tr><td>@lxconstant{LIBLX_CAT_INTERNAL_CONSISTENCY, XMLErrorCategory_t}</td><td>Category of
 * errors that can occur while validating libLX's internal representation
 * of LX constructs. (These are tests performed by libLX and do
 * not have equivalent LX validation rules.)</td></tr>
 * <tr><td>@lxconstant{LIBLX_CAT_LX_L2V4_COMPAT, XMLErrorCategory_t}</td><td>Category of errors
 * that can only occur during attempted translation from one Level/Version
 * of LX to another.  This particular category applies to errors
 * encountered while trying to convert a model to LX Level&nbsp;2
 * Version&nbsp;4.</td></tr>
 * <tr><td>@lxconstant{LIBLX_CAT_LX_L3V1_COMPAT, XMLErrorCategory_t}</td><td>Category of errors
 * that can only occur during attempted translation from one Level/Version
 * of LX to another.  This particular category applies to errors
 * encountered while trying to convert a model to LX Level&nbsp;3
 * Version&nbsp;1.</td></tr>
 *
 * </table>
 * </center>
 *
 * @if clike
 * <h3><a class="anchor" name="LXErrorSeverity_t">LXErrorSeverity_t</a></h3>
 *
 * This is an enumeration of severity codes for LXError diagnostics.
 * User programs receiving an LXError object can use this distinction to
 * check whether the error represents a low-level XML problem or an LX
 * problem.
 *
 * In libLX version @htmlinclude liblx-version.html
 * there are no additional severity codes in
 * #LXErrorSeverity_t beyond those defined in #XMLErrorSeverity_t.
 *
 * <hr>
 * @endif@if java <h3><a class="anchor"
 * name="LXErrorSeverity_t">Severity codes associated with LXError
 * objects</h3>
 *
 * In libLX version @htmlinclude liblx-version.html
 * there are no additional severity codes beyond those defined by XMLError.
 * They are implemented as static integer constants defined in the interface
 * class <code><a href="liblxConstants.html">liblxConstants</a></code>,
 * and have names beginning with <code>LIBLX_SEV_</code>.
 * @endif@if python <h3><a class="anchor"
 * name="LXErrorSeverity_t">Severity codes associated with LXError
 * objects</h3>
 *
 * In libLX version @htmlinclude liblx-version.html
 * there are no additional severity codes beyond those defined by XMLError.
 * They are implemented as static integer constants defined in the
 * interface class @link liblx liblx@endlink, and have names beginning
 * with <code>LIBLX_SEV_</code>.
 * @endif@~
 */

#ifndef LIBLXERROR_H
#define LIBLXERROR_H

#include <liblx/xml/XMLError.h>
#include <liblx/common/operationReturnValues.h>

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
  /** @cond doxygenLiblxInternal **/

  /* The following is used in initializing the XMLError class   */

  LIBLX_SEV_UNKNOWN = (LIBLX_SEV_FATAL + SEVERITY_OFFSET)
  /*!< This error code is used as the default argument to the XMLError constructor, so the constructor can know if the caller deliberately set the severity or not. */

  /** @endcond **/
} LibLXErrorSeverity_t;

#endif /* LIBLXERROR_H */
