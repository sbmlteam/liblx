/*
 *
 * @file    TestUnit_newSetters.java
 * @brief   Unit unit tests for new set function API
 *
 * @author  Akiya Jouraku (Java conversion)
 * @author  Sarah Keating 
 *
 * $Id$
 * $HeadURL$
 *
 * This test file was converted from src/sbml/test/TestUnit_newSetters.c
 * with the help of conversion sciprt (ctest_converter.pl).
 *
 *<!---------------------------------------------------------------------------
 * This file is part of libSBML.  Please visit http://sbml.org for more
 * information about SBML, and the latest version of libSBML.
 *
 * Copyright 2005-2010 California Institute of Technology.
 * Copyright 2002-2005 California Institute of Technology and
 *                     Japan Science and Technology Corporation.
 * 
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation.  A copy of the license agreement is provided
 * in the file named "LICENSE.txt" included with this software distribution
 * and also available online as http://sbml.org/software/libsbml/license.html
 *--------------------------------------------------------------------------->*/


package org.sbml.libsbml.test.sbml;

import org.sbml.libsbml.*;

import java.io.File;
import java.lang.AssertionError;

public class TestUnit_newSetters {

  static void assertTrue(boolean condition) throws AssertionError
  {
    if (condition == true)
    {
      return;
    }
    throw new AssertionError();
  }

  static void assertEquals(Object a, Object b) throws AssertionError
  {
    if ( (a == null) && (b == null) )
    {
      return;
    }
    else if ( (a == null) || (b == null) )
    {
      throw new AssertionError();
    }
    else if (a.equals(b))
    {
      return;
    }

    throw new AssertionError();
  }

  static void assertNotEquals(Object a, Object b) throws AssertionError
  {
    if ( (a == null) && (b == null) )
    {
      throw new AssertionError();
    }
    else if ( (a == null) || (b == null) )
    {
      return;
    }
    else if (a.equals(b))
    {
      throw new AssertionError();
    }
  }

  static void assertEquals(boolean a, boolean b) throws AssertionError
  {
    if ( a == b )
    {
      return;
    }
    throw new AssertionError();
  }

  static void assertNotEquals(boolean a, boolean b) throws AssertionError
  {
    if ( a != b )
    {
      return;
    }
    throw new AssertionError();
  }

  static void assertEquals(int a, int b) throws AssertionError
  {
    if ( a == b )
    {
      return;
    }
    throw new AssertionError();
  }

  static void assertNotEquals(int a, int b) throws AssertionError
  {
    if ( a != b )
    {
      return;
    }
    throw new AssertionError();
  }
  private Unit U;

  protected void setUp() throws Exception
  {
    U = new  Unit(1,2);
    if (U == null);
    {
    }
  }

  protected void tearDown() throws Exception
  {
    U = null;
  }

  public void test_Unit_removeScale()
  {
    long i = U.setScale(2);
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertTrue( U.getScale() == 2 );
    i = Unit.removeScale(U);
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertTrue( U.getScale() == 0 );
    assertTrue( U.getMultiplier() == 100 );
  }

  public void test_Unit_setExponent1()
  {
    long i = U.setExponent(2);
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertTrue( U.getExponent() == 2 );
  }

  public void test_Unit_setExponent2()
  {
    long i = U.setExponent(2.0);
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertTrue( U.getExponent() == 2 );
  }

  public void test_Unit_setExponent3()
  {
    long i = U.setExponent(2.2);
    assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
    assertTrue( U.getExponent() == 1 );
  }

  public void test_Unit_setKind1()
  {
    long i = U.setKind(libsbml.UnitKind_forName("cell"));
    assertTrue( i == libsbml.LIBSBML_INVALID_ATTRIBUTE_VALUE );
    assertEquals( false, U.isSetKind() );
  }

  public void test_Unit_setKind2()
  {
    long i = U.setKind(libsbml.UnitKind_forName("litre"));
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertEquals( true, U.isSetKind() );
  }

  public void test_Unit_setMultiplier1()
  {
    long i = U.setMultiplier(2);
    assertTrue( i == libsbml.LIBSBML_UNEXPECTED_ATTRIBUTE );
    assertTrue( U.getMultiplier() == 2 );
  }

  public void test_Unit_setMultiplier2()
  {
    Unit c = new  Unit(2,2);
    long i = c.setMultiplier(4);
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertTrue( c.getMultiplier() == 4 );
    c = null;
  }

  public void test_Unit_setOffset1()
  {
    long i = U.setOffset(2.0);
    assertTrue( i == libsbml.LIBSBML_UNEXPECTED_ATTRIBUTE );
    assertTrue( U.getOffset() == 0 );
  }

  public void test_Unit_setOffset2()
  {
    Unit U1 = new  Unit(2,1);
    long i = U1.setOffset(2.0);
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertTrue( U1.getOffset() == 2 );
  }

  public void test_Unit_setScale1()
  {
    long i = U.setScale(2);
    assertTrue( i == libsbml.LIBSBML_OPERATION_SUCCESS );
    assertTrue( U.getScale() == 2 );
  }

  /**
   * Loads the SWIG-generated libSBML Java module when this class is
   * loaded, or reports a sensible diagnostic message about why it failed.
   */
  static
  {
    String varname;
    String shlibname;

    if (System.getProperty("mrj.version") != null)
    {
      varname = "DYLD_LIBRARY_PATH";    // We're on a Mac.
      shlibname = "libsbmlj.jnilib and/or libsbml.dylib";
    }
    else
    {
      varname = "LD_LIBRARY_PATH";      // We're not on a Mac.
      shlibname = "libsbmlj.so and/or libsbml.so";
    }

    try
    {
      System.loadLibrary("sbmlj");
      // For extra safety, check that the jar file is in the classpath.
      Class.forName("org.sbml.libsbml.libsbml");
    }
    catch (SecurityException e)
    {
      e.printStackTrace();
      System.err.println("Could not load the libSBML library files due to a"+
                         " security exception.\n");
      System.exit(1);
    }
    catch (UnsatisfiedLinkError e)
    {
      e.printStackTrace();
      System.err.println("Error: could not link with the libSBML library files."+
                         " It is likely\nyour " + varname +
                         " environment variable does not include the directories\n"+
                         "containing the " + shlibname + " library files.\n");
      System.exit(1);
    }
    catch (ClassNotFoundException e)
    {
      e.printStackTrace();
      System.err.println("Error: unable to load the file libsbmlj.jar."+
                         " It is likely\nyour -classpath option and CLASSPATH" +
                         " environment variable\n"+
                         "do not include the path to libsbmlj.jar.\n");
      System.exit(1);
    }
  }
}
