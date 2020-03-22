cmake_minimum_required(VERSION 3.2)
project(sdpa-test CXX Fortran)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDPA REQUIRED)
include_directories(${SDPA_INCLUDE_DIRS}
   ${MUMPS_INCLUDE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -funroll-all-loops")
set(CMAKE_Fortran_FLAGS "-g -O2 -Wall -fPIC -funroll-all-loops")

add_executable(example1 ${CMAKE_SOURCE_DIR}/src/example1.cpp)
target_link_libraries(example1 ${SDPA_LIBRARIES})

add_executable(example2 ${CMAKE_SOURCE_DIR}/src/example2.cpp)
target_link_libraries(example2 ${SDPA_LIBRARIES})

add_executable(example3 ${CMAKE_SOURCE_DIR}/src/example3.cpp)
target_link_libraries(example3 ${SDPA_LIBRARIES})

add_executable(example4 ${CMAKE_SOURCE_DIR}/src/example4.cpp)
target_link_libraries(example4 ${SDPA_LIBRARIES})

add_executable(example5 ${CMAKE_SOURCE_DIR}/src/example5.cpp)
target_link_libraries(example5 ${SDPA_LIBRARIES})

add_executable(example6 ${CMAKE_SOURCE_DIR}/src/example6.cpp)
target_link_libraries(example6 ${SDPA_LIBRARIES})

add_executable(example1_wikipedia ${CMAKE_SOURCE_DIR}/src/example1_wikipedia.cpp)
target_link_libraries(example1_wikipedia ${SDPA_LIBRARIES})
