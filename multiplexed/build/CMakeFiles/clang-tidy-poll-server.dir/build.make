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

# Utility rule file for clang-tidy-poll-server.

# Include any custom commands dependencies for this target.
include CMakeFiles/clang-tidy-poll-server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/clang-tidy-poll-server.dir/progress.make

CMakeFiles/clang-tidy-poll-server:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/chika/Documents/comp4981/04-multiplexed/multiplexed/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running clang-tidy"
	/usr/bin/clang-tidy -p /home/chika/Documents/comp4981/04-multiplexed/multiplexed/build "-checks=*,-altera-id-dependent-backward-branch,-altera-struct-pack-align,-altera-unroll-loops,-android-cloexec-accept,-android-cloexec-creat,-android-cloexec-dup,-android-cloexec-open,-android-cloexec-pipe,-android-cloexec-socket,-bugprone-easily-swappable-parameters,-cert-dcl03-c,-clang-analyzer-deadcode.DeadStores,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling,-clang-analyzer-security.insecureAPI.strcpy,-clang-diagnostic-cast-align,-clang-diagnostic-format-nonliteral,-clang-diagnostic-incompatible-pointer-types-discards-qualifiers,-clang-diagnostic-unknown-warning-option,-clang-diagnostic-unused-but-set-variable,-clang-diagnostic-unused-function,-clang-diagnostic-unused-parameter,-clang-diagnostic-unused-variable,-clang-diagnostic-vla,-cppcoreguidelines-init-variables,-google-readability-todo,-hicpp-static-assert,-llvmlibc-restrict-system-libc-headers,-misc-static-assert,-misc-unused-parameters,-modernize-macro-to-enum,-readability-identifier-length" --quiet /home/chika/Documents/comp4981/04-multiplexed/multiplexed/src/main-poll-server.c

clang-tidy-poll-server: CMakeFiles/clang-tidy-poll-server
clang-tidy-poll-server: CMakeFiles/clang-tidy-poll-server.dir/build.make
.PHONY : clang-tidy-poll-server

# Rule to build all files generated by this target.
CMakeFiles/clang-tidy-poll-server.dir/build: clang-tidy-poll-server
.PHONY : CMakeFiles/clang-tidy-poll-server.dir/build

CMakeFiles/clang-tidy-poll-server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/clang-tidy-poll-server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/clang-tidy-poll-server.dir/clean

CMakeFiles/clang-tidy-poll-server.dir/depend:
	cd /home/chika/Documents/comp4981/04-multiplexed/multiplexed/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chika/Documents/comp4981/04-multiplexed/multiplexed /home/chika/Documents/comp4981/04-multiplexed/multiplexed /home/chika/Documents/comp4981/04-multiplexed/multiplexed/build /home/chika/Documents/comp4981/04-multiplexed/multiplexed/build /home/chika/Documents/comp4981/04-multiplexed/multiplexed/build/CMakeFiles/clang-tidy-poll-server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/clang-tidy-poll-server.dir/depend

