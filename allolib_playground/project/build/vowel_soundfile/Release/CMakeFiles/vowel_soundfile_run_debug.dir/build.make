# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.29.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.29.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/build/vowel_soundfile/Release

# Utility rule file for vowel_soundfile_run_debug.

# Include any custom commands dependencies for this target.
include CMakeFiles/vowel_soundfile_run_debug.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/vowel_soundfile_run_debug.dir/progress.make

CMakeFiles/vowel_soundfile_run_debug: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/vowel_soundfile
	cd /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin && lldb -o\ run ./vowel_soundfiled

vowel_soundfile_run_debug: CMakeFiles/vowel_soundfile_run_debug
vowel_soundfile_run_debug: CMakeFiles/vowel_soundfile_run_debug.dir/build.make
.PHONY : vowel_soundfile_run_debug

# Rule to build all files generated by this target.
CMakeFiles/vowel_soundfile_run_debug.dir/build: vowel_soundfile_run_debug
.PHONY : CMakeFiles/vowel_soundfile_run_debug.dir/build

CMakeFiles/vowel_soundfile_run_debug.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vowel_soundfile_run_debug.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vowel_soundfile_run_debug.dir/clean

CMakeFiles/vowel_soundfile_run_debug.dir/depend:
	cd /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/build/vowel_soundfile/Release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/build/vowel_soundfile/Release /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/build/vowel_soundfile/Release /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/build/vowel_soundfile/Release/CMakeFiles/vowel_soundfile_run_debug.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/vowel_soundfile_run_debug.dir/depend

