# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/raybello/Github/TrajectorySim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/raybello/Github/TrajectorySim/build

# Include any dependencies generated for this target.
include external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/compiler_depend.make

# Include the progress variables for this target.
include external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/progress.make

# Include the compile flags for this target's objects.
include external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/flags.make

external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/ImCoolBar/ImCoolBar/ImCoolbar.cpp.o: external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/ImCoolBar/ImCoolBar/ImCoolbar.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImCoolBar/ImCoolBar/ImCoolbar.cpp
external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/ImCoolBar/ImCoolBar/ImCoolbar.cpp.o: external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/ImCoolBar/ImCoolBar/ImCoolbar.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/ImCoolBar/ImCoolBar/ImCoolbar.cpp.o -MF CMakeFiles/imcoolbar.dir/ImCoolBar/ImCoolBar/ImCoolbar.cpp.o.d -o CMakeFiles/imcoolbar.dir/ImCoolBar/ImCoolBar/ImCoolbar.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImCoolBar/ImCoolBar/ImCoolbar.cpp

external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/ImCoolBar/ImCoolBar/ImCoolbar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imcoolbar.dir/ImCoolBar/ImCoolBar/ImCoolbar.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImCoolBar/ImCoolBar/ImCoolbar.cpp > CMakeFiles/imcoolbar.dir/ImCoolBar/ImCoolBar/ImCoolbar.cpp.i

external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/ImCoolBar/ImCoolBar/ImCoolbar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imcoolbar.dir/ImCoolBar/ImCoolBar/ImCoolbar.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImCoolBar/ImCoolBar/ImCoolbar.cpp -o CMakeFiles/imcoolbar.dir/ImCoolBar/ImCoolBar/ImCoolbar.cpp.s

# Object files for target imcoolbar
imcoolbar_OBJECTS = \
"CMakeFiles/imcoolbar.dir/ImCoolBar/ImCoolBar/ImCoolbar.cpp.o"

# External object files for target imcoolbar
imcoolbar_EXTERNAL_OBJECTS =

external/imgui_bundle/external/libimcoolbar.a: external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/ImCoolBar/ImCoolBar/ImCoolbar.cpp.o
external/imgui_bundle/external/libimcoolbar.a: external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/build.make
external/imgui_bundle/external/libimcoolbar.a: external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libimcoolbar.a"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && $(CMAKE_COMMAND) -P CMakeFiles/imcoolbar.dir/cmake_clean_target.cmake
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imcoolbar.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/build: external/imgui_bundle/external/libimcoolbar.a
.PHONY : external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/build

external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/clean:
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && $(CMAKE_COMMAND) -P CMakeFiles/imcoolbar.dir/cmake_clean.cmake
.PHONY : external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/clean

external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/depend:
	cd /Users/raybello/Github/TrajectorySim/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/raybello/Github/TrajectorySim /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external /Users/raybello/Github/TrajectorySim/build /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : external/imgui_bundle/external/CMakeFiles/imcoolbar.dir/depend

