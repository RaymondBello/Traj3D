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
include external/imgui_bundle/external/CMakeFiles/imgui.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/imgui_bundle/external/CMakeFiles/imgui.dir/compiler_depend.make

# Include the progress variables for this target.
include external/imgui_bundle/external/CMakeFiles/imgui.dir/progress.make

# Include the compile flags for this target's objects.
include external/imgui_bundle/external/CMakeFiles/imgui.dir/flags.make

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui.cpp.o: external/imgui_bundle/external/CMakeFiles/imgui.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui.cpp
external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui.cpp.o: external/imgui_bundle/external/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui.cpp.o -MF CMakeFiles/imgui.dir/imgui/imgui/imgui.cpp.o.d -o CMakeFiles/imgui.dir/imgui/imgui/imgui.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui.cpp

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui/imgui.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui.cpp > CMakeFiles/imgui.dir/imgui/imgui/imgui.cpp.i

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui/imgui.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui.cpp -o CMakeFiles/imgui.dir/imgui/imgui/imgui.cpp.s

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_demo.cpp.o: external/imgui_bundle/external/CMakeFiles/imgui.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_demo.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui_demo.cpp
external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_demo.cpp.o: external/imgui_bundle/external/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_demo.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_demo.cpp.o -MF CMakeFiles/imgui.dir/imgui/imgui/imgui_demo.cpp.o.d -o CMakeFiles/imgui.dir/imgui/imgui/imgui_demo.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui_demo.cpp

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui/imgui_demo.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui_demo.cpp > CMakeFiles/imgui.dir/imgui/imgui/imgui_demo.cpp.i

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui/imgui_demo.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui_demo.cpp -o CMakeFiles/imgui.dir/imgui/imgui/imgui_demo.cpp.s

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_draw.cpp.o: external/imgui_bundle/external/CMakeFiles/imgui.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_draw.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui_draw.cpp
external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_draw.cpp.o: external/imgui_bundle/external/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_draw.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_draw.cpp.o -MF CMakeFiles/imgui.dir/imgui/imgui/imgui_draw.cpp.o.d -o CMakeFiles/imgui.dir/imgui/imgui/imgui_draw.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui_draw.cpp

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui/imgui_draw.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui_draw.cpp > CMakeFiles/imgui.dir/imgui/imgui/imgui_draw.cpp.i

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui/imgui_draw.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui_draw.cpp -o CMakeFiles/imgui.dir/imgui/imgui/imgui_draw.cpp.s

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_tables.cpp.o: external/imgui_bundle/external/CMakeFiles/imgui.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_tables.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui_tables.cpp
external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_tables.cpp.o: external/imgui_bundle/external/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_tables.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_tables.cpp.o -MF CMakeFiles/imgui.dir/imgui/imgui/imgui_tables.cpp.o.d -o CMakeFiles/imgui.dir/imgui/imgui/imgui_tables.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui_tables.cpp

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_tables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui/imgui_tables.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui_tables.cpp > CMakeFiles/imgui.dir/imgui/imgui/imgui_tables.cpp.i

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_tables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui/imgui_tables.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui_tables.cpp -o CMakeFiles/imgui.dir/imgui/imgui/imgui_tables.cpp.s

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_widgets.cpp.o: external/imgui_bundle/external/CMakeFiles/imgui.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_widgets.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui_widgets.cpp
external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_widgets.cpp.o: external/imgui_bundle/external/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_widgets.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_widgets.cpp.o -MF CMakeFiles/imgui.dir/imgui/imgui/imgui_widgets.cpp.o.d -o CMakeFiles/imgui.dir/imgui/imgui/imgui_widgets.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui_widgets.cpp

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui/imgui_widgets.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui_widgets.cpp > CMakeFiles/imgui.dir/imgui/imgui/imgui_widgets.cpp.i

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui/imgui_widgets.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/imgui_widgets.cpp -o CMakeFiles/imgui.dir/imgui/imgui/imgui_widgets.cpp.s

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/misc/cpp/imgui_stdlib.cpp.o: external/imgui_bundle/external/CMakeFiles/imgui.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/misc/cpp/imgui_stdlib.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/misc/cpp/imgui_stdlib.cpp
external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/misc/cpp/imgui_stdlib.cpp.o: external/imgui_bundle/external/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/misc/cpp/imgui_stdlib.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/misc/cpp/imgui_stdlib.cpp.o -MF CMakeFiles/imgui.dir/imgui/imgui/misc/cpp/imgui_stdlib.cpp.o.d -o CMakeFiles/imgui.dir/imgui/imgui/misc/cpp/imgui_stdlib.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/misc/cpp/imgui_stdlib.cpp

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/misc/cpp/imgui_stdlib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui/misc/cpp/imgui_stdlib.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/misc/cpp/imgui_stdlib.cpp > CMakeFiles/imgui.dir/imgui/imgui/misc/cpp/imgui_stdlib.cpp.i

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/misc/cpp/imgui_stdlib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui/misc/cpp/imgui_stdlib.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/misc/cpp/imgui_stdlib.cpp -o CMakeFiles/imgui.dir/imgui/imgui/misc/cpp/imgui_stdlib.cpp.s

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/misc/freetype/imgui_freetype.cpp.o: external/imgui_bundle/external/CMakeFiles/imgui.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/misc/freetype/imgui_freetype.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/misc/freetype/imgui_freetype.cpp
external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/misc/freetype/imgui_freetype.cpp.o: external/imgui_bundle/external/CMakeFiles/imgui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/misc/freetype/imgui_freetype.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/misc/freetype/imgui_freetype.cpp.o -MF CMakeFiles/imgui.dir/imgui/imgui/misc/freetype/imgui_freetype.cpp.o.d -o CMakeFiles/imgui.dir/imgui/imgui/misc/freetype/imgui_freetype.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/misc/freetype/imgui_freetype.cpp

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/misc/freetype/imgui_freetype.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui/misc/freetype/imgui_freetype.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/misc/freetype/imgui_freetype.cpp > CMakeFiles/imgui.dir/imgui/imgui/misc/freetype/imgui_freetype.cpp.i

