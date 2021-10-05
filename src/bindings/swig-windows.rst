Here are some instructions for getting a basic SWIG/Python wrapper to work
on Windows using Visual Studio tools. This is completely independent from liblx.

by Matthew Gillman, September 2021.

SWIG website links:
C example http://www.swig.org/Doc4.0/Python.html#Python_nn4
environment variables http://www.swig.org/Doc4.0/Windows.html#Windows_python
Windows quirks http://www.swig.org/Doc4.0/Windows.html#Windows_interface_file

My PC is an x64 Windows box. I was only able to get this working using the special
"x64 Native Tools Command Prompt". There is a linker option (/MACHINE:X64) but that
wasn't enough to get things working in a normal Visual Studio command prompt.

========================================================================================

1. C example (from SWIG website)
--------------------------------

/* File: example.h */

int fact(int n);
-----------------
/* File: example.c */

#include "example.h"

int fact(int n) {
  if (n < 0) { /* This should probably return an error, but this is simpler */
    return 0;
  }
  if (n == 0) {
    return 1;
  } else {
    /* testing for overflow would be a good idea here */
    return n * fact(n-1);
  }
}
-----------------------------
/* File: example.i */
%module example

/* On Windows you need to include <windows.h> and all header files here. */
%include <windows.i>
%include "example.h"

/* You might not need this Windows-specific block. */
%begin %{
#ifdef _MSC_VER
#define SWIG_PYTHON_INTERPRETER_NO_DEBUG
#endif
%}

%{
#define SWIG_FILE_WITH_INIT
#include "example.h"
%}

int fact(int n);
------------------------------------------------

The .i file needs a number of additions compared to the *nix version of the file
- namely the two %include lines near the top, and the %begin block below them.

As my PC is an x64 I was required to use the Visual Studio "x64 Native Tools Command Prompt".
The commands within that were:

> C:\Users\mattg\swigwin-4.0.2\swig.exe -python example.i
This produces new files example.py and example_wrap.c

> cl.exe example.c example_wrap.c /I"C:\Program Files\Python39\include" /link /LIBPATH:"C:\Program Files\Python39\libs" /DLL [not used: /]MACHINE:X64]
The include path is to the directory where Python.h is located. (In the Python you have installed; use "where python" to find out where)
Although the SWIG website says to set these as environment variables, I had some trouble using the library one.
So you could just issue these commands without setting the envt. variables, as long as you specify what you need to.
And you can check that the correct Python executable, etc., are picked up if you issue the command "where python".
Final step:

> rename example.exe _example.pyd

C:\Users\mattg\envts\swigtest>python
Python 3.9.7 (tags/v3.9.7:1016ef3, Aug 30 2021, 20:19:38) [MSC v.1929 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license" for more information.
>>> from example import *
>>> fact(4)
24
>>>

===========================================================================

2. C++ Example (adapted from C example)
---------------------------------------

/* File: example.h */

class Util {

public:
  Util() {}
  ~Util() {}

  static int fact(int n);
};
-----------------------------
/* File: example.cpp */

#include "example.h"
#include <iostream>
using namespace std;

int Util::fact(int n) {
  if (n < 0) { /* This should probably return an error, but this is simpler */
    return 0;
  }
  if (n == 0) {
    return 1;
  } else {
    /* testing for overflow would be a good idea here */
    return n * fact(n-1);
  }
}

/* Just for when I was getting the basic C++ to work without SWIG/Python!
int main() {

   int x = Util::fact(4);
   cout << "\n result is " << x << endl;
   return 0;
}
*/
------------------------------------------------------
/* File: example.i */
%module example

%include <windows.i>
%include "example.h"

/* It's possible this block isn't required. */
%begin %{
#ifdef _MSC_VER
#define SWIG_PYTHON_INTERPRETER_NO_DEBUG
#endif
%}

%{
#define SWIG_FILE_WITH_INIT
#include "example.h"
%}

int Util::fact(int n);
-------------------------------------------------------------

Again, using the Visual Studio "x64 Native Tools Command Prompt":

> C:\Users\mattg\swigwin-4.0.2\swig.exe -c++ -python example.i
(note the `-c++` option in the above command).
This command produces new files example.py and example_wrap.cxx.

> cl.exe example.cpp example_wrap.cxx /I"C:\Program Files\Python39\include" /link /LIBPATH:"C:\Program Files\Python39\libs" /DLL
This produces new files example.exe, example.lib, example.exp, example.obj and example_wrap.obj

> rename example.exe _example.pyd

> python
Python 3.9.7 (tags/v3.9.7:1016ef3, Aug 30 2021, 20:19:38) [MSC v.1929 64 bit (AMD64)] on win32
Type "help", "copyright", "credits" or "license" for more information.
>>> import example
>>> example.Util.fact(5)
120
>>>