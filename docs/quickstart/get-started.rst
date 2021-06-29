Quickstart
==========

.. _building_library:

Building the libLX library
--------------------------
The first task is to clone the libLX repository:

.. code-block:: bash

    git clone https://github.com/sbmlteam/liblx.git

You then need to install `check` (unit testing library for C). Example (MacOS):

.. code-block:: bash

    brew install check

We then create and enter a `build` folder, within the `liblx` repository we have just cloned,
to store the results of the build we are going to make:

.. code-block:: bash

    mkdir -p liblx/build
    cd liblx/build

This section must mention a `build/` folder.

We can now invoke CMake (assuming you have it installed!), with various options as appropriate. For example

.. code-block:: bash

    cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DWITH_CHECK=TRUE -G "Unix Makefiles" ..

The trailing `..` at the end of this command refers to the folder immediately above our new `build` folder, i.e. the
top-level `liblx` folder in the repository we cloned. The top-level `liblx` folder contains the top-level `CMakeLists.txt`
file which controls the builds. (Sub-folders have a lower-level `CMakeLists.txt` file.)

The `-DWITH_CHECK=TRUE` option means that we have requested the test suite is built as well as the library itself.
Assuming the `cmake` command completes successfully, there should now be a `Makefile` in the `build/` folder;
we can then issue the command:

.. code-block:: bash

    make

This is the instruction to compile the `libLX` library (and test code).

If this completes successfully, you should find static and dynamic versions of the library have been built in the
newly-created `src` sub-folder in `build/`. On a Mac, these will be `liblx-static.a` and `liblx.dylib`.

2. install check (unit testing library for C) - e.g. brew install check  -> /usr/local/Cellar/check/0.15.2/
3. git clone https://github.com/sbmlteam/liblx.git    (in a suitable directory).
In my case, it creates /Users/matthewgillman/repos/libLX/liblx/ when I do this command in /Users/matthewgillman/repos/libLX/
4. cd liblx
5. mkdir build   -  the results of the build will be in here.
6. cd build
7. cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DWITH_CHECK=TRUE -G "Unix Makefiles" /Users/matthewgillman/repos/libLX/liblx/
Note that the directory at the end of the cmake command above is the top-level directory of the cloned repo (i.e. it contains the top-level CMakeLists.txt file).
8. make
9. invoke test script In my build subdir, it is src/liblx/xml/test/test_sbml_xml
On Mac, this builds build/src/liblx-static.a and build/src/liblx.dylib


Running the tests - check the next line is correct.
-----------------
We use the testing framework catch2 <https://github.com/catchorg/Catch2> and
integrated it with the cmake build, so after building the library you can run
the tests using ``ctest``:

.. code-block:: bash

    (venv) build > ctest -V

If you want to run tests on another build configuration, you can specify those
using the ``-C`` option. So for example for the debug build:

.. code-block:: bash

    (venv) build > ctest -C Debug -V     # check this is true for liblx




.. _building_bindings:

Building the SWIG language bindings
-----------------------------------
install swig e.g. brew install swig


.. _building_documentation:

Building the documentation
--------------------------
add `-DWITH_DOXYGEN=ON` to the `cmake` command.
Need Sphinx and Doxygen installed.
??? brew install sphinx-doc  # to /usr/local/opt/sphinx-doc/bin
??? or pip install -U sphinx   -> sphinx-build --version = "sphinx-build 4.0.2"
brew install doxygen   # e.g. to /usr/local/bin/doxygen
pip install breathe # see https://breathe.readthedocs.io/en/latest/quickstart.html
pip show breathe -> /Users/matthewgillman/repos/Deviser/deviser/generator/pytest_files/cbl-env/lib/python3.6/site-packages/breathe

If you need to have sphinx-doc first in your PATH, run:
  echo 'export PATH="/usr/local/opt/sphinx-doc/bin:$PATH"' >> /Users/matthewgillman/.bash_profile
can use copasi cmake module FindSphinx.cmake

cmake -DWITH_DOXYGEN=ON -DDOXYGEN_EXECUTABLE=/usr/local/bin/doxygen ..

-- Found Doxygen: /usr/local/bin/doxygen (found version "1.9.1") found components: doxygen missing components: dot
The dot is from graphviz, which can be used by Doxygen to draw inheritance diagrams etc


The documentation is automatically built on readthedocs with every commit. However, you
can still generate the documentation locally along your normal build (see `Building the library`_). For that you will 
need the following requirements installed: 

  * doxygen <https://www.doxygen.nl>
  * python3

