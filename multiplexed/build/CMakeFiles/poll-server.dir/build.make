# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chika/Documents/comp4981/04-multiplexed/multiplexed

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chika/Documents/comp4981/04-multiplexed/multiplexed/build

# Include any dependencies generated for this target.
include CMakeFiles/poll-server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/poll-server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/poll-server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/poll-server.dir/flags.make

CMakeFiles/poll-server.dir/src/main-poll-server.c.o: CMakeFiles/poll-server.dir/flags.make
CMakeFiles/poll-server.dir/src/main-poll-server.c.o: ../src/main-poll-server.c
CMakeFiles/poll-server.dir/src/main-poll-server.c.o: CMakeFiles/poll-server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chika/Documents/comp4981/04-multiplexed/multiplexed/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/poll-server.dir/src/main-poll-server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/poll-server.dir/src/main-poll-server.c.o -MF CMakeFiles/poll-server.dir/src/main-poll-server.c.o.d -o CMakeFiles/poll-server.dir/src/main-poll-server.c.o -c /home/chika/Documents/comp4981/04-multiplexed/multiplexed/src/main-poll-server.c

CMakeFiles/poll-server.dir/src/main-poll-server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/poll-server.dir/src/main-poll-server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chika/Documents/comp4981/04-multiplexed/multiplexed/src/main-poll-server.c > CMakeFiles/poll-server.dir/src/main-poll-server.c.i

CMakeFiles/poll-server.dir/src/main-poll-server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/poll-server.dir/src/main-poll-server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chika/Documents/comp4981/04-multiplexed/multiplexed/src/main-poll-server.c -o CMakeFiles/poll-server.dir/src/main-poll-server.c.s

# Object files for target poll-server
poll__server_OBJECTS = \
"CMakeFiles/poll-server.dir/src/main-poll-server.c.o"

# External object files for target poll-server
poll__server_EXTERNAL_OBJECTS =

poll-server: CMakeFiles/poll-server.dir/src/main-poll-server.c.o
poll-server: CMakeFiles/poll-server.dir/build.make
poll-server: /usr/local/lib/libdc_error.so
poll-server: /usr/local/lib/libdc_env.so
poll-server: /usr/local/lib/libdc_c.so
poll-server: /usr/local/lib/libdc_posix.so
poll-server: CMakeFiles/poll-server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chika/Documents/comp4981/04-multiplexed/multiplexed/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable poll-server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/poll-server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/poll-server.dir/build: poll-server
.PHONY : CMakeFiles/poll-server.dir/build

CMakeFiles/poll-server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/poll-server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/poll-server.dir/clean

CMakeFiles/poll-server.dir/depend:
	cd /home/chika/Documents/comp4981/04-multiplexed/multiplexed/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chika/Documents/comp4981/04-multiplexed/multiplexed /home/chika/Documents/comp4981/04-multiplexed/multiplexed /home/chika/Documents/comp4981/04-multiplexed/multiplexed/build /home/chika/Documents/comp4981/04-multiplexed/multiplexed/build /home/chika/Documents/comp4981/04-multiplexed/multiplexed/build/CMakeFiles/poll-server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/poll-server.dir/depend
