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
include CMakeFiles/cos_cubed.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cos_cubed.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cos_cubed.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cos_cubed.dir/flags.make

CMakeFiles/cos_cubed.dir/src/cos_cubed.cc.obj: CMakeFiles/cos_cubed.dir/flags.make
CMakeFiles/cos_cubed.dir/src/cos_cubed.cc.obj: CMakeFiles/cos_cubed.dir/includes_CXX.rsp
CMakeFiles/cos_cubed.dir/src/cos_cubed.cc.obj: E:/personal/raytracing_Cpp/src/cos_cubed.cc
CMakeFiles/cos_cubed.dir/src/cos_cubed.cc.obj: CMakeFiles/cos_cubed.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=E:\personal\raytracing_Cpp\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cos_cubed.dir/src/cos_cubed.cc.obj"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cos_cubed.dir/src/cos_cubed.cc.obj -MF CMakeFiles\cos_cubed.dir\src\cos_cubed.cc.obj.d -o CMakeFiles\cos_cubed.dir\src\cos_cubed.cc.obj -c E:\personal\raytracing_Cpp\src\cos_cubed.cc

CMakeFiles/cos_cubed.dir/src/cos_cubed.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cos_cubed.dir/src/cos_cubed.cc.i"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\personal\raytracing_Cpp\src\cos_cubed.cc > CMakeFiles\cos_cubed.dir\src\cos_cubed.cc.i

CMakeFiles/cos_cubed.dir/src/cos_cubed.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cos_cubed.dir/src/cos_cubed.cc.s"
	C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\personal\raytracing_Cpp\src\cos_cubed.cc -o CMakeFiles\cos_cubed.dir\src\cos_cubed.cc.s

# Object files for target cos_cubed
cos_cubed_OBJECTS = \
"CMakeFiles/cos_cubed.dir/src/cos_cubed.cc.obj"

# External object files for target cos_cubed
cos_cubed_EXTERNAL_OBJECTS =

cos_cubed.exe: CMakeFiles/cos_cubed.dir/src/cos_cubed.cc.obj
cos_cubed.exe: CMakeFiles/cos_cubed.dir/build.make
cos_cubed.exe: CMakeFiles/cos_cubed.dir/linkLibs.rsp
cos_cubed.exe: CMakeFiles/cos_cubed.dir/objects1.rsp
cos_cubed.exe: CMakeFiles/cos_cubed.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=E:\personal\raytracing_Cpp\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cos_cubed.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\cos_cubed.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cos_cubed.dir/build: cos_cubed.exe
.PHONY : CMakeFiles/cos_cubed.dir/build

CMakeFiles/cos_cubed.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\cos_cubed.dir\cmake_clean.cmake
.PHONY : CMakeFiles/cos_cubed.dir/clean

CMakeFiles/cos_cubed.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\personal\raytracing_Cpp E:\personal\raytracing_Cpp E:\personal\raytracing_Cpp\build E:\personal\raytracing_Cpp\build E:\personal\raytracing_Cpp\build\CMakeFiles\cos_cubed.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/cos_cubed.dir/depend

