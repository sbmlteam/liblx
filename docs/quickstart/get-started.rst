Quickstart
==========

.. _building_library:

Building the libLX library
--------------------------
The first task is to clone the libLX repository, and then ``cd`` into it:

.. code-block:: bash

    git clone https://github.com/sbmlteam/liblx.git
    cd liblx

You then need to install ``check`` (unit testing library for C). Example (MacOS):

.. code-block:: bash

    brew install check

It might be necessary to do this in a virtual environment.

We then create and enter a ``build`` folder, within the ``liblx`` repository we have just cloned,
to store the results of the build we are going to make:

.. code-block:: bash

    mkdir build
    cd build

[NB Added later: Despite what I've done here, it is generally recommended NOT to have the build within the
same directory structure as the repo; best to move completely outside. It is then termed an
"out of source build". If you do it properly, the `cmake` commands below should end with the directory of the
source files you are building, rather than just `..` as I have done here. Hopefully later we'll have some
time to update the wording of this doc to remove the need for this note. Sorry!] 

We can now invoke CMake (assuming you have it installed!), with various options as appropriate. For example

.. code-block:: bash

    cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON -DWITH_CHECK=TRUE -G "Unix Makefiles" ..

The trailing ``..`` at the end of this command refers to the folder immediately above our new `build` folder, i.e. the
top-level ``liblx`` folder in the repository we cloned. The top-level ``liblx`` folder contains the top-level ``CMakeLists.txt``
file which controls the builds. (Sub-folders have a lower-level ``CMakeLists.txt`` file.)

The ``-DWITH_CHECK=TRUE`` option means that we have requested the test suite is built as well as the library itself.
Assuming the ``cmake`` command completes successfully, there should now be a ``Makefile`` in the ``build/`` folder;
we can then issue the command:

.. code-block:: bash

    make

This is the instruction to compile the ``libLX`` library (and test code).

If this completes successfully, you should find static and dynamic versions of the library have been built in the
newly-created ``src`` sub-folder in ``build/``. On a Mac, these will be ``liblx-static.a`` and ``liblx.dylib``.


Running the tests
-----------------
Assuming you used the ``-DWITH_CHECK=TRUE`` option in your ``cmake`` command, you should have a test program,
``src/liblx/xml/test/test_sbml_xml``, which you can invoke with ``ctest``.

To see more verbose output, e.g. because a test has failed, use ``ctest -V``.


.. _building_bindings:

Building the SWIG language bindings
-----------------------------------
``liblx`` is written in C/C++. But we can create an interface from another programming language (e.g. Python).
To do this, we generate "language bindings" from a program called `SWIG <http://www.swig.org/>`_. So, first,
we need to install SWIG. Example (MacOS):

.. code-block:: bash

    brew install swig

We then need to re-issue our ``cmake`` command with a suitable addition: ``-DWITH_PYTHON=TRUE``, and then ``make`` again.

NB for all the different ``cmake`` invocations in this document, it may be necessary each time to delete and then re-create
the ``build/`` directory (and ``cd`` into it, of course).



.. _building_with_choice_of_xml_libs:

Building with a choice of XML libraries
---------------------------------------



.. _building_documentation:

Building the documentation
--------------------------
To generate the documentation, you need `Sphinx <https://www.sphinx-doc.org/en/master/>`_,
`Doxygen <https://www.doxygen.nl/index.html>`_ and `breathe <https://breathe.readthedocs.io/en/latest/quickstart.html>`_
installed. It is probably best to refer to their websites to find the preferred way of installing on your operating system.

??? brew install sphinx-doc  # to /usr/local/opt/sphinx-doc/bin
??? or pip install -U sphinx   -> sphinx-build --version = "sphinx-build 4.0.2"
brew install doxygen   # e.g. to /usr/local/bin/doxygen
pip install breathe # see
pip show breathe -> ~/repos/Deviser/deviser/generator/pytest_files/cbl-env/lib/python3.6/site-packages/breathe

If you need to have ``sphinx-doc`` first in your ``PATH``, run:

.. code-block:: bash

     echo 'export PATH="/usr/local/opt/sphinx-doc/bin:$PATH"' >> ~/.bash_profile

can use copasi cmake module FindSphinx.cmake

cmake -DWITH_DOXYGEN=ON -DDOXYGEN_EXECUTABLE=/usr/local/bin/doxygen ..

-- Found Doxygen: /usr/local/bin/doxygen (found version "1.9.1") found components: doxygen missing components: dot
The dot is from graphviz, which can be used by Doxygen to draw inheritance diagrams etc


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


Since the documentation is not generated by default, you have to reconfigure your ``cmake``
project for the libLX API next. So change into your build folder from before, and
reconfigure with the option ``-DWITH_DOXYGEN=ON``.

[If necessary, add the link to the Doxygen executable (if your system doesn't pick it up),
e.g. ``-DDOXYGEN_EXECUTABLE=/usr/local/bin/doxygen``] in the ``cmake`` command below (before the final ``..``).

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
    Running Sphinx v4.0.2
    loading pickled environment... done
    building [mo]: targets for 0 po files that are out of date
    building [html]: targets for 1 source files that are out of date
    updating environment: 0 added, 1 changed, 0 removed
    reading sources... [100%] quickstart/get-started
    ...
    ...
    build succeeded.

    The HTML pages are in sphinx.
    [100%] Built target Sphinx

    (venv) build >

And at this point you have the HTML pages generated in ``./docs/sphinx/`` with the 
main document being ``./docs/sphinx/index.html``. This page will be ``./docs/sphinx/quickstart/get-started.html``.

The documentation will then be accessible from ``liblx/build/docs/sphinx/index.html``.



