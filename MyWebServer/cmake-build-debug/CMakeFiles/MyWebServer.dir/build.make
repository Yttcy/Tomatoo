# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /home/yttcy/WorkingFiles/CLion/clion-2021.1.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/yttcy/WorkingFiles/CLion/clion-2021.1.2/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yttcy/WorkingFiles/C++/MyWebServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MyWebServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MyWebServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyWebServer.dir/flags.make

CMakeFiles/MyWebServer.dir/main.cpp.o: CMakeFiles/MyWebServer.dir/flags.make
CMakeFiles/MyWebServer.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyWebServer.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyWebServer.dir/main.cpp.o -c /home/yttcy/WorkingFiles/C++/MyWebServer/main.cpp

CMakeFiles/MyWebServer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyWebServer.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yttcy/WorkingFiles/C++/MyWebServer/main.cpp > CMakeFiles/MyWebServer.dir/main.cpp.i

CMakeFiles/MyWebServer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyWebServer.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yttcy/WorkingFiles/C++/MyWebServer/main.cpp -o CMakeFiles/MyWebServer.dir/main.cpp.s

CMakeFiles/MyWebServer.dir/ServerCppfiles/MyServer.cpp.o: CMakeFiles/MyWebServer.dir/flags.make
CMakeFiles/MyWebServer.dir/ServerCppfiles/MyServer.cpp.o: ../ServerCppfiles/MyServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MyWebServer.dir/ServerCppfiles/MyServer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyWebServer.dir/ServerCppfiles/MyServer.cpp.o -c /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/MyServer.cpp

CMakeFiles/MyWebServer.dir/ServerCppfiles/MyServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyWebServer.dir/ServerCppfiles/MyServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/MyServer.cpp > CMakeFiles/MyWebServer.dir/ServerCppfiles/MyServer.cpp.i

CMakeFiles/MyWebServer.dir/ServerCppfiles/MyServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyWebServer.dir/ServerCppfiles/MyServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/MyServer.cpp -o CMakeFiles/MyWebServer.dir/ServerCppfiles/MyServer.cpp.s

CMakeFiles/MyWebServer.dir/ServerCppfiles/Reactor.cpp.o: CMakeFiles/MyWebServer.dir/flags.make
CMakeFiles/MyWebServer.dir/ServerCppfiles/Reactor.cpp.o: ../ServerCppfiles/Reactor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MyWebServer.dir/ServerCppfiles/Reactor.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyWebServer.dir/ServerCppfiles/Reactor.cpp.o -c /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/Reactor.cpp

CMakeFiles/MyWebServer.dir/ServerCppfiles/Reactor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyWebServer.dir/ServerCppfiles/Reactor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/Reactor.cpp > CMakeFiles/MyWebServer.dir/ServerCppfiles/Reactor.cpp.i

CMakeFiles/MyWebServer.dir/ServerCppfiles/Reactor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyWebServer.dir/ServerCppfiles/Reactor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/Reactor.cpp -o CMakeFiles/MyWebServer.dir/ServerCppfiles/Reactor.cpp.s

CMakeFiles/MyWebServer.dir/ServerCppfiles/EventHander.cpp.o: CMakeFiles/MyWebServer.dir/flags.make
CMakeFiles/MyWebServer.dir/ServerCppfiles/EventHander.cpp.o: ../ServerCppfiles/EventHander.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MyWebServer.dir/ServerCppfiles/EventHander.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyWebServer.dir/ServerCppfiles/EventHander.cpp.o -c /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/EventHander.cpp

CMakeFiles/MyWebServer.dir/ServerCppfiles/EventHander.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyWebServer.dir/ServerCppfiles/EventHander.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/EventHander.cpp > CMakeFiles/MyWebServer.dir/ServerCppfiles/EventHander.cpp.i

CMakeFiles/MyWebServer.dir/ServerCppfiles/EventHander.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyWebServer.dir/ServerCppfiles/EventHander.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/EventHander.cpp -o CMakeFiles/MyWebServer.dir/ServerCppfiles/EventHander.cpp.s

CMakeFiles/MyWebServer.dir/ServerCppfiles/Epoll.cpp.o: CMakeFiles/MyWebServer.dir/flags.make
CMakeFiles/MyWebServer.dir/ServerCppfiles/Epoll.cpp.o: ../ServerCppfiles/Epoll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MyWebServer.dir/ServerCppfiles/Epoll.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyWebServer.dir/ServerCppfiles/Epoll.cpp.o -c /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/Epoll.cpp

CMakeFiles/MyWebServer.dir/ServerCppfiles/Epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyWebServer.dir/ServerCppfiles/Epoll.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/Epoll.cpp > CMakeFiles/MyWebServer.dir/ServerCppfiles/Epoll.cpp.i