external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/misc/freetype/imgui_freetype.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui/misc/freetype/imgui_freetype.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/imgui/imgui/misc/freetype/imgui_freetype.cpp -o CMakeFiles/imgui.dir/imgui/imgui/misc/freetype/imgui_freetype.cpp.s

# Object files for target imgui
imgui_OBJECTS = \
"CMakeFiles/imgui.dir/imgui/imgui/imgui.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui/imgui_demo.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui/imgui_draw.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui/imgui_tables.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui/imgui_widgets.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui/misc/cpp/imgui_stdlib.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui/misc/freetype/imgui_freetype.cpp.o"

# External object files for target imgui
imgui_EXTERNAL_OBJECTS =

external/imgui_bundle/external/libimgui.a: external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui.cpp.o
external/imgui_bundle/external/libimgui.a: external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_demo.cpp.o
external/imgui_bundle/external/libimgui.a: external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_draw.cpp.o
external/imgui_bundle/external/libimgui.a: external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_tables.cpp.o
external/imgui_bundle/external/libimgui.a: external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/imgui_widgets.cpp.o
external/imgui_bundle/external/libimgui.a: external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/misc/cpp/imgui_stdlib.cpp.o
external/imgui_bundle/external/libimgui.a: external/imgui_bundle/external/CMakeFiles/imgui.dir/imgui/imgui/misc/freetype/imgui_freetype.cpp.o
external/imgui_bundle/external/libimgui.a: external/imgui_bundle/external/CMakeFiles/imgui.dir/build.make
external/imgui_bundle/external/libimgui.a: external/imgui_bundle/external/CMakeFiles/imgui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libimgui.a"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && $(CMAKE_COMMAND) -P CMakeFiles/imgui.dir/cmake_clean_target.cmake
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imgui.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/imgui_bundle/external/CMakeFiles/imgui.dir/build: external/imgui_bundle/external/libimgui.a
.PHONY : external/imgui_bundle/external/CMakeFiles/imgui.dir/build

external/imgui_bundle/external/CMakeFiles/imgui.dir/clean:
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && $(CMAKE_COMMAND) -P CMakeFiles/imgui.dir/cmake_clean.cmake
.PHONY : external/imgui_bundle/external/CMakeFiles/imgui.dir/clean

external/imgui_bundle/external/CMakeFiles/imgui.dir/depend:
	cd /Users/raybello/Github/TrajectorySim/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/raybello/Github/TrajectorySim /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external /Users/raybello/Github/TrajectorySim/build /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external/CMakeFiles/imgui.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : external/imgui_bundle/external/CMakeFiles/imgui.dir/depend

