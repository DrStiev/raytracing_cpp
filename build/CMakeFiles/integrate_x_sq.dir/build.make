# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\personal\raytracing_Cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\personal\raytracing_Cpp\build

# Include any dependencies generated for this target.
include CMakeFiles/integrate_x_sq.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/integrate_x_sq.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/integrate_x_sq.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/integrate_x_sq.dir/flags.make

CMakeFiles/integrate_x_sq.dir/src/integrate_x_sq.cc.obj: CMakeFiles/integrate_x_sq.dir/flags.make
CMakeFiles/integrate_x_sq.dir/src/integrate_x_sq.cc.obj: CMakeFiles/integrate_x_sq.dir/includes_CXX.rsp
CMakeFiles/integrate_x_sq.dir/src/integrate_x_sq.cc.obj: E:/personal/raytracing_Cpp/src/integrate_x_sq.cc
CMakeFiles/integrate_x_sq.dir/src/integrate_x_sq.cc.obj: CMakeFiles/integrate_x_sq.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=E:\personal\raytracing_Cpp\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/integrate_x_sq.dir/src/integrate_x_sq.cc.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/integrate_x_sq.dir/src/integrate_x_sq.cc.obj -MF CMakeFiles\integrate_x_sq.dir\src\integrate_x_sq.cc.obj.d -o CMakeFiles\integrate_x_sq.dir\src\integrate_x_sq.cc.obj -c E:\personal\raytracing_Cpp\src\integrate_x_sq.cc

CMakeFiles/integrate_x_sq.dir/src/integrate_x_sq.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/integrate_x_sq.dir/src/integrate_x_sq.cc.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\personal\raytracing_Cpp\src\integrate_x_sq.cc > CMakeFiles\integrate_x_sq.dir\src\integrate_x_sq.cc.i

CMakeFiles/integrate_x_sq.dir/src/integrate_x_sq.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/integrate_x_sq.dir/src/integrate_x_sq.cc.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\personal\raytracing_Cpp\src\integrate_x_sq.cc -o CMakeFiles\integrate_x_sq.dir\src\integrate_x_sq.cc.s

# Object files for target integrate_x_sq
integrate_x_sq_OBJECTS = \
"CMakeFiles/integrate_x_sq.dir/src/integrate_x_sq.cc.obj"

# External object files for target integrate_x_sq
integrate_x_sq_EXTERNAL_OBJECTS =

integrate_x_sq.exe: CMakeFiles/integrate_x_sq.dir/src/integrate_x_sq.cc.obj
integrate_x_sq.exe: CMakeFiles/integrate_x_sq.dir/build.make
integrate_x_sq.exe: CMakeFiles/integrate_x_sq.dir/linkLibs.rsp
integrate_x_sq.exe: CMakeFiles/integrate_x_sq.dir/objects1.rsp
integrate_x_sq.exe: CMakeFiles/integrate_x_sq.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=E:\personal\raytracing_Cpp\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable integrate_x_sq.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\integrate_x_sq.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/integrate_x_sq.dir/build: integrate_x_sq.exe
.PHONY : CMakeFiles/integrate_x_sq.dir/build

CMakeFiles/integrate_x_sq.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\integrate_x_sq.dir\cmake_clean.cmake
.PHONY : CMakeFiles/integrate_x_sq.dir/clean

CMakeFiles/integrate_x_sq.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\personal\raytracing_Cpp E:\personal\raytracing_Cpp E:\personal\raytracing_Cpp\build E:\personal\raytracing_Cpp\build E:\personal\raytracing_Cpp\build\CMakeFiles\integrate_x_sq.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/integrate_x_sq.dir/depend

