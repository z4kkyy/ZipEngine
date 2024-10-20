cmake_minimum_required(VERSION 3.10)
project(ZipEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_library(ZipEngine STATIC ${SOURCES})

add_executable(ZipEngineExample examples/main.cpp)
target_link_libraries(ZipEngineExample ZipEngine)

# テストの追加（後で実装）
# enable_testing()
# add_subdirectory(tests)