Next you need the following python packages ``breathe`` and ``sphinx_rtd_theme``. So we start
by creating a virtual environment, activating it and installing the packages into it. 

.. code-block:: bash

    ~ > python3 -m venv venv 
    ~ > . ./venv/bin/activate
    (venv) ~ > pip install sphinx_rtd_theme breathe
    (venv) ~ > brew install doxygen

The command ``pip show breathe`` will show whereabouts on your system ``breathe`` has been installed.
This location needs to be added to your ``PYTHONPATH`` before building the documentation.
For example, if the ``breathe`` directory is installed as ``/Users/smith/venv/lib/python3.6/site-packages/breathe``,
add ``/Users/smith/venv/lib/python3.6/site-packages/`` to your ``PYTHONPATH``. For example:

.. code-block:: bash

    > export PYTHONPATH="/Users/smith/venv/lib/python3.6/site-packages/"
    > echo $PYTHONPATH
    /Users/smith/venv/lib/python3.6/site-packages/


Since the documentation is not generated by default, you have to reconfigure your cmake
project for the libLX API next. So change into your build folder from before, and
reconfigure with the option ``-DWITH_DOXYGEN=ON``.

.. code-block:: bash

    (venv) ~ > cd liblx/build
    (venv) build > cmake -DWITH_DOXYGEN=ON ..

    add some typical cmake output here

    ...
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /some/path/or/other/build
    (venv) build >

Errors would have shown if Doxygen or Sphinx could not be found in the process. Now you
are ready to build the documentation with: 

.. code-block:: bash

    (venv) build > make Sphinx
    [ 50%] Generating documentation with Sphinx
    Running Sphinx v3.5.4

    .... add sample output here .....

    build succeeded.

    The HTML pages are in sphinx.
    [100%] Built target Sphinx

    (venv) build >

And at this point you have the HTML pages generated in ``./docs/sphinx/`` with the 
main document being ``./docs/sphinx/index.html``





The following is specific to COPASI. Add liblx details as appropriate...
========================================================================



You can also run the test binary directly, but in that case test files provided in
``./tests/test-data`` will not be automatically found, as the source dir is not known. 

.. code-block:: bash

    (venv) build > ./tests/test_api
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    test_api.exe is a Catch v1.5.6 host application.
    Run with -? for options

    -------------------------------------------------------------------------------
    load copasi file and access via regular COPASI api
    -------------------------------------------------------------------------------
    /copasi-api/tests/TestCore.cpp(32)
    ...............................................................................

    /copasi-api/tests/TestCore.cpp(38): FAILED:
    REQUIRE( dm->loadModel(fileName, 0) == true )
    with expansion:
        false == true

    ===============================================================================
    test cases:  2 |  1 passed | 1 failed
    assertions: 22 | 21 passed | 1 failed

In that case you can specify an environment variable ``srcdir`` pointing to it: 

.. code-block:: bash

    (venv) build > srcdir=/copasi-api/tests ./tests/test_api
    ===============================================================================
    All tests passed (24 assertions in 2 test cases)

Additional options of the test runner: 

.. code-block:: bash

    (venv) build > ./tests/test_api -?
    Catch v1.5.6
    usage:
        test_api [<test name, pattern or tags> ...] [options]

    where options are:
        -?, -h, --help               display usage information
        -l, --list-tests             list all/matching test cases
        -t, --list-tags              list all/matching tags
        -s, --success                include successful tests in output
        -b, --break                  break into debugger on failure
        -e, --nothrow                skip exception tests
        -i, --invisibles             show invisibles (tabs, newlines)
        -o, --out <filename>         output filename
        -r, --reporter <name>        reporter to use (defaults to console)
        -n, --name <name>            suite name
        -a, --abort                  abort at first failure
        -x, --abortx <no. failures>  abort after x failures
        -w, --warn <warning name>    enable warnings
        -d, --durations <yes|no>     show test durations
        -f, --input-file <filename>  load test names to run from a file
        -#, --filenames-as-tags      adds a tag for the filename
        --list-test-names-only       list all/matching test cases names only
        --list-reporters             list all reporters
        --order <decl|lex|rand>      test case order (defaults to decl)
        --rng-seed <'time'|number>   set a specific seed for random numbers
        --force-colour               force colourised output (deprecated)
        --use-colour <yes|no>        should output be colourised
