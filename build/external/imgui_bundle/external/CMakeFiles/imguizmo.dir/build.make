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
include external/imgui_bundle/external/CMakeFiles/imguizmo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/imgui_bundle/external/CMakeFiles/imguizmo.dir/compiler_depend.make

# Include the progress variables for this target.
include external/imgui_bundle/external/CMakeFiles/imguizmo.dir/progress.make

# Include the compile flags for this target's objects.
include external/imgui_bundle/external/CMakeFiles/imguizmo.dir/flags.make

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/GraphEditor.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/GraphEditor.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/GraphEditor.cpp
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/GraphEditor.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/GraphEditor.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/GraphEditor.cpp.o -MF CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/GraphEditor.cpp.o.d -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/GraphEditor.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/GraphEditor.cpp

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/GraphEditor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/GraphEditor.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/GraphEditor.cpp > CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/GraphEditor.cpp.i

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/GraphEditor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/GraphEditor.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/GraphEditor.cpp -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/GraphEditor.cpp.s

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImCurveEdit.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImCurveEdit.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/ImCurveEdit.cpp
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImCurveEdit.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImCurveEdit.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImCurveEdit.cpp.o -MF CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImCurveEdit.cpp.o.d -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImCurveEdit.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/ImCurveEdit.cpp

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImCurveEdit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImCurveEdit.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/ImCurveEdit.cpp > CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImCurveEdit.cpp.i

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImCurveEdit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImCurveEdit.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/ImCurveEdit.cpp -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImCurveEdit.cpp.s

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGradient.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGradient.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/ImGradient.cpp
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGradient.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGradient.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGradient.cpp.o -MF CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGradient.cpp.o.d -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGradient.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/ImGradient.cpp

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGradient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGradient.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/ImGradient.cpp > CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGradient.cpp.i

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGradient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGradient.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/ImGradient.cpp -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGradient.cpp.s

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGuizmo.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGuizmo.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/ImGuizmo.cpp
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGuizmo.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGuizmo.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGuizmo.cpp.o -MF CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGuizmo.cpp.o.d -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGuizmo.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/ImGuizmo.cpp

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGuizmo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGuizmo.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/ImGuizmo.cpp > CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGuizmo.cpp.i

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGuizmo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGuizmo.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/ImGuizmo.cpp -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGuizmo.cpp.s

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImSequencer.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImSequencer.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/ImSequencer.cpp
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImSequencer.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImSequencer.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImSequencer.cpp.o -MF CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImSequencer.cpp.o.d -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImSequencer.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/ImSequencer.cpp

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImSequencer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImSequencer.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/ImSequencer.cpp > CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImSequencer.cpp.i

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImSequencer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImSequencer.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmo/ImSequencer.cpp -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImSequencer.cpp.s

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp.o -MF CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp.o.d -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp > CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp.i

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp.s

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp.o -MF CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp.o.d -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp > CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp.i

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp.s

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp.o -MF CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp.o.d -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp > CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp.i

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp.s

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/flags.make
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp.o: /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp.o: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp.o"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp.o -MF CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp.o.d -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp.o -c /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp.i"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp > CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp.i

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp.s"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && /Library/Developer/CommandLineTools/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp -o CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp.s

# Object files for target imguizmo
imguizmo_OBJECTS = \
"CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/GraphEditor.cpp.o" \
"CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImCurveEdit.cpp.o" \
"CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGradient.cpp.o" \
"CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGuizmo.cpp.o" \
"CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImSequencer.cpp.o" \
"CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp.o" \
"CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp.o" \
"CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp.o" \
"CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp.o"

# External object files for target imguizmo
imguizmo_EXTERNAL_OBJECTS =

external/imgui_bundle/external/libimguizmo.a: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/GraphEditor.cpp.o
external/imgui_bundle/external/libimguizmo.a: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImCurveEdit.cpp.o
external/imgui_bundle/external/libimguizmo.a: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGradient.cpp.o
external/imgui_bundle/external/libimguizmo.a: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImGuizmo.cpp.o
external/imgui_bundle/external/libimguizmo.a: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmo/ImSequencer.cpp.o
external/imgui_bundle/external/libimguizmo.a: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImCurveEditPure.cpp.o
external/imgui_bundle/external/libimguizmo.a: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGradientPure.cpp.o
external/imgui_bundle/external/libimguizmo.a: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImGuizmoPure.cpp.o
external/imgui_bundle/external/libimguizmo.a: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/ImGuizmo/ImGuizmoPure/ImZoomSliderPure.cpp.o
external/imgui_bundle/external/libimguizmo.a: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/build.make
external/imgui_bundle/external/libimguizmo.a: external/imgui_bundle/external/CMakeFiles/imguizmo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/raybello/Github/TrajectorySim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library libimguizmo.a"
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && $(CMAKE_COMMAND) -P CMakeFiles/imguizmo.dir/cmake_clean_target.cmake
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imguizmo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/imgui_bundle/external/CMakeFiles/imguizmo.dir/build: external/imgui_bundle/external/libimguizmo.a
.PHONY : external/imgui_bundle/external/CMakeFiles/imguizmo.dir/build

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/clean:
	cd /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external && $(CMAKE_COMMAND) -P CMakeFiles/imguizmo.dir/cmake_clean.cmake
.PHONY : external/imgui_bundle/external/CMakeFiles/imguizmo.dir/clean

external/imgui_bundle/external/CMakeFiles/imguizmo.dir/depend:
	cd /Users/raybello/Github/TrajectorySim/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/raybello/Github/TrajectorySim /Users/raybello/Github/TrajectorySim/external/imgui_bundle/external /Users/raybello/Github/TrajectorySim/build /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external /Users/raybello/Github/TrajectorySim/build/external/imgui_bundle/external/CMakeFiles/imguizmo.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : external/imgui_bundle/external/CMakeFiles/imguizmo.dir/depend

