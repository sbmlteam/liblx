Complete Windows Example
========================

This is a complete Windows example, building the ``liblx`` library, the Python bindings, and the documentation (both docs such as this
one, and Doxygen-generated ones from the ``liblx`` source files). This is because I think some of the other documentation
has become a little inconsistent, as I wrote it whilst battling different Windows build issues.

Install Visual Studio, with the Windows SDK. You can then use its version of ``cmake`` (see below).

Download the `SBML Windows dependencies <https://sourceforge.net/projects/sbml/files/libsbml/win-dependencies/>`_.
You can download all 4 and use as required. 
The most commonly downloaded one is ``libSBML_dependencies_vs15_release_x64_static.zip``, and we will use it in this example.
In this example, I unzipped it and renamed the unzipped folder to:

``C:\Users\cceagil\repos\CompBioLibs\dependencies\libSBML-Dependencies-1.0.0-b1-win64-release-static``

Use Python to create a virtual environment.

.. code-block:: bash

	> mkdir envts && cd envts
	> python -m venv myenv
	> myenv\Scripts\activate
	(myenv)

If you have installed ``cmake``, you can use it directly. If not, you can use the version which comes with Visual Studio.
See `Using cmake at the command line with Visual Studio <https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-160#run-cmake-from-the-command-line>`_
and `Building on the command line <https://docs.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-160>`_.

NB ensure you select the correct version of the documentation for your version of Visual Studio.

Basically, to use the VS version of ``cmake``, you have to ``cd`` into the relevant directory on your PC,
and then execute the appropriate ``.bat`` file to update the ``PATH`` and required environment variables.
e.g.

.. code-block:: bash

    (myenv) cd C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build

Running the ``set`` command (lists environment variables) reveals ``PROCESSOR_ARCHITECTURE=AMD64`` and ``Platform=x64``
(or you might be able to get this information by right-clicking on "This PC" or "My Computer", and choosing the Properties option.)
So we need to `run the file vcvar64.bat at the command line, in our existing command 
window <https://docs.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-160#use-the-developer-tools-in-an-existing-command-window>`_.

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

Now we can look at the documentation (in the ``build/docs/sphinx/quickstart`` folder, e.g.
``build/docs/sphinx/quickstart/get-started.html`` and ``build/docs/sphinx/quickstart/complete-windows-example.html``).
You should also be able to view the API documentation, formed by Doxygen and Sphinx from the relevant comments in the source files.

You can also now use the Python bindings (wrapper) to the ``liblx`` C/C++ code. For example, from within the ``build/`` directory:

.. code-block:: bash

    (myenv) cd src\bindings\python    

Invoking ``dir`` should show that ``liblx.py`` is visible. To work, this needs ``_liblx.pyd``, which in our case is in the 
directory ``build\src\bindings\python\Release``. To use ``liblx`` within Python, we need to update our ``PYTHONPATH`` to 
include this directory. We can do this inside Python:

 .. code-block:: bash

    (myenv) python
    >>> import sys
    >>> sys.path += ["C:\\Users\\cceagil\\repos\\CompBioLibs\\build\\src\\bindings\\python\\Release"]
    >>> from liblx import *


The ``liblx`` Python library can then be used as per the example Sample Python Session in ``python-bindings.html``. 

