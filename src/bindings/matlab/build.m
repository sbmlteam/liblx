function build

  [detected_os, matlab, root] = determine_system();

  switch detected_os
    case 0
      build_win(matlab, root);
    case 1
      build_mac(matlab, root);
    case 2
      build_linux(matlab, root);
    otherwise
      error('OS not recognised');
  end;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% check what we are using
function [detected_os, matlab, root] = determine_system

  disp('Checking system ...');
  disp('Looking at software ...');
  % matlab = [0, 1]
  %     0 - octave
  %     1 - matlab
  if (strcmp(isoctave(), '0'))
    matlab = 1;
    disp('MATLAB detected');
  else
    matlab = 0;
    disp('Octave detected');
  end;

  disp('Looking at OS ...');
  % detected_os = [0, 1, 2]
  %      0 - windows
  %      1 - mac
  %      2 - unix
  if (ispc())
    detected_os = 0;
    disp('Windows OS detected');
  elseif(ismac())
    detected_os = 1;
    disp('Mac OS detected');
  elseif(isunix())
    detected_os = 2;
    disp('Linux OS detected');
  else
    error('Unable to establish operating system');
  end;

  disp('Checking directory structure ...');
  % need to check which directory we are in
  % if we are in the src directory we should 
  % be in directory ../src/bindings/matlab
  [remain, first] = fileparts(pwd);
  [remain1, second] = fileparts(remain);
  [remain2, third] = fileparts(remain1);

  if (~strcmp(first, 'matlab'))
    report_incorrect_dir(pwd, '/src/bindings/matlab');
  elseif (~strcmp(second, 'bindings'))
    report_incorrect_dir(pwd, '/src/bindings/matlab');
  elseif (~strcmp(third, 'src'))
    report_incorrect_dir(pwd, '/src/bindings/matlab');
  else
    root = remain2;
    disp('Expected directory structure found');
  end;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% tell user we are in the wrong location
function report_incorrect_dir(this_dir, expected)

  message = sprintf('You are in directory %s \nbut should be in %s', this_dir, expected);
  error(message);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% build on windows
function build_win(ismatlab, root)

  % check that the win/bin directory exists
  bin_dir = [root, filesep, 'win', filesep, 'bin'];
  disp(sprintf('Checking for the %s directory ...', bin_dir));
  if (exist(bin_dir, 'dir') ~= 7)
    error (sprintf('%s not found\n%s', bin_dir, ...
      'the libSBML source tree expects this directory to exist'));
  else
    disp('Checking for libraries ...');
    % check that the library files are all there
    lib{1} = [bin_dir, filesep, 'libsbml.lib'];
    lib{2} = [bin_dir, filesep, 'libsbml.dll'];
    lib{3} = [bin_dir, filesep, 'libxml2.lib'];
    lib{4} = [bin_dir, filesep, 'libxml2.dll'];
    lib{5} = [bin_dir, filesep, 'iconv.lib'];
    lib{6} = [bin_dir, filesep, 'iconv.dll'];
    lib{7} = [bin_dir, filesep, 'bzip2.lib'];
    lib{8} = [bin_dir, filesep, 'bzip2.dll'];

    found = 1;
    for i = 1:8
      if (exist(lib{i}) ~= 0)
        disp(sprintf('%s found', lib{i}));
      else
        disp(sprintf('%s not found', lib{i}));
        found = 0;
      end;
    end; 
    
    if (found == 0)
      error (sprintf('Not all dependencies could be found\n%s%s', ...
      'the libSBML source tree expects the dependencies to be in ', bin_dir));
    else
      disp('All dependencies found');
    end;
  end;
  
  % check that the include directory exists
  include_dir = [root, filesep, 'include'];
  disp(sprintf('Checking for the %s directory ...', include_dir));
  if (exist(include_dir, 'dir') ~= 7)
    error (sprintf('%s not found\n%s', include_dir, ...
      'the libSBML source tree expects this directory to exist'));
  end;
  
  if (ismatlab)
    % build the files
    inc_flag = ['-I', include_dir];
    buildMexFiles(inc_flag, lib{1});

  else
    % TO DO
    disp('Build on octave');
  end;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% build on mac
