Complete Windows Example
========================

This is a complete Windows example, building the `liblx` library, the Python bindings, and the documentation (both docs such as this
one, and Doxygen-generated ones from the `liblx` source files). This is because I think some of the other documentation
has become a little inconsistent, as I wrote it whilst battling different build issues.

Install Visual Studio, with the Windows SDK. You can then use its version of `cmake` (see below).

Download the `SBML Windows dependencies <https://sourceforge.net/projects/sbml/files/libsbml/win-dependencies/>`_.
You can download all 4 and use as required. 
Most commonly downloaded one is libSBML_dependencies_vs15_release_x64_static.zip, and we will use it in this example.

Use Python to create a virtual environment.

.. code-block:: bash

	> mkdir envts && cd envts
	> python -m venv myenv
	> myenv\Scripts\activate
	(myenv)>

If you have installed `cmake`, you can use it directly. If not, you can use the version which comes with Visual Studio.
See https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-160#run-cmake-from-the-command-line
and https://docs.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-160

Basically, to use the VS version of `cmake`, you have to `cd` into the relevant directory on your PC,
and then execute the appropriate `.bat` file to update the `PATH` and required environment variables.
e.g.

.. code-block:: bash

    (myenv) cd C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build

Running the `set` command (lists environment variables) reveals `PROCESSOR_ARCHITECTURE=AMD64` and `Platform=x64`
(or you might be able to get this information by right-clicking on "This PC" or "My Computer", and choosing the Properties option.)
So we need to run the file `vcvarsx86_amd64.bat` at the command line. 

After that, we need the tools to build the documentation.
For the docs, do the following:

.. code-block:: bash

     (myenv)> pip install sphinx_rtd_theme
     (myenv)> pip install breathe

You will also need to download `Doxygen <https://www.doxygen.nl/download.html>`_; also see
info about `Windows builds <https://www.doxygen.nl/manual/install.html#install_bin_windows>`_.
And then update your `PATH` to include the location of the Doxygen executable (`doxygen.exe`). For example:

.. code-block:: bash

    (mvenv) set PATH="C:\Program Files\doxygen\bin";%PATH%

Now download `GraphViz <https://graphviz.org/download/>`_, and do the same.
e.g.

.. code-block:: bash

    (mvenv) set PATH="C:\Program Files\GraphViz\bin";%PATH%

For the C/C++-Python SWIG bindings, you need to install SWIG.
 
 C:\Users\cceagil\swigwin-4.0.2\swigwin-4.0.2\swig.exe
set PATH=C:\Users\cceagil\swigwin-4.0.2\swigwin-4.0.2;%PATH%

(venv) C:\Users\cceagil\repos\CompBioLibs\build>echo %PATH%
C:\Users\cceagil\swigwin-4.0.2\swigwin-4.0.2;"C:\Program Files\doxygen\bin";C:\Users\cceagil\venvs\venv\Scripts;C:\Program Files\Java\jdk1.8.0_291\bin;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C;C:\Program Files\Git\cmd;C:\Program Files\Java\jdk1.8.0_291\bin;C:\Users\cceagil\AppData\Local\Programs\Python\Python39\Scripts\;C:\Users\cceagil\AppData\Local\Programs\Python\Python39\;C:\Users\cceagil\AppData\Local\Microsoft\WindowsApps;C:\Program Files\Graphviz\bin

C:\Users\cceagil\repos\CompBioLibs\dependencies\libSBML-Dependencies-1.0.0-b1-win64-release-static
set CODE_SRC_DIR=C:\Users\cceagil\repos\CompBioLibs\liblx\src 
in build dir:
cmake -DCMAKE_BUILD_TYPE=Release -DWITH_PYTHON=ON -DWITH_STATIC_RUNTIME=ON -DWITH_DOXYGEN=TRUE -DWITH_CHECK=TRUE -DLIBLX_DEPENDENCY_DIR=C:\Users\cceagil\repos\CompBioLibs\dependencies\libSBML-Dependencies-1.0.0-b1-win64-release-static C:\Users\cceagil\repos\CompBioLibs\liblx

cmake not found
see https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-160#run-cmake-from-the-command-line
and https://docs.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-160
probably simpler to install cmake and update the path
x64-based provessor.
##cd C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools
cd C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build
PROCESSOR_ARCHITECTURE=AMD64
PROCESSOR_IDENTIFIER=Intel64 Family 6 Model 140 Stepping 1, GenuineIntel
vcvarsx86_amd64.bat

in build dir:
cd src\bindings\python
dir -> liblx.py
in Release dir: _liblx.pyd
so need to add Release to pythonpath
>>> import sys
>>> sys.path += ["C:\\Users\\cceagil\\repos\\CompBioLibs\\build\\src\\bindings\\python\\Release"]

or
(venv) C:\Users\cceagil\repos\CompBioLibs\build\src\bindings\python>set PYTHONPATH=C:\Users\cceagil\repos\CompBioLibs\build\src\bindings\python;C:\Users\cceagil\repos\CompBioLibs\build\src\bindings\python\Release
and then can use directly

ctest -C Release  NB seems to run test 2 ok without needing pythonpath

file:///C:/Users/cceagil/repos/CompBioLibs/build/docs/sphinx/index.html
