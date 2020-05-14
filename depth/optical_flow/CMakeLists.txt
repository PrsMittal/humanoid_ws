cmake_minimum_required(VERSION 2.8)
if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)
project( depthmono VERSION 1.0 )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
add_library(depthmono SHARED
	src/shrink.cpp
	src/expand.cpp
	src/optical_flow.cpp	
)
#set_target_properties(depthmono PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(depthmono PROPERTIES PUBLIC_HEADER optical_flow.hpp)
target_include_directories(depthmono PRIVATE ${CMAKE_BINARY_DIR}/../include)
target_link_libraries(depthmono ${OpenCV_LIBS})
set_target_properties(depthmono PROPERTIES LINK_FLAGS "-lgomp -fopenmp -pthread") 

add_executable(test1 test.cpp)
#find_library(Depth_LIB depthmono)
message("${Depth_LIB}")
target_link_libraries(test1 depthmono ${OpenCV_LIBS})
