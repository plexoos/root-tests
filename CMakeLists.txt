cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(root-test-io)

# Add to path in order to pick up the FindXXX.cmake files included in this project
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

# This project depends on ROOT
find_package(ROOT)

if(NOT ROOT_FOUND)
   message(FATAL_ERROR "Fatal error: ROOT package not found")
endif()

include_directories(
	${ROOT_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
)

link_directories(
	${ROOT_LIBRARY_DIR}
)

root_generate_dictionary(
	root-test-io_Cint
	MyEvent.h
	MyBaseObj.h
	MyDerivObj.h
	LINKDEF LinkDef.h
)

add_library(
	root-test-io
	SHARED
	root-test-io_Cint.cxx
)


add_executable(write-tree write-tree.cc)
add_executable(read-tree read-tree.cc)

set_property(TARGET root-test-io PROPERTY CXX_STANDARD 11)
target_link_libraries(root-test-io ${ROOT_LIBRARIES})
set_property(TARGET write-tree PROPERTY CXX_STANDARD 11)
target_link_libraries(write-tree root-test-io ${ROOT_LIBRARIES})
set_property(TARGET read-tree PROPERTY CXX_STANDARD 11)
target_link_libraries(read-tree root-test-io ${ROOT_LIBRARIES})

string(REGEX MATCH "(^|[\t ]+)-m([\t ]*)(32|64)([\t ]+|$)" ROOT_CXX_FLAGS_M ${ROOT_CXX_FLAGS})

if (ROOT_CXX_FLAGS_M)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m${CMAKE_MATCH_3}")
	message(STATUS "Found -m${CMAKE_MATCH_3} option in $ROOT_CXX_FLAGS (root-config). Will add it to $CMAKE_CXX_FLAGS")

	if (CMAKE_MATCH_3 EQUAL 32)
		set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS OFF)
	endif()
endif()
