Complete Windows Example
========================

.. _building_cli:

Using the command line
----------------------
This is a complete Windows example, building the ``liblx`` library, the Python bindings, and the documentation (both docs such as this
one, and Doxygen-generated ones from the ``liblx`` source files). This is because I think some of the other documentation
has become a little inconsistent, as I wrote it whilst battling different Windows build issues.

We assume you have cloned the ``liblx`` repository on your local Windows computer.

The term "directory", in the following instructions, is synonymous with the Windows term "folder".

Install `Microsoft Visual Studio <https://visualstudio.microsoft.com/vs/>`_, with the Windows SDK. You can then use its version of ``cmake`` (see below).

Download the `SBML Windows dependencies <https://sourceforge.net/projects/sbml/files/libsbml/win-dependencies/>`_.
You can download all 4 and use as required. Right now there is no "version 16", the version number of my Visual Studio,
so I downloaded the highest available one (15). Make sure you check the checksums.

The most commonly downloaded one is ``libSBML_dependencies_vs15_release_x64_static.zip``, and we will use it in this example.
In this example, I unzipped it and renamed the unzipped folder to:

``C:\Users\cceagil\repos\CompBioLibs\dependencies\libSBML-Dependencies-1.0.0-b1-win64-release-static``

Use Python to create a virtual environment. Do this outside the repo you have cloned, otherwise lots of unnecessary files
will be generated in the documentation step

.. code-block:: bash

	> mkdir envts && cd envts
	> python -m venv myenv
	> myenv\Scripts\activate
	(myenv)

(Use the command ``deactivate`` if you need to exit the virtual environment.)

If you have installed ``cmake``, you can use it directly. If not, you can use the version which comes with Visual Studio.
See `Using cmake at the command line with Visual Studio <https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-160#run-cmake-from-the-command-line>`_
and `Building on the command line <https://docs.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-160>`_.

**NB ensure you select the correct version of the documentation for your version of Visual Studio.**

Basically, to use the VS version of ``cmake``, you have to ``cd`` into the relevant directory on your PC,
and then execute the appropriate ``.bat`` file to update the ``PATH`` and required environment variables.
e.g.

.. code-block:: bash

    (myenv) cd C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build

Running the ``set`` command (lists environment variables) reveals ``PROCESSOR_ARCHITECTURE=AMD64`` and ``Platform=x64``
(or you might be able to get this information by right-clicking on "This PC" or "My Computer", and choosing the Properties option.)
So we need to `run the file vcvar64.bat (in this case) at the command line, in our existing command 
window <https://docs.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-160#use-the-developer-tools-in-an-existing-command-window>`_.
Obviously, based on your computer's arhitecture you may need to select a different ``.bat`` file.

.. code-block:: bash

    (myenv) vcvars64.bat
    **********************************************************************
    ** Visual Studio 2019 Developer Command Prompt v16.11.3
    ** Copyright (c) 2021 Microsoft Corporation
    **********************************************************************
    [vcvarsall.bat] Environment initialized for: 'x64'

    (myenv)

After that, we need the tools to build the documentation.
For the docs, do the following:

.. code-block:: bash

     (myenv) pip install sphinx_rtd_theme
     (myenv) pip install breathe

You will also need to download `Doxygen <https://www.doxygen.nl/download.html>`_; also see
info about `Windows builds <https://www.doxygen.nl/manual/install.html#install_bin_windows>`_.
And then update your ``PATH`` to include the location of the Doxygen executable (``doxygen.exe``). For example:

.. code-block:: bash

    (myenv) set PATH="C:\Program Files\doxygen\bin";%PATH%

Now download `GraphViz <https://graphviz.org/download/>`_, and do the same.
e.g.

.. code-block:: bash

    (myenv) set PATH="C:\Program Files\GraphViz\bin";%PATH%

In the above examples, I enclosed the new part of the ``PATH`` in quotes, due to the space in "Program Files", 
but this may not be necessary. 

For the C/C++-Python SWIG bindings, you need to install SWIG. On my PC, the executable is 
``C:\Users\cceagil\swigwin-4.0.2\swigwin-4.0.2\swig.exe``. So we again update the ``PATH``:

