# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\nopassword\CLionProjects\ECE_209_Program2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\nopassword\CLionProjects\ECE_209_Program2\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ECE_209_Program2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ECE_209_Program2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ECE_209_Program2.dir/flags.make

CMakeFiles/ECE_209_Program2.dir/futo.c.obj: CMakeFiles/ECE_209_Program2.dir/flags.make
CMakeFiles/ECE_209_Program2.dir/futo.c.obj: ../futo.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\nopassword\CLionProjects\ECE_209_Program2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ECE_209_Program2.dir/futo.c.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\ECE_209_Program2.dir\futo.c.obj   -c C:\Users\nopassword\CLionProjects\ECE_209_Program2\futo.c

CMakeFiles/ECE_209_Program2.dir/futo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ECE_209_Program2.dir/futo.c.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\nopassword\CLionProjects\ECE_209_Program2\futo.c > CMakeFiles\ECE_209_Program2.dir\futo.c.i

CMakeFiles/ECE_209_Program2.dir/futo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ECE_209_Program2.dir/futo.c.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\nopassword\CLionProjects\ECE_209_Program2\futo.c -o CMakeFiles\ECE_209_Program2.dir\futo.c.s

# Object files for target ECE_209_Program2
ECE_209_Program2_OBJECTS = \
"CMakeFiles/ECE_209_Program2.dir/futo.c.obj"

# External object files for target ECE_209_Program2
ECE_209_Program2_EXTERNAL_OBJECTS =

ECE_209_Program2.exe: CMakeFiles/ECE_209_Program2.dir/futo.c.obj
ECE_209_Program2.exe: CMakeFiles/ECE_209_Program2.dir/build.make
ECE_209_Program2.exe: CMakeFiles/ECE_209_Program2.dir/linklibs.rsp
ECE_209_Program2.exe: CMakeFiles/ECE_209_Program2.dir/objects1.rsp
ECE_209_Program2.exe: CMakeFiles/ECE_209_Program2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\nopassword\CLionProjects\ECE_209_Program2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ECE_209_Program2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ECE_209_Program2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ECE_209_Program2.dir/build: ECE_209_Program2.exe

.PHONY : CMakeFiles/ECE_209_Program2.dir/build

CMakeFiles/ECE_209_Program2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ECE_209_Program2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ECE_209_Program2.dir/clean

CMakeFiles/ECE_209_Program2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\nopassword\CLionProjects\ECE_209_Program2 C:\Users\nopassword\CLionProjects\ECE_209_Program2 C:\Users\nopassword\CLionProjects\ECE_209_Program2\cmake-build-debug C:\Users\nopassword\CLionProjects\ECE_209_Program2\cmake-build-debug C:\Users\nopassword\CLionProjects\ECE_209_Program2\cmake-build-debug\CMakeFiles\ECE_209_Program2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ECE_209_Program2.dir/depend