function build_mac(ismatlab, root)

  % check that libsbml is in usr/local/lib directory
  bin_dir = [];

  for i=1:length(strfind(pwd, filesep))
      bin_dir = [bin_dir, '..', filesep];
  end;
  bin_dir = [bin_dir, 'usr', filesep, 'local', filesep, 'lib'];
  disp('Checking for libraries ...');
  % check that the library files are all there
  lib{1} = [bin_dir, filesep, 'libsbml.dylib'];
  if (exist(lib{1}) == 0)
      disp('libsbml.dylib could not be found');
      new_bin_dir = input(sprintf('\n\n%s\n%s\n%s\n%s', ...
          'The build process assumes that libsbml', ...
          'has been installed at usr/local', ...
          'if libsbml.dylib is in another directory please enter the ', ...
          'full path to reach the directory from this directory: '), 's');
      lib{2} = [new_bin_dir, filesep, 'libsbml.dylib'];
      
      if (exist(lib{2}) == 0)
          error('libsbml.dylib could not be found');
      else
        lib{1} = lib{2};
      end;
  end;
  
  % check that the include directory exists
  include_dir = [root, filesep, 'include'];
  disp(sprintf('Checking for the %s directory ...', include_dir));
  if (exist(include_dir, 'dir') ~= 7)
    error (sprintf('%s not found\n%s', include_dir, ...
      'the libSBML source tree expects this directory to exist'));
  end;
  
  if (ismatlab)
    % build the files
    inc_flag = ['-I', include_dir];
    buildMexFiles(inc_flag, lib{1});

  else
    disp('Build on octave');
  end;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% build on linux
function build_linux(ismatlab, root)

  % check that libsbml is in usr/local/lib directory
  bin_dir = [];

  for i=1:length(strfind(pwd, filesep))
      bin_dir = [bin_dir, '..', filesep];
  end;
  bin_dir = [bin_dir, 'usr', filesep, 'local', filesep, 'lib'];
  disp('Checking for libraries ...');
  % check that the library files are all there
  lib{1} = [bin_dir, filesep, 'libsbml.so'];
  if (exist(lib{1}) == 0)
      disp('libsbml.so could not be found');
      new_bin_dir = input(sprintf('\n\n%s\n%s\n%s\n%s', ...
          'The build process assumes that libsbml', ...
          'has been installed at usr/local', ...
          'if libsbml.so is in another directory please enter the ', ...
          'full path to reach the directory from this directory: '), 's');
      lib{2} = [new_bin_dir, filesep, 'libsbml.so'];
      
      if (exist(lib{2}) == 0)
          error('libsbml.so could not be found');
      else
        lib{1} = lib{2};
      end;
  end;
  
  % check that the include directory exists
  include_dir = [root, filesep, 'include'];
  disp(sprintf('Checking for the %s directory ...', include_dir));
  if (exist(include_dir, 'dir') ~= 7)
    error (sprintf('%s not found\n%s', include_dir, ...
      'the libSBML source tree expects this directory to exist'));
  end;
  
  if (ismatlab)
    % build the files
    inc_flag = ['-I', include_dir];
    buildMexFiles(inc_flag, lib{1});

  else
    disp('Build on octave');
  end;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% runs the mex command for windows and matlab
% the messy file handle stuff is because this seems to be the best way to 
% be able to pass arguments to the function
function buildMexFiles(include, library)

  fhandle = @mex;
  disp('Building TranslateSBML ...');
  feval(fhandle, 'TranslateSBML.c', include, library);
  disp('Building OutputSBML ...');
  feval(fhandle, 'OutputSBML.c', include, library);

  transFile = strcat('TranslateSBML.', mexext());
  outFile = strcat('OutputSBML.', mexext());

  if ((exist(transFile) == 3 && ...
      exist(outFile) == 3))      
    disp(sprintf('%s\n%s', 'Build successful', ...
      'Now run the install script which will install and test the files'));
  else
    disp('Build failed');
  end;

