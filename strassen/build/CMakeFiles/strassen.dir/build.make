# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/justyful/vtm_prac_23_24/strassen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/justyful/vtm_prac_23_24/strassen/build

# Include any dependencies generated for this target.
include CMakeFiles/strassen.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/strassen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/strassen.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/strassen.dir/flags.make

CMakeFiles/strassen.dir/strassen.cpp.o: CMakeFiles/strassen.dir/flags.make
CMakeFiles/strassen.dir/strassen.cpp.o: /Users/justyful/vtm_prac_23_24/strassen/strassen.cpp
CMakeFiles/strassen.dir/strassen.cpp.o: CMakeFiles/strassen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/justyful/vtm_prac_23_24/strassen/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/strassen.dir/strassen.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/strassen.dir/strassen.cpp.o -MF CMakeFiles/strassen.dir/strassen.cpp.o.d -o CMakeFiles/strassen.dir/strassen.cpp.o -c /Users/justyful/vtm_prac_23_24/strassen/strassen.cpp

CMakeFiles/strassen.dir/strassen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/strassen.dir/strassen.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/justyful/vtm_prac_23_24/strassen/strassen.cpp > CMakeFiles/strassen.dir/strassen.cpp.i

CMakeFiles/strassen.dir/strassen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/strassen.dir/strassen.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/justyful/vtm_prac_23_24/strassen/strassen.cpp -o CMakeFiles/strassen.dir/strassen.cpp.s

# Object files for target strassen
strassen_OBJECTS = \
"CMakeFiles/strassen.dir/strassen.cpp.o"

# External object files for target strassen
strassen_EXTERNAL_OBJECTS =

libstrassen.a: CMakeFiles/strassen.dir/strassen.cpp.o
libstrassen.a: CMakeFiles/strassen.dir/build.make
libstrassen.a: CMakeFiles/strassen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/justyful/vtm_prac_23_24/strassen/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libstrassen.a"
	$(CMAKE_COMMAND) -P CMakeFiles/strassen.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/strassen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/strassen.dir/build: libstrassen.a
.PHONY : CMakeFiles/strassen.dir/build

CMakeFiles/strassen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/strassen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/strassen.dir/clean

CMakeFiles/strassen.dir/depend:
	cd /Users/justyful/vtm_prac_23_24/strassen/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/justyful/vtm_prac_23_24/strassen /Users/justyful/vtm_prac_23_24/strassen /Users/justyful/vtm_prac_23_24/strassen/build /Users/justyful/vtm_prac_23_24/strassen/build /Users/justyful/vtm_prac_23_24/strassen/build/CMakeFiles/strassen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/strassen.dir/depend