.. code-block:: bash

    (myenv) set PATH=C:\Users\cceagil\swigwin-4.0.2\swigwin-4.0.2;%PATH%

You can check the value of the ``PATH`` if desired:

.. code-block:: bash

    (myenv) echo %PATH%
    C:\Users\cceagil\swigwin-4.0.2\swigwin-4.0.2;"C:\Program Files\doxygen\bin";C:\Users\cceagil\venvs\venv\Scripts;C:\Program Files\Java\jdk1.8.0_291\bin;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C;C:\Program Files\Git\cmd;C:\Program Files\Java\jdk1.8.0_291\bin;C:\Users\cceagil\AppData\Local\Programs\Python\Python39\Scripts\;C:\Users\cceagil\AppData\Local\Programs\Python\Python39\;C:\Users\cceagil\AppData\Local\Microsoft\WindowsApps;C:\Program Files\Graphviz\bin

Now we need to set the ``CODE_SRC_DIR`` environment variable to the top of the ``liblx`` source file hierarchy:

.. code-block:: bash

    (myenv) set CODE_SRC_DIR=C:\Users\cceagil\repos\CompBioLibs\liblx\src 

Finally, we create a new build directory, outside of the ``liblx`` git repo directory hierarchy. Then enter it and execute ``cmake``:

.. code-block:: bash

    (myenv) mkdir build
    (myenv) cd build
    (myenv) cmake -DCMAKE_BUILD_TYPE=Release -DWITH_PYTHON=ON -DWITH_STATIC_RUNTIME=ON -DWITH_DOXYGEN=TRUE -DWITH_CHECK=TRUE -DLIBLX_DEPENDENCY_DIR=C:\Users\cceagil\repos\CompBioLibs\dependencies\libSBML-Dependencies-1.0.0-b1-win64-release-static C:\Users\cceagil\repos\CompBioLibs\liblx
    (myenv) cmake --build . --config Release

Note, in this case, that we want a static Release build, per the version of the SBML dependency libraries we are
linking against. So both the ``CMAKE_BUILD_TYPE`` and ``--config`` options are set to ``Release``. Also, we "switch on"
the ``WITH_STATIC_RUNTIME`` option. The (rather copious) ``cmake`` output is not shown. The final item in the first ``cmake`` command
is the top level directory of the ``liblx`` cloned repository.

Run the tests to check all is well; in this case, we created a Release build:

.. code-block:: bash

    (myenv) ctest -C Release
    Test project C:/Users/cceagil/repos/CompBioLibs/build
        Start 1: test_sbml_xml_run
    1/2 Test #1: test_sbml_xml_run ................   Passed    2.25 sec
        Start 2: test_python_binding
    2/2 Test #2: test_python_binding ..............   Passed    0.48 sec

    100% tests passed, 0 tests failed out of 2

    Total Test time (real) =   2.75 sec

    (myenv) 

If more detailed output is required, also use the ``-V`` switch - so, in this case, it would be:


.. code-block:: bash

    ctest -V -C Release

Now we can look at the documentation (in the ``build/docs/sphinx/quickstart`` folder, e.g.
`Quickstart <./get-started.html>`_ and ``build/docs/sphinx/quickstart/complete-windows-example.html`` (this file)).
You should also be able to view the `API documentation <../api.html>`_, formed by Doxygen and Sphinx from the relevant comments in the source files.

You can also now use the Python bindings (wrapper) to the ``liblx`` C/C++ code. For example, from within the ``build/`` directory:

.. code-block:: bash

    (myenv) cd src\bindings\python    

Invoking ``dir`` should show that ``liblx.py`` is visible, and we are in the directory
``build\src\bindings\python``. To work, this needs ``_liblx.pyd``, which in our case is in the 
directory ``build\src\bindings\python\Release``. To use ``liblx`` within Python, we need to update our ``PYTHONPATH`` to 
include this directory. We can do this inside Python:

 .. code-block:: bash

    (myenv) python
    >>> import sys
    >>> sys.path += ["C:\\Users\\cceagil\\repos\\CompBioLibs\\build\\src\\bindings\\python\\Release"]
    >>> from liblx import *


The ``liblx`` Python library can then be used as per the example 
`Sample Python Session <../liblx/python-bindings.html#sample-python-session>`_. 


