cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project( RoguelikeKD )

set(SDLENGINE_DIR ${CMAKE_SOURCE_DIR}/SDLEngine/)
set(SDL_LIBRARIES_DIR ${SDLENGINE_DIR}/Linux/libs/SDL2/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -w -g")

include_directories(${SDLENGINE_DIR}/Linux/include/SDL2)
include_directories(${SDLENGINE_DIR}/Classes/include)
include_directories(${CMAKE_SOURCE_DIR}/SimpleRoguelike/Game)

link_directories(${SDL_LIBRARIES_DIR})

file( GLOB HEADERS
      "${CMAKE_SOURCE_DIR}/SimpleRoguelike/Game/*/*.h"
      "${CMAKE_SOURCE_DIR}/SimpleRoguelike/Game/*.h"
      "${SDLENGINE_DIR}/Classes/include/*/*.h"
      "${SDLENGINE_DIR}/Classes/include/*.h")

file( GLOB SOURCES
      "${CMAKE_SOURCE_DIR}/SimpleRoguelike/Game/*/*.cpp"
      "${CMAKE_SOURCE_DIR}/SimpleRoguelike/Game/*.cpp"
      "${CMAKE_SOURCE_DIR}/SimpleRoguelike/main.cpp"
      "${SDLENGINE_DIR}/Classes/src/*/*.cpp"
      "${SDLENGINE_DIR}/Classes/src/*.cpp")

find_library(SDL2	libSDL2.so		${SDL_LIBRARIES_DIR})
find_library(SDL2_IMAGE	libSDL2_image.so	${SDL_LIBRARIES_DIR})
find_library(SDL2_MIXER	libSDL2_mixer.so	${SDL_LIBRARIES_DIR})
find_library(SDL2_NET	libSDL2_net.so		${SDL_LIBRARIES_DIR})
find_library(SDL2_TTF	libSDL2_ttf.so	 	${SDL_LIBRARIES_DIR})

message("\nChecking libraries...")
message(STATUS "	      sdl2: " ${SDL2})
message(STATUS "      sdl_image: " ${SDL2_IMAGE})
message(STATUS "      sdl_mixer: " ${SDL2_MIXER})
message(STATUS "        sdl_net: " ${SDL2_NET})
message(STATUS "        sdl_ttf: " ${SDL2_TTF})
message("")

add_executable(run ${SOURCES} ${HEADERS})

target_link_libraries(run
		${SDL2}
		${SDL2_IMAGE}
		${SDL2_MIXER}
		${SDL2_NET}
		${SDL2_TTF})
	
file(COPY ${CMAKE_SOURCE_DIR}/Resources  DESTINATION ${CMAKE_SOURCE_DIR}/bin/)
