cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main main.cpp
        Mappa.cpp
        pg.cpp
        findpath.cpp)
add_executable(tests
       tests/test_main.cpp
)

add_subdirectory(${CMAKE_SOURCE_DIR}/googletest-main)
include_directories(${CMAKE_SOURCE_DIR}/googletest-main/googletest/include)
include_directories(${CMAKE_SOURCE_DIR})

target_link_libraries(tests
        gtest
        gtest_main
)
target_link_libraries(main PRIVATE SFML::Graphics)

enable_testing()
add_test(NAME GameTest COMMAND tests)

target_compile_features(main PRIVATE cxx_std_17)

#librerie e executable usate e librerie per i test sono separate