.. _building_dont-like-cli:

I don't want to use the command line!
-------------------------------------
If you don't like the command line, you can refer to the
`detailed instructions <http://sbml.org/Software/libSBML/5.18.0/docs/cpp-api/libsbml-installation.html#detailed-windows>`_
for building ``libSBML`` on Windows (which we can adapt for building ``liblx``). Use the CMake GUI for the first
step. Then, the second command above (the build (i.e. compilation) step) can be done from within the Visual Studio
GUI. The easiest way is to locate the "solution" file, ``liblx.sln``, which should have been generated in
the ``build`` directory; navigate to it using Windows Explorer, then double-click on it to open this solution
in Visual Studio (but see below). Then, right-click on the desired target (e.g. ``ALL_BUILD``) and select the build option.

Obviously you will still have to download the required dependencies and other software referred to in the command-line build section.


.. _other_xml:

Choice of XML library
---------------------

By default, ``liblx`` is compiled with the `libXML <http://xmlsoft.org/>`_ library. However, users can choose to use another XML library instead.
The others supported at the moment are the `Expat <https://github.com/libexpat/libexpat>`_ and  `Xerces <http://xerces.apache.org/xerces-c/>`_ libraries.

The required files are included in the SBML Windows dependencies, mentioned near the beginning of this page. If you wish to use another one, please refer to the table below.

.. list-table:: Choice of XML library
   :widths: 20 80
   :header-rows: 1

   * - Preferred library
     - Changes required to first ``cmake`` command above
   * - libXML
     - (no changes required)
   * - Expat
     - Add ``-DWITH_EXPAT=TRUE -DWITH_LIBXML=FALSE`` to first ``cmake`` command
   * - Xerces
     - Add ``-DWITH_XERCES=TRUE -DWITH_LIBXML=FALSE`` to first ``cmake`` command


.. _windows-issues:

Windows issues with the SWIG Python build
-----------------------------------------

Things should work OK, as detailed above, but this section is a record of some issues I had when battling to get a successful Windows
build, in case it helps someone.

Basically, don't use Anaconda Python to get this to work! (at least, not a Debug build).

.. code-block:: bash

    set PYTHON_INCLUDE=C:\ProgramData\Anaconda3\include
    set PYTHON_LIB=C:\ProgramData\Anaconda3\libs\python38.lib
    -DSWIG_EXECUTABLE=C:\Users\mattg\swigwin-4.0.2\swig.exe
    produces src/bindings/python/liblx.py

    linker error:
    LINK : fatal error LNK1104: cannot open file 'python38_d.lib' [C:\Users\mattg\build\src\bindings\python\binding_python_
    lib.vcxproj]


Maybe because I specified a debug version of the dependencies???
see:
https://stackoverflow.com/questions/59126760/building-a-python-c-extension-on-windows-with-a-debug-python-installation

and:
https://stackoverflow.com/questions/17028576/using-python-3-3-in-c-python33-d-lib-not-found/45407558

It looks like we need to download a debug version of the python library. Anaconda doesn't appear to supply this.
Downloading Windows installer of Python 3.9.7 https://www.python.org/downloads/release/python-397/
Or, one can use ``#ifdef`` statements.
The installer updated the ``PATH`` (selected option to disable max ``PATH`` character limit) and appears before the
Anaconda version in the ``PATH``.

.. code-block:: bash

    set PYTHON_INCLUDE="C:\Program Files\Python39\include"   # location of Python.h
    set PYTHON_LIB="C:\Program Files\Python39\libs\python39_d.lib"  # debug library
    -DPYTHON_EXECUTABLE="C:\Program Files\Python39\python.exe"
    rm -rf ~/repos/work/CompBioLibs/liblx/out # delete vs cmake cache Visual Studio: Project-> cmake cache->delete cache

    LINK : warning LNK4098: defaultlib 'MSVCRT' conflicts with use of other libs; use /NODEFAULTLIB:library [C:\Users\mattg
    \build\src\liblx\xml\test\test_sbml_xml.vcxproj]

https://stackoverflow.com/questions/3007312/resolving-lnk4098-defaultlib-msvcrt-conflicts-with 

