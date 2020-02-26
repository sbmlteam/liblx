/**
 * @file    TestCompression.cpp
 * @brief   TestCompression unit tests
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
 * Copyright (C) 2009-2011 jointly by the following organizations: 
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

#include <limits>

#include <iostream>
#include <check.h>
#include <sbml/common/extern.h>
#include <sbml/packages/spatial/common/SpatialExtensionTypes.h>
#include <sbml/extension/SBMLExtensionRegistry.h>
#include <sbml/SBMLTypeCodes.h>
#include <string>

/** @cond doxygenIgnored */

using namespace std;
LIBSBML_CPP_NAMESPACE_USE

/** @endcond doxygenIgnored */

CK_CPPSTART


// libsbml still only exports char* in its string serialization ...
#define PRINT_SBML(stream, label, x)  \
    {                                 \
        char *tmp = x.toSBML();       \
        stream << label << std::endl; \
        stream << tmp << std::endl;   \
        free(tmp);                    \
    }
// write data out, to see what is what
#define PRINT_DATA(stream, label, data) \
    {                                   \
        auto it = data.begin();         \
        auto end = data.end();          \
        stream << label << std::endl;   \
        while (it != end)               \
            stream << " " << *(it++);   \
        stream << std::endl             \
               << std::endl;            \
    }



START_TEST(test_Compression_SampledField_1)
{
  // assume we have some values from our app in a structure
  std::vector<double> values =
  {
    1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
    1.1, 2.1, 3.1, 4.1, 5.1, 6.1,
    1.2, 2.2, 3.2, 4.2, 5.2, 6.2,
    1.3, 2.3, 3.3, 4.3, 5.3, 6.3 };

  string valstring = "1 2 3 4 5 6 1.1000000000000001 2.1000000000000001 3.1000000000000001 4.0999999999999996 5.0999999999999996 6.0999999999999996 1.2 2.2000000000000002 3.2000000000000002 4.2000000000000002 5.2000000000000002 6.2000000000000002 1.3 2.2999999999999998 3.2999999999999998 4.2999999999999998 5.2999999999999998 6.2999999999999998 ";

  std::vector<float> values_float;
  for (size_t n = 0; n < values.size(); n++)
  {
    values_float.push_back(static_cast<float>(values[n]));
  }

  string compressed = "120 218 101 206 185 17 0 33 12 67 209 86 84 129 7 249 154 165 255 198 128 208 43 133 47 240 55 225 8 36 10 13 26 215 24 225 74 161 148 182 246 88 163 148 90 137 230 55 225 243 222 125 72 41 149 74 169 149 104 241 18 179 252 189 196 159 82 169 148 90 233 0 141 250 63 196 ";

  std::vector<int> compressedvals =
  { 120, 218, 101, 206, 185, 17, 0, 33, 12, 67, 209, 86, 84, 129, 7, 249, 154, 165, 255, 198, 128, 208, 43, 133, 47, 240, 55, 225, 8, 36, 10, 13, 26, 215, 24, 225, 74, 161, 148, 182, 246, 88, 163, 148, 90, 137, 230, 55, 225, 243, 222, 125, 72, 41, 149, 74, 169, 149, 104, 241, 18, 179, 252, 189, 196, 159, 82, 169, 148, 90, 233, 0, 141, 250, 63, 196 };

  SampledField field;
  field.setId("uncompressed_double");
  field.setDataType(SPATIAL_DATAKIND_DOUBLE);
  field.setCompression(SPATIAL_COMPRESSIONKIND_UNCOMPRESSED);
  field.setNumSamples1(values.size());

  // here then the values are set by the user, passing in either a values vector, an array
  // or even just a std::string that they constucted themselves.
  field.setSamples(values);

  fail_unless(field.getSamples() == valstring);
  fail_unless(field.getSamplesLength() == 24);
  fail_unless(field.isSetSamplesLength() == true);

  std::vector<double> uncompressed_data;
  field.getSamples(uncompressed_data);
  fail_unless(uncompressed_data == values);

  // Now compress the values
  field.compress(9);

  fail_unless(field.getSamples() == compressed);
  fail_unless(field.getSamplesLength() == 76);
  fail_unless(field.isSetSamplesLength() == true);
  fail_unless(field.getCompression() == SPATIAL_COMPRESSIONKIND_DEFLATED);

  std::vector<int> compressed_data;
  field.getSamples(compressed_data);

  fail_unless(compressed_data == compressedvals);

  //Now uncompress them again
  field.uncompress();
  fail_unless(field.getSamples() == valstring);
  fail_unless(field.getSamplesLength() == 24);
  fail_unless(field.isSetSamplesLength() == true);
  fail_unless(field.getCompression() == SPATIAL_COMPRESSIONKIND_UNCOMPRESSED);

  field.getSamples(uncompressed_data);
  fail_unless(uncompressed_data == values);

  std::vector<float> uncompressed_data_float;
  field.getSamples(uncompressed_data_float);
  fail_unless(uncompressed_data_float == values_float);

}
END_TEST


