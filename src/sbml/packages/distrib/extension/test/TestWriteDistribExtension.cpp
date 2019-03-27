/**
* @file    TestWriteDistribExtension.cpp
* @brief   Unit tests of writing DistribExtension
 * @author  Sarah Keating
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBML. Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright (C) 2019 jointly by the following organizations:
 *     1. California Institute of Technology, Pasadena, CA, USA
 *     2. University of Heidelberg, Heidelberg, Germany
 *
 * Copyright (C) 2013-2018 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 * 3. University of Heidelberg, Heidelberg, Germany
 *
 * Copyright (C) 2009-2013 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
 *
 * Copyright (C) 2006-2008 by the California Institute of Technology,
 * Pasadena, CA, USA
 *
 * Copyright (C) 2002-2005 jointly by the following organizations:
 * 1. California Institute of Technology, Pasadena, CA, USA
 * 2. Japan Science and Technology Agency, Japan
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation. A copy of the license agreement is provided in the
 * file named "LICENSE.txt" included with this software distribution and also
 * available online as http://sbml.org/software/libsbml/license.html
 * ------------------------------------------------------------------------ -->
*/

#include <limits>

#include <iostream>
#include <check.h>
#include <sbml/SBMLTypes.h>
#include <sbml/extension/SBMLExtensionRegistry.h>
#include <sbml/packages/distrib/common/DistribExtensionTypes.h>

#include <sbml/conversion/ConversionProperties.h>

#include <string>

/** @cond doxygenIgnored */

using namespace std;
LIBSBML_CPP_NAMESPACE_USE

/** @endcond doxygenIgnored */

CK_CPPSTART
extern char *TestDataDirectory;

static string Distrib_XMLNS_L3V1V1;
static DistribExtension* G;
static DistribPkgNamespaces* GNS;

void
WriteDistribExtensionTest_setup(void)
{
  try
  {
    G = new DistribExtension();
    GNS = new DistribPkgNamespaces();
    Distrib_XMLNS_L3V1V1 = GNS->getURI();
  }
  catch (...)
  {
    fail("Failed to create a DistribExtension object");
  }
}

void
WriteDistribExtensionTest_teardown(void)
{
  delete G;
  delete GNS;
}

static bool
equals(std::string& expected, std::string& actual)
{
  if (expected == actual) return true;

  cout << "\nStrings are not equal:\n";
  cout << "Expected:\n[" << expected << "]\n";
  cout << "Actual:\n[" << actual << "]\n";

  return false;
}




//START_TEST(test_DistribExtension_create_and_write_L3V1V1)
//{
//  DistribPkgNamespaces *sbmlns = new DistribPkgNamespaces(3, 1, 1);
//
//  // create the document
//
//  SBMLDocument document(sbmlns);
//
//  // mark groups as not required
//
//  document.setPackageRequired("distrib", true);
//
//  // create the Model
//
//  Model* model = document.createModel();
//
//  // create the Compartment
//
//  Compartment* compartment = model->createCompartment();
//  compartment->setId("C");
//  compartment->setConstant(true);
//  compartment->setSize(1.0);
//  compartment->setSpatialDimensions(3.0);
//  compartment->setUnits("litre");
//
//  // create the Species
//
//  Species* species = model->createSpecies();
//  species->setId("S1");
//  species->setCompartment("C");
//  species->setHasOnlySubstanceUnits(false);
//  species->setBoundaryCondition(false);
//  species->setConstant(false);
//  species->setInitialAmount(5.2);
//  species->setSubstanceUnits("mole");
//
//  // create the uncertainty
//
//  DistribSBasePlugin* mplugin = static_cast<DistribSBasePlugin*>(species->getPlugin("distrib"));
//
//  fail_unless(mplugin != NULL);
//  Uncertainty * uncert = mplugin->createUncertainty();
//  UncertValue * sd = uncert->createStandardDeviation();
//  sd->setValue(0.3);
//
//  // createParameter
//  Parameter* p = model->createParameter();
//  p->setId("P1");
//  p->setValue(5.13);
//  p->setConstant(true);
//  p->setUnits("dimensionless");
//
//  // create the uncertainty
//
//  DistribSBasePlugin* pplugin = static_cast<DistribSBasePlugin*>(p->getPlugin("distrib"));
//
//  fail_unless(pplugin != NULL);
//  Uncertainty * puncert = pplugin->createUncertainty();
//  UncertStatisticSpan * span = puncert->createConfidenceInterval();
//  span->setValueLower(5);
//  span->setValueUpper(5.32);
//
//
//
//  std::string s2 = writeSBMLToStdString(&document);
//
//  std::string fileName = std::string(TestDataDirectory) + std::string("/") + std::string("distrib1ns.xml");
//  SBMLDocument *doc = readSBMLFromFile(fileName.c_str());
//  std::string s1 = writeSBMLToStdString(doc);
//  delete doc;
//
//  fail_unless(equals(s1, s2));
//
//  // check clone()
//
//  SBMLDocument document2 = document;
//  s2 = writeSBMLToStdString(&document2);
//  fail_unless(equals(s1, s2));
//
//  // check operator=
//
//  Model m = *(document.getModel());
//  document2.setModel(&m);
//  s2 = writeSBMLToStdString(&document2);
//  fail_unless(equals(s1, s2));
//
//  delete sbmlns;
//}
//END_TEST
//
//
//

Suite *
create_suite_WriteDistribExtension(void)
{
  Suite *suite = suite_create("WriteDistribExtension");
  TCase *tcase = tcase_create("WriteDistribExtension");

  tcase_add_checked_fixture(tcase, WriteDistribExtensionTest_setup, WriteDistribExtensionTest_teardown);
  
  //tcase_add_test(tcase, test_DistribExtension_create_and_write_L3V1V1);

  suite_add_tcase(suite, tcase);

  return suite;
}

CK_CPPEND