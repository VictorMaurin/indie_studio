# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required(VERSION 3.10)
project(bomberman)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
include_directories(./include)

if (UNIX)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
	find_package(Irrlicht)
	link_directories(Irrlicht) #link vers le .a
	add_executable(bomberman
 ./test.cpp)

 target_link_libraries(bomberman ${irrlicht})
endif()

if (WIN32)
add_library(Irrlicht STATIC IMPORTED)
set_property(TARGET Irrlicht PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Irrlicht.lib)
add_executable(bomberman
 ./test.cpp)
target_link_libraries(bomberman Irrlicht)
endif()