START_TEST(test_Compression_SampledField_2)
{
  //This test checks the 'getUncompressed' functions if they're originally set in compressed form.

  std::vector<double> values =
  {
    1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
    1.1, 2.1, 3.1, 4.1, 5.1, 6.1,
    1.2, 2.2, 3.2, 4.2, 5.2, 6.2,
    1.3, 2.3, 3.3, 4.3, 5.3, 6.3 };

  string compressed = "120 218 101 206 185 17 0 33 12 67 209 86 84 129 7 249 154 165 255 198 128 208 43 133 47 240 55 225 8 36 10 13 26 215 24 225 74 161 148 182 246 88 163 148 90 137 230 55 225 243 222 125 72 41 149 74 169 149 104 241 18 179 252 189 196 159 82 169 148 90 233 0 141 250 63 196 ";

  std::vector<int> compressedvals =
  { 120, 218, 101, 206, 185, 17, 0, 33, 12, 67, 209, 86, 84, 129, 7, 249, 154, 165, 255, 198, 128, 208, 43, 133, 47, 240, 55, 225, 8, 36, 10, 13, 26, 215, 24, 225, 74, 161, 148, 182, 246, 88, 163, 148, 90, 137, 230, 55, 225, 243, 222, 125, 72, 41, 149, 74, 169, 149, 104, 241, 18, 179, 252, 189, 196, 159, 82, 169, 148, 90, 233, 0, 141, 250, 63, 196 };

  SampledField field;
  field.setId("uncompressed_double");
  field.setDataType(SPATIAL_DATAKIND_DOUBLE);
  field.setCompression(SPATIAL_COMPRESSIONKIND_DEFLATED);
  field.setNumSamples1(values.size());

  field.setSamples(compressedvals);

  fail_unless(field.getSamples() == compressed);
  fail_unless(field.getSamplesLength() == 76);
  fail_unless(field.isSetSamplesLength() == true);
  fail_unless(field.getCompression() == SPATIAL_COMPRESSIONKIND_DEFLATED);

  double* uncompressed_data = new double[values.size()];
  field.getUncompressed(uncompressed_data);
  for (size_t n = 0; n < values.size(); n++) {
    fail_unless(values[n] == uncompressed_data[n]);
  }
  free(uncompressed_data);
  fail_unless(field.getUncompressedLength() == values.size());

  uncompressed_data = NULL;
  size_t len = 0;
  field.getUncompressedData(uncompressed_data, len);
  for (size_t n = 0; n < values.size(); n++) {
    fail_unless(values[n] == uncompressed_data[n]);
  }
  fail_unless(len == values.size());
  free(uncompressed_data);

}
END_TEST


START_TEST(test_Compression_SampledField_3)
{
  //This test checks the 'getUncompressed' functions if they're originally set uncompressed.

  // assume we have some values from our app in a structure
  std::vector<double> values =
  {
    1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
    1.1, 2.1, 3.1, 4.1, 5.1, 6.1,
    1.2, 2.2, 3.2, 4.2, 5.2, 6.2,
    1.3, 2.3, 3.3, 4.3, 5.3, 6.3 };

  string valstring = "1 2 3 4 5 6 1.1000000000000001 2.1000000000000001 3.1000000000000001 4.0999999999999996 5.0999999999999996 6.0999999999999996 1.2 2.2000000000000002 3.2000000000000002 4.2000000000000002 5.2000000000000002 6.2000000000000002 1.3 2.2999999999999998 3.2999999999999998 4.2999999999999998 5.2999999999999998 6.2999999999999998 ";

  SampledField field;
  field.setId("uncompressed_double");
  field.setDataType(SPATIAL_DATAKIND_DOUBLE);
  field.setCompression(SPATIAL_COMPRESSIONKIND_UNCOMPRESSED);
  field.setNumSamples1(values.size());

  field.setSamples(values);

  fail_unless(field.getSamples() == valstring);
  fail_unless(field.getSamplesLength() == values.size());
  fail_unless(field.isSetSamplesLength() == true);
  fail_unless(field.getCompression() == SPATIAL_COMPRESSIONKIND_UNCOMPRESSED);

  double* uncompressed_data = new double[values.size()];
  field.getUncompressed(uncompressed_data);
  for (size_t n = 0; n < values.size(); n++) {
    fail_unless(values[n] == uncompressed_data[n]);
  }
  free(uncompressed_data);
  fail_unless(field.getUncompressedLength() == values.size());

  uncompressed_data = NULL;
  size_t len = 0;
  field.getUncompressedData(uncompressed_data, len);
  for (size_t n = 0; n < values.size(); n++) {
    fail_unless(values[n] == uncompressed_data[n]);
  }
  fail_unless(len == values.size());
  free(uncompressed_data);

}
END_TEST


