# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\wangsy\Desktop\ml_proj\DecisionTree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\wangsy\Desktop\ml_proj\DecisionTree\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/DesitionTree.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DesitionTree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DesitionTree.dir/flags.make

CMakeFiles/DesitionTree.dir/test/test.cc.obj: CMakeFiles/DesitionTree.dir/flags.make
CMakeFiles/DesitionTree.dir/test/test.cc.obj: ../test/test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\wangsy\Desktop\ml_proj\DecisionTree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DesitionTree.dir/test/test.cc.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\DesitionTree.dir\test\test.cc.obj -c C:\Users\wangsy\Desktop\ml_proj\DecisionTree\test\test.cc

CMakeFiles/DesitionTree.dir/test/test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DesitionTree.dir/test/test.cc.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\wangsy\Desktop\ml_proj\DecisionTree\test\test.cc > CMakeFiles\DesitionTree.dir\test\test.cc.i

CMakeFiles/DesitionTree.dir/test/test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DesitionTree.dir/test/test.cc.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\wangsy\Desktop\ml_proj\DecisionTree\test\test.cc -o CMakeFiles\DesitionTree.dir\test\test.cc.s

# Object files for target DesitionTree
DesitionTree_OBJECTS = \
"CMakeFiles/DesitionTree.dir/test/test.cc.obj"

# External object files for target DesitionTree
DesitionTree_EXTERNAL_OBJECTS =

DesitionTree.exe: CMakeFiles/DesitionTree.dir/test/test.cc.obj
DesitionTree.exe: CMakeFiles/DesitionTree.dir/build.make
DesitionTree.exe: CMakeFiles/DesitionTree.dir/linklibs.rsp
DesitionTree.exe: CMakeFiles/DesitionTree.dir/objects1.rsp
DesitionTree.exe: CMakeFiles/DesitionTree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\wangsy\Desktop\ml_proj\DecisionTree\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DesitionTree.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\DesitionTree.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DesitionTree.dir/build: DesitionTree.exe

.PHONY : CMakeFiles/DesitionTree.dir/build

CMakeFiles/DesitionTree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\DesitionTree.dir\cmake_clean.cmake
.PHONY : CMakeFiles/DesitionTree.dir/clean

CMakeFiles/DesitionTree.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\wangsy\Desktop\ml_proj\DecisionTree C:\Users\wangsy\Desktop\ml_proj\DecisionTree C:\Users\wangsy\Desktop\ml_proj\DecisionTree\cmake-build-debug C:\Users\wangsy\Desktop\ml_proj\DecisionTree\cmake-build-debug C:\Users\wangsy\Desktop\ml_proj\DecisionTree\cmake-build-debug\CMakeFiles\DesitionTree.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DesitionTree.dir/depend

