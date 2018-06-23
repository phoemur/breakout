cmake_minimum_required(VERSION 3.9)

project(breakout DESCRIPTION "Remake of classic brakout game" LANGUAGES C CXX VERSION 0.1.0)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
pkg_search_module(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
include_directories(include/ ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS})

set(SOURCES
    src/exception.cpp
    src/main.cpp
    src/mainwindow.cpp
    src/music.cpp
    src/font.cpp
    src/texture.cpp
    src/rect.cpp
    src/ball.cpp
    src/locator.hpp
    src/observer.cpp
    src/subject.cpp
    src/collisionobserver.cpp
    src/audioobserver.cpp
    src/player.cpp
    src/gamestate.cpp
    src/intro.cpp
    src/level1.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
        -O3 -pipe -march=native
        $<$<CONFIG:Debug>:
        -O0 -Wall -Wextra -Weffc++ -pedantic-errors>>
    $<$<CXX_COMPILER_ID:MSVC>:
        $<$<CONFIG:Debug>:/Od /Wall /Zi>>
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2MIXER_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/breakout_assets/
    DESTINATION ${CMAKE_INSTALL_BINDIR}/breakout_assets/
)
