# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required(VERSION 3.10)
project(bomberman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
include_directories(./include)

if (APPLE)
	find_package(OPENGL)
	find_library(COCOA_LIBRARY Cocoa)
	find_library(IOKIT IOKit)
        find_library(FOUNDATION Foundation)
        find_library(CARBON Carbon)
        find_library(APPKIT AppKit)
endif (APPLE)

if (UNIX)
        set (CMAKE_SHARED_LINKER_FLAGS "-lGLU, -lGL")
        INCLUDE_DIRECTORIES(
                "/usr/include/irrlicht"
		"/usr/local/include/irrlicht"
        )
        include_directories(inc)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
	find_package(Irrlicht)
        link_libraries(Irrlicht)
	link_directories(Irrlicht) #link vers le .a
	add_executable(bomberman
        ./src/Core/Core.cpp
        ./src/Mesh/Mesh.cpp
        ./src/Bomb/Bomb.cpp
        ./assets/find_asset.cpp
 ./src/main.cpp)

 target_link_libraries(bomberman ${irrlicht})
endif()

if (APPLE)
        target_link_libraries(bomberman ${OPENGL_LIBRARY} ${COCOA_LIBRARY} ${IOKIT} ${FOUNDATION} ${CARBON} ${APPKIT} Irrlicht)
endif (APPLE)

if (WIN32)
add_library(Irrlicht STATIC IMPORTED)
set_property(TARGET Irrlicht PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Irrlicht.lib)
add_executable(bomberman
./src/Core/Core.cpp
./src/Entity/Entity.cpp)
target_link_libraries(bomberman Irrlicht)
endif()