/**
 * \file    libsbml.h
 * \brief   Language-independent SWIG includes for wrapping libSBML
 * \author  Ben Bornstein
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
 * ---------------------------------------------------------------------- -->*/

#include <liblx/common/libsbml-version.h>
#include <liblx/common/operationReturnValues.h>

#include <liblx/util/IdList.h>
#include <liblx/util/IdentifierTransformer.h>
#include <liblx/util/ElementFilter.h>

#include <liblx/SBMLReader.h>
#include <liblx/SBMLWriter.h>
#include <liblx/UnitKind.h>
#include <liblx/SBMLTypeCodes.h>
#include <liblx/SBase.h>
#include <liblx/ListOf.h>
#include <liblx/Model.h>
#include <liblx/SBMLDocument.h>
#include <liblx/SBMLError.h>
#include <liblx/SBMLErrorLog.h>
#include <liblx/SBMLNamespaces.h>
#include <liblx/FunctionDefinition.h>
#include <liblx/Unit.h>
#include <liblx/UnitDefinition.h>
#include <liblx/CompartmentType.h>
#include <liblx/SpeciesType.h>
#include <liblx/Compartment.h>
#include <liblx/Species.h>
#include <liblx/Parameter.h>
#include <liblx/LocalParameter.h>
#include <liblx/InitialAssignment.h>
#include <liblx/Rule.h>
#include <liblx/AlgebraicRule.h>
#include <liblx/AssignmentRule.h>
#include <liblx/RateRule.h>
#include <liblx/Constraint.h>
#include <liblx/Reaction.h>
#include <liblx/KineticLaw.h>
#include <liblx/SimpleSpeciesReference.h>
#include <liblx/SpeciesReference.h>
#include <liblx/ModifierSpeciesReference.h>
#include <liblx/Event.h>
#include <liblx/EventAssignment.h>
#include <liblx/Trigger.h>
#include <liblx/Delay.h>
#include <liblx/CompartmentType.h>
#include <liblx/Constraint.h>
#include <liblx/InitialAssignment.h>
#include <liblx/SpeciesType.h>
#include <liblx/SBO.h>
#include <liblx/SyntaxChecker.h>
#include <liblx/StoichiometryMath.h>
#include <liblx/SBMLNamespaces.h>
#include <liblx/SBMLTransforms.h>
#include <liblx/SBMLConstructorException.h>

#include <liblx/conversion/ConversionOption.h>
#include <liblx/conversion/ConversionProperties.h>
#include <liblx/conversion/SBMLConverter.h>
#include <liblx/conversion/SBMLConverterRegistry.h>
#include <liblx/conversion/SBMLFunctionDefinitionConverter.h>
#include <liblx/conversion/SBMLIdConverter.h>
#include <liblx/conversion/SBMLInferUnitsConverter.h>
#include <liblx/conversion/SBMLInitialAssignmentConverter.h>
#include <liblx/conversion/SBMLLevelVersionConverter.h>
#include <liblx/conversion/SBMLLevel1Version1Converter.h>
#include <liblx/conversion/SBMLLocalParameterConverter.h>
#include <liblx/conversion/SBMLReactionConverter.h>
#include <liblx/conversion/SBMLRuleConverter.h>
#include <liblx/conversion/SBMLStripPackageConverter.h>
#include <liblx/conversion/SBMLUnitsConverter.h>

#include <liblx/validator/SBMLValidator.h>
#include <liblx/validator/SBMLExternalValidator.h>

#include <liblx/xml/XMLAttributes.h>
#include <liblx/xml/XMLNamespaces.h>
#include <liblx/xml/XMLConstructorException.h>
#include <liblx/xml/XMLToken.h>
#include <liblx/xml/XMLNode.h>
#include <liblx/xml/XMLTriple.h>
#include <liblx/xml/XMLInputStream.h>
#include <liblx/xml/XMLOutputStream.h>
#include <liblx/xml/XMLError.h>
#include <liblx/xml/XMLErrorLog.h>
#include <liblx/xml/XMLParser.h>
#include <liblx/xml/XMLHandler.h>
#include <liblx/xml/XMLTokenizer.h>

#include <liblx/annotation/CVTerm.h>
#include <liblx/annotation/Date.h>
#include <liblx/annotation/ModelCreator.h>
#include <liblx/annotation/ModelHistory.h>
#include <liblx/annotation/RDFAnnotationParser.h>

#include <liblx/extension/ISBMLExtensionNamespaces.h>
#include <liblx/extension/SBaseExtensionPoint.h>
#include <liblx/extension/SBasePlugin.h>
#include <liblx/extension/SBMLDocumentPlugin.h>
#include <liblx/extension/SBMLExtension.h>
#include <liblx/extension/SBMLExtensionException.h>
#include <liblx/extension/SBMLExtensionNamespaces.h>
#include <liblx/extension/SBMLExtensionRegistry.h>

#include <liblx/util/CallbackRegistry.h>

#include "ListWrapper.h"

