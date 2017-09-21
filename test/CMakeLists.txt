message("=====================================================")
message("===== Start CMakeLists.txt on test/ =================")
message("=====================================================")

find_package(Threads REQUIRED)

enable_testing()

include_directories("${PROJECT_SOURCE_DIR}/test/" "${PROJECT_SOURCE_DIR}/src/" "${PROJECT_SOURCE_DIR}/src/includes")

set(DSA_TEST "DSAInCppTest")
#file(GLOB DSA_SRC_FILES "${PROJECT_SOURCE_DIR}/src/codeWars/kyu8/*.cpp" "${PROJECT_SOURCE_DIR}/src/codeWars/kyu7/*.cpp")
file(GLOB_RECURSE DSA_SRC_FILES "${PROJECT_SOURCE_DIR}/src/implementations" "*.cpp")
file(GLOB_RECURSE DSA_TEST_SRC_FILES "${PROJECT_SOURCE_DIR}/test/" "*.cpp")
add_executable(${DSA_TEST} main.cpp ${DSA_SRC_FILES} ${DSA_TEST_SRC_FILES})
add_dependencies(${DSA_TEST} gtest gtest_main gmock gmock_main)
target_link_libraries(${DSA_TEST} gtest gtest_main gmock gmock_main ${CMAKE_THREAD_LIBS_INIT})
message("${DSA_TEST_SRC_FILES}")