CMakeFiles/MyWebServer.dir/ServerCppfiles/Epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyWebServer.dir/ServerCppfiles/Epoll.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/Epoll.cpp -o CMakeFiles/MyWebServer.dir/ServerCppfiles/Epoll.cpp.s

CMakeFiles/MyWebServer.dir/ServerCppfiles/Http.cpp.o: CMakeFiles/MyWebServer.dir/flags.make
CMakeFiles/MyWebServer.dir/ServerCppfiles/Http.cpp.o: ../ServerCppfiles/Http.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/MyWebServer.dir/ServerCppfiles/Http.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyWebServer.dir/ServerCppfiles/Http.cpp.o -c /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/Http.cpp

CMakeFiles/MyWebServer.dir/ServerCppfiles/Http.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyWebServer.dir/ServerCppfiles/Http.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/Http.cpp > CMakeFiles/MyWebServer.dir/ServerCppfiles/Http.cpp.i

CMakeFiles/MyWebServer.dir/ServerCppfiles/Http.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyWebServer.dir/ServerCppfiles/Http.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/Http.cpp -o CMakeFiles/MyWebServer.dir/ServerCppfiles/Http.cpp.s

CMakeFiles/MyWebServer.dir/ServerCppfiles/Time.cpp.o: CMakeFiles/MyWebServer.dir/flags.make
CMakeFiles/MyWebServer.dir/ServerCppfiles/Time.cpp.o: ../ServerCppfiles/Time.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/MyWebServer.dir/ServerCppfiles/Time.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyWebServer.dir/ServerCppfiles/Time.cpp.o -c /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/Time.cpp

CMakeFiles/MyWebServer.dir/ServerCppfiles/Time.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyWebServer.dir/ServerCppfiles/Time.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/Time.cpp > CMakeFiles/MyWebServer.dir/ServerCppfiles/Time.cpp.i

CMakeFiles/MyWebServer.dir/ServerCppfiles/Time.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyWebServer.dir/ServerCppfiles/Time.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yttcy/WorkingFiles/C++/MyWebServer/ServerCppfiles/Time.cpp -o CMakeFiles/MyWebServer.dir/ServerCppfiles/Time.cpp.s

CMakeFiles/MyWebServer.dir/ThreadCppfiles/Thread.cpp.o: CMakeFiles/MyWebServer.dir/flags.make
CMakeFiles/MyWebServer.dir/ThreadCppfiles/Thread.cpp.o: ../ThreadCppfiles/Thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/MyWebServer.dir/ThreadCppfiles/Thread.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyWebServer.dir/ThreadCppfiles/Thread.cpp.o -c /home/yttcy/WorkingFiles/C++/MyWebServer/ThreadCppfiles/Thread.cpp

CMakeFiles/MyWebServer.dir/ThreadCppfiles/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyWebServer.dir/ThreadCppfiles/Thread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yttcy/WorkingFiles/C++/MyWebServer/ThreadCppfiles/Thread.cpp > CMakeFiles/MyWebServer.dir/ThreadCppfiles/Thread.cpp.i

CMakeFiles/MyWebServer.dir/ThreadCppfiles/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyWebServer.dir/ThreadCppfiles/Thread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yttcy/WorkingFiles/C++/MyWebServer/ThreadCppfiles/Thread.cpp -o CMakeFiles/MyWebServer.dir/ThreadCppfiles/Thread.cpp.s

CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThread.cpp.o: CMakeFiles/MyWebServer.dir/flags.make
CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThread.cpp.o: ../ThreadCppfiles/ReactorThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThread.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThread.cpp.o -c /home/yttcy/WorkingFiles/C++/MyWebServer/ThreadCppfiles/ReactorThread.cpp

CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yttcy/WorkingFiles/C++/MyWebServer/ThreadCppfiles/ReactorThread.cpp > CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThread.cpp.i

CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yttcy/WorkingFiles/C++/MyWebServer/ThreadCppfiles/ReactorThread.cpp -o CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThread.cpp.s

CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThreadPool.cpp.o: CMakeFiles/MyWebServer.dir/flags.make
CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThreadPool.cpp.o: ../ThreadCppfiles/ReactorThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThreadPool.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThreadPool.cpp.o -c /home/yttcy/WorkingFiles/C++/MyWebServer/ThreadCppfiles/ReactorThreadPool.cpp

CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThreadPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yttcy/WorkingFiles/C++/MyWebServer/ThreadCppfiles/ReactorThreadPool.cpp > CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThreadPool.cpp.i

CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThreadPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yttcy/WorkingFiles/C++/MyWebServer/ThreadCppfiles/ReactorThreadPool.cpp -o CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThreadPool.cpp.s

