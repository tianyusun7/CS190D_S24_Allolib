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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.29.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.29.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/build/formant_synth/Release

# Utility rule file for formant_synth_run.

# Include any custom commands dependencies for this target.
include CMakeFiles/formant_synth_run.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/formant_synth_run.dir/progress.make

CMakeFiles/formant_synth_run: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth
	cd /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin && ./formant_synth

formant_synth_run: CMakeFiles/formant_synth_run
formant_synth_run: CMakeFiles/formant_synth_run.dir/build.make
.PHONY : formant_synth_run

# Rule to build all files generated by this target.
CMakeFiles/formant_synth_run.dir/build: formant_synth_run
.PHONY : CMakeFiles/formant_synth_run.dir/build

CMakeFiles/formant_synth_run.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/formant_synth_run.dir/cmake_clean.cmake
.PHONY : CMakeFiles/formant_synth_run.dir/clean

CMakeFiles/formant_synth_run.dir/depend:
	cd /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/build/formant_synth/Release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/build/formant_synth/Release /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/build/formant_synth/Release /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/build/formant_synth/Release/CMakeFiles/formant_synth_run.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/formant_synth_run.dir/depend
