cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project( RoguelikeKD )

set(SDLENGINE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SDLEngine/)
#set(SDL_LIBRARIES_DIR ${SDLENGINE_DIR}/Linux/libs/SDL2/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -w -g")

add_subdirectory(SDLEngine)

set(ROGUELIKE_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SimpleRoguelike/Game)

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

add_executable(${PROJECT_NAME} ${ROUGUELIKE_SOURCES} ${ROGUELIKE_HEADERS})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${SDLENGINE_DIR}/Source/public
    PUBLIC ${SDL2_INCLUDE_DIR}
    PUBLIC ${ROGUELIKE_SOURCES_DIR}
)

message(" SDL2_INCLUDE_DIR: "${SDL2_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} 
                      ${CMAKE_CURRENT_BINARY_DIR}/SDLEngine/libKDEngine.so
                      ${SDL2_LIB_OUT}
                      ${SDL2_IMAGE_LIB_OUT}
                      ${SDL2_MIXER_LIB_OUT}
                      ${SDL2_NET_LIB_OUT}
                      ${SDL2_TTF_LIB_OUT})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources  DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