CMakeFiles/MyWebServer.dir/util/Util.cpp.o: CMakeFiles/MyWebServer.dir/flags.make
CMakeFiles/MyWebServer.dir/util/Util.cpp.o: ../util/Util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/MyWebServer.dir/util/Util.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyWebServer.dir/util/Util.cpp.o -c /home/yttcy/WorkingFiles/C++/MyWebServer/util/Util.cpp

CMakeFiles/MyWebServer.dir/util/Util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyWebServer.dir/util/Util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yttcy/WorkingFiles/C++/MyWebServer/util/Util.cpp > CMakeFiles/MyWebServer.dir/util/Util.cpp.i

CMakeFiles/MyWebServer.dir/util/Util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyWebServer.dir/util/Util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yttcy/WorkingFiles/C++/MyWebServer/util/Util.cpp -o CMakeFiles/MyWebServer.dir/util/Util.cpp.s

CMakeFiles/MyWebServer.dir/test/test.cpp.o: CMakeFiles/MyWebServer.dir/flags.make
CMakeFiles/MyWebServer.dir/test/test.cpp.o: ../test/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/MyWebServer.dir/test/test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MyWebServer.dir/test/test.cpp.o -c /home/yttcy/WorkingFiles/C++/MyWebServer/test/test.cpp

CMakeFiles/MyWebServer.dir/test/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyWebServer.dir/test/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yttcy/WorkingFiles/C++/MyWebServer/test/test.cpp > CMakeFiles/MyWebServer.dir/test/test.cpp.i

CMakeFiles/MyWebServer.dir/test/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyWebServer.dir/test/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yttcy/WorkingFiles/C++/MyWebServer/test/test.cpp -o CMakeFiles/MyWebServer.dir/test/test.cpp.s

# Object files for target MyWebServer
MyWebServer_OBJECTS = \
"CMakeFiles/MyWebServer.dir/main.cpp.o" \
"CMakeFiles/MyWebServer.dir/ServerCppfiles/MyServer.cpp.o" \
"CMakeFiles/MyWebServer.dir/ServerCppfiles/Reactor.cpp.o" \
"CMakeFiles/MyWebServer.dir/ServerCppfiles/EventHander.cpp.o" \
"CMakeFiles/MyWebServer.dir/ServerCppfiles/Epoll.cpp.o" \
"CMakeFiles/MyWebServer.dir/ServerCppfiles/Http.cpp.o" \
"CMakeFiles/MyWebServer.dir/ServerCppfiles/Time.cpp.o" \
"CMakeFiles/MyWebServer.dir/ThreadCppfiles/Thread.cpp.o" \
"CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThread.cpp.o" \
"CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThreadPool.cpp.o" \
"CMakeFiles/MyWebServer.dir/util/Util.cpp.o" \
"CMakeFiles/MyWebServer.dir/test/test.cpp.o"

# External object files for target MyWebServer
MyWebServer_EXTERNAL_OBJECTS =

MyWebServer: CMakeFiles/MyWebServer.dir/main.cpp.o
MyWebServer: CMakeFiles/MyWebServer.dir/ServerCppfiles/MyServer.cpp.o
MyWebServer: CMakeFiles/MyWebServer.dir/ServerCppfiles/Reactor.cpp.o
MyWebServer: CMakeFiles/MyWebServer.dir/ServerCppfiles/EventHander.cpp.o
MyWebServer: CMakeFiles/MyWebServer.dir/ServerCppfiles/Epoll.cpp.o
MyWebServer: CMakeFiles/MyWebServer.dir/ServerCppfiles/Http.cpp.o
MyWebServer: CMakeFiles/MyWebServer.dir/ServerCppfiles/Time.cpp.o
MyWebServer: CMakeFiles/MyWebServer.dir/ThreadCppfiles/Thread.cpp.o
MyWebServer: CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThread.cpp.o
MyWebServer: CMakeFiles/MyWebServer.dir/ThreadCppfiles/ReactorThreadPool.cpp.o
MyWebServer: CMakeFiles/MyWebServer.dir/util/Util.cpp.o
MyWebServer: CMakeFiles/MyWebServer.dir/test/test.cpp.o
MyWebServer: CMakeFiles/MyWebServer.dir/build.make
MyWebServer: CMakeFiles/MyWebServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable MyWebServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyWebServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyWebServer.dir/build: MyWebServer

.PHONY : CMakeFiles/MyWebServer.dir/build

CMakeFiles/MyWebServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyWebServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyWebServer.dir/clean

CMakeFiles/MyWebServer.dir/depend:
	cd /home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yttcy/WorkingFiles/C++/MyWebServer /home/yttcy/WorkingFiles/C++/MyWebServer /home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug /home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug /home/yttcy/WorkingFiles/C++/MyWebServer/cmake-build-debug/CMakeFiles/MyWebServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyWebServer.dir/depend

