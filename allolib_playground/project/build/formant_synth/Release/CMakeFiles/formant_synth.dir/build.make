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

# Include any dependencies generated for this target.
include CMakeFiles/formant_synth.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/formant_synth.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/formant_synth.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/formant_synth.dir/flags.make

CMakeFiles/formant_synth.dir/project/formant_synth.cpp.o: CMakeFiles/formant_synth.dir/flags.make
CMakeFiles/formant_synth.dir/project/formant_synth.cpp.o: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/formant_synth.cpp
CMakeFiles/formant_synth.dir/project/formant_synth.cpp.o: CMakeFiles/formant_synth.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/build/formant_synth/Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/formant_synth.dir/project/formant_synth.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/formant_synth.dir/project/formant_synth.cpp.o -MF CMakeFiles/formant_synth.dir/project/formant_synth.cpp.o.d -o CMakeFiles/formant_synth.dir/project/formant_synth.cpp.o -c /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/formant_synth.cpp

CMakeFiles/formant_synth.dir/project/formant_synth.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/formant_synth.dir/project/formant_synth.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/formant_synth.cpp > CMakeFiles/formant_synth.dir/project/formant_synth.cpp.i

CMakeFiles/formant_synth.dir/project/formant_synth.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/formant_synth.dir/project/formant_synth.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/formant_synth.cpp -o CMakeFiles/formant_synth.dir/project/formant_synth.cpp.s

# Object files for target formant_synth
formant_synth_OBJECTS = \
"CMakeFiles/formant_synth.dir/project/formant_synth.cpp.o"

# External object files for target formant_synth
formant_synth_EXTERNAL_OBJECTS =

/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: CMakeFiles/formant_synth.dir/project/formant_synth.cpp.o
/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: CMakeFiles/formant_synth.dir/build.make
/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/allolib/build/Release/libal.a
/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/allolib/build/al_ext/openvr/libal_openvr.a
/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/allolib/build/al_ext/soundfile/libal_soundfile.a
/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/allolib/build/al_ext/statedistribution/libal_statedistribution.a
/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/allolib/build/Release/libal.a
/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/allolib/build/Release/external/rtaudio/librtaudio.a
/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/allolib/build/Release/external/Gamma/lib/libGamma.a
/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: /usr/local/lib/libsndfile.dylib
/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/allolib/build/Release/external/glfw/src/libglfw3.a
/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/allolib/build/Release/external/glad/libglad.a
/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/allolib/build/Release/external/rtmidi/librtmidi.a
/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/allolib/build/Release/external/libimgui.a
/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/allolib/build/Release/external/liboscpack.a
/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/allolib/build/Release/external/libserial.a
/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth: CMakeFiles/formant_synth.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/build/formant_synth/Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/formant_synth.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/formant_synth.dir/build: /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/bin/formant_synth
.PHONY : CMakeFiles/formant_synth.dir/build

CMakeFiles/formant_synth.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/formant_synth.dir/cmake_clean.cmake
.PHONY : CMakeFiles/formant_synth.dir/clean

CMakeFiles/formant_synth.dir/depend:
	cd /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/build/formant_synth/Release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/build/formant_synth/Release /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/build/formant_synth/Release /Users/suntianyu/Desktop/prime/senior/CS190D/allolib_playground/project/build/formant_synth/Release/CMakeFiles/formant_synth.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/formant_synth.dir/depend
