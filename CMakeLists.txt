message("=====================================================")
message("=== Start CMakeLists.txt on Data Structures in Cpp ==")
message("=====================================================")

# cmake version
cmake_minimum_required(VERSION 3.5)

# set project name
set(PROJECT_NAME "DataStructuresInCpp")
project(${PROJECT_NAME})
enable_language(CXX)

# Add definitions. Compiler flags? Not yet sure...
add_definitions(-Wall -Werror -ansi -Wno-deprecated -pthread)

# Specify to use C++11
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set to Debug. For prints? Not yet sure, how logs differ...
set(CMAKE_BUILD_TYPE Debug)

# creating cmake options
option(BUILD_UT "This flag builds UT" OFF)
option(BUILD_SRC "This flag builds src" OFF)

# Set other variables
set(EXTERNAL_DIR ${PROJECT_SOURCE_DIR}/externals)

# Add googletest. This will call CMakeLists.txt of googletest and it will compile the libraries along with your project
add_subdirectory(${EXTERNAL_DIR}/googletest)

# googltest includes for test files and for Calculator class hpp
# include_directories(${gtest_SOURCE_DIR}/include ${gmock_SOURCE_DIR}/include) # gtest_SOURCE_DIR was defined when googletest was compiled

# for src
if(BUILD_SRC)
	add_subdirectory(src)
endif()

### for test
# if option set to true, compile UT
if(BUILD_UT)
	add_subdirectory(test)
endif()
### 