START_TEST(test_Compression_SampledField_4)
{
  //This test checks the 'getSamples' functions from uncompressed data.

  // assume we have some values from our app in a structure
  std::vector<double> values =
  {
    1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
    1.1, 2.1, 3.1, 4.1, 5.1, 6.1,
    1.2, 2.2, 3.2, 4.2, 5.2, 6.2,
    1.3, 2.3, 3.3, 4.3, 5.3, 6.3 };

  SampledField field;
  field.setId("uncompressed_double");
  field.setDataType(SPATIAL_DATAKIND_DOUBLE);
  field.setCompression(SPATIAL_COMPRESSIONKIND_UNCOMPRESSED);
  field.setNumSamples1(values.size());

  field.setSamples(values);


  double* doubles = new double[values.size()];
  field.getSamples(doubles);
  for (size_t n = 0; n < values.size(); n++) {
    fail_unless(values[n] == doubles[n]);
  }
  free(doubles);

  vector<double> doublevec;
  field.getSamples(doublevec);
  fail_unless(doublevec == values);

  float* floats = new float[values.size()];
  field.getSamples(floats);
  for (size_t n = 0; n < values.size(); n++) {
    fail_unless(static_cast<float>(values[n]) == floats[n]);
  }
  free(floats);

  vector<float> floatvec;
  field.getSamples(floatvec);
  fail_unless(floatvec.size() == values.size());
  for (size_t n = 0; n < floatvec.size(); n++)
  {
    fail_unless(static_cast<float>(values[n]) == floatvec[n]);
  }

  int* ints = new int[values.size()];
  fail_unless(field.getSamples(ints) == LIBSBML_OPERATION_FAILED);
  free(ints);

  vector<int> intvec;
  field.getSamples(intvec);
  fail_unless(intvec.size() == 0);

}
END_TEST


START_TEST(test_Compression_SampledField_5)
{
  //This test checks the 'getSamples' functions from compressed data.

  // assume we have some values from our app in a structure
  std::vector<double> values =
  {
    1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
    1.1, 2.1, 3.1, 4.1, 5.1, 6.1,
    1.2, 2.2, 3.2, 4.2, 5.2, 6.2,
    1.3, 2.3, 3.3, 4.3, 5.3, 6.3 };

  std::vector<int> compressedvals =
  { 120, 218, 101, 206, 185, 17, 0, 33, 12, 67, 209, 86, 84, 129, 7, 249, 154, 165, 255, 198, 128, 208, 43, 133, 47, 240, 55, 225, 8, 36, 10, 13, 26, 215, 24, 225, 74, 161, 148, 182, 246, 88, 163, 148, 90, 137, 230, 55, 225, 243, 222, 125, 72, 41, 149, 74, 169, 149, 104, 241, 18, 179, 252, 189, 196, 159, 82, 169, 148, 90, 233, 0, 141, 250, 63, 196 };

  SampledField field;
  field.setId("uncompressed_double");
  field.setDataType(SPATIAL_DATAKIND_DOUBLE);
  field.setCompression(SPATIAL_COMPRESSIONKIND_DEFLATED);
  field.setNumSamples1(values.size());

  field.setSamples(compressedvals);


  double* doubles = new double[values.size()];
  field.getSamples(doubles);
  for (size_t n = 0; n < values.size(); n++) {
    fail_unless(values[n] == doubles[n]);
  }
  free(doubles);

  vector<double> doublevec;
  field.getSamples(doublevec);
  fail_unless(doublevec == values);

  float* floats = new float[values.size()];
  field.getSamples(floats);
  for (size_t n = 0; n < values.size(); n++) {
    fail_unless(static_cast<float>(values[n]) == floats[n]);
  }
  free(floats);

  vector<float> floatvec;
  field.getSamples(floatvec);
  fail_unless(floatvec.size() == values.size());
  for (size_t n = 0; n < floatvec.size(); n++)
  {
    fail_unless(static_cast<float>(values[n]) == floatvec[n]);
  }

  int* ints = new int[compressedvals.size()];
  field.getSamples(ints);
  for (size_t n = 0; n < compressedvals.size(); n++) {
    fail_unless(compressedvals[n] == ints[n]);
  }
  free(ints);

  vector<int> intvec;
  field.getSamples(intvec);
  fail_unless(intvec == compressedvals);

}
END_TEST


Suite *
create_suite_Compression(void)
{
  Suite *suite = suite_create("Compression");
  TCase *tcase = tcase_create("Compression");

#ifndef USE_ZLIB
  tcase_add_test( tcase, test_Compression_SampledField_1);
  tcase_add_test( tcase, test_Compression_SampledField_2);
  tcase_add_test( tcase, test_Compression_SampledField_3);
  tcase_add_test( tcase, test_Compression_SampledField_4);
  tcase_add_test( tcase, test_Compression_SampledField_5);
#endif

  suite_add_tcase(suite, tcase);

  return suite;
}


CK_CPPEND
