cmake_minimum_required(VERSION 3.16)
project(QuantLibLite VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE QUANTLibLite_SOURCES
    src/marketdata/*.cpp
    src/curves/*.cpp
    src/instruments/*.cpp
    src/sensitivity/*.cpp
    src/models/*.cpp
    src/mathengines/*.cpp
)
add_library(QuantLibLite ${QUANTLibLite_SOURCES})

target_include_directories(QuantLibLite
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_testing()

file(GLOB TEST_SOURCES tests/*.cpp)
foreach(TEST_SRC ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SRC})
    target_link_libraries(${TEST_NAME} PRIVATE QuantLibLite)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

