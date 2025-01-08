cmake_minimum_required(VERSION 3.10)
project(wfc)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED sfml-window sfml-graphics sfml-audio sfml-network)

include_directories(${SFML_INCLUDE_DIRS})

add_executable(wfc src/main.cc)

target_link_libraries(wfc ${SFML_LIBRARIES})
