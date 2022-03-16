cmake_minimum_required(VERSION 3.12)
project(nokia VERSION 0.1.0)

include(CTest)
enable_testing()

#set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/SFML-2.5.1-mingw-7.3.0-posix-seh/lib/cmake/SFML)


add_executable(nokia main.cpp main.h algorithms/Fcfs.cpp algorithms/Fcfs.h algorithms/PriorityNP.cpp algorithms/PriorityNP.h algorithms/Process.cpp algorithms/Process.h algorithms/Roundrobin.cpp algorithms/Roundrobin.h)


find_package(SFML COMPONENTS graphics audio REQUIRED)
target_link_libraries(nokia sfml-graphics sfml-window sfml-system)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
