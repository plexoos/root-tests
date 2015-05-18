cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(root-test-io)

option(FORCE_32BIT "compile 32-bit application" ON)

if(FORCE_32BIT)
	set_property(GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS OFF)
	set(CMAKE_CXX_FLAGS "-m32 -std=c++0x")
endif()



# Add to path in order to pick up the FindXXX.cmake files included in this project
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")

# This project depends on ROOT
find_package(ROOT)

if(NOT ROOT_FOUND)
   message(FATAL_ERROR "Fatal error: ROOT package not found")
endif()

include_directories(
	${ROOT_INCLUDE_DIR}
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

target_link_libraries(write-tree root-test-io ${ROOT_LIBRARIES})
target_link_libraries(read-tree root-test-io ${ROOT_LIBRARIES})

if(FORCE_32BIT)
	set_target_properties(root-test-io PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
	set_target_properties(write-tree PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
	set_target_properties(read-tree PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif()
