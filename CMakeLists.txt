cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project( RoguelikeKD )

set(SDLENGINE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SDLEngine/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -w -g")

set(ROGUELIKE_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SimpleRoguelike/Game)

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
endif()

add_subdirectory(SDLEngine)

set(ROGUELIKE_HEADERS
    ${ROGUELIKE_SOURCES_DIR}/Entities/Creature.h
    ${ROGUELIKE_SOURCES_DIR}/Entities/Fighter.h
    ${ROGUELIKE_SOURCES_DIR}/Entities/Item.h
    ${ROGUELIKE_SOURCES_DIR}/Entities/Ranger.h
    ${ROGUELIKE_SOURCES_DIR}/Entities/Stats.h
    ${ROGUELIKE_SOURCES_DIR}/Entities/Warrior.h

    ${ROGUELIKE_SOURCES_DIR}/GameMap/Field.h
    ${ROGUELIKE_SOURCES_DIR}/GameMap/GameField.h
    ${ROGUELIKE_SOURCES_DIR}/GameMap/Map.h
    ${ROGUELIKE_SOURCES_DIR}/GameMap/GameMap.h

    ${ROGUELIKE_SOURCES_DIR}/UI/CurrentStats.h

    ${ROGUELIKE_SOURCES_DIR}/GameScene.h
)

set(ROUGUELIKE_SOURCES
    ${ROGUELIKE_SOURCES_DIR}/Entities/Creature.cpp
    ${ROGUELIKE_SOURCES_DIR}/Entities/Fighter.cpp
    ${ROGUELIKE_SOURCES_DIR}/Entities/Item.cpp
    ${ROGUELIKE_SOURCES_DIR}/Entities/Ranger.cpp
    ${ROGUELIKE_SOURCES_DIR}/Entities/Warrior.cpp

    ${ROGUELIKE_SOURCES_DIR}/GameMap/GameField.cpp
    ${ROGUELIKE_SOURCES_DIR}/GameMap/GameMap.cpp

    ${ROGUELIKE_SOURCES_DIR}/UI/CurrentStats.cpp

    ${ROGUELIKE_SOURCES_DIR}/GameScene.cpp

    ${ROGUELIKE_SOURCES_DIR}/../main.cpp
)

if(WIN32)
	add_executable(${PROJECT_NAME} WIN32 ${ROUGUELIKE_SOURCES} ${ROGUELIKE_HEADERS})
else()
	add_executable(${PROJECT_NAME} ${ROUGUELIKE_SOURCES} ${ROGUELIKE_HEADERS})
endif(WIN32)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${SDLENGINE_DIR}/Source/public
    PUBLIC ${SDL2_INCLUDE_DIR_P}
    PUBLIC ${ROGUELIKE_SOURCES_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC KDEngine
		PUBLIC ${SDL2_LIB}
		PUBLIC ${SDL2_IMAGE_LIB}
		PUBLIC ${SDL2_MIXER_LIB}
		PUBLIC ${SDL2_NET_LIB}
		PUBLIC ${SDL2_TTF_LIB}
)

add_dependencies(${PROJECT_NAME} KDEngine)

# there is the difference in resource path because in visual studio projects actual runtime output directory
# not ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} but ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/{Debug/Release}
# so this if branches are created to averride this behavior
message(WARNING "Get rid of this Resources hack!")
# as a possible solution we may define a macro with path to Resources/ directory in cmake and pass it to the executable

if(WIN32)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
else()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/..)
endif(WIN32)

if(WIN32)
	file(COPY ${SDL2_LIBRARIES_DIR_P}/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug)
endif(WIN32)
