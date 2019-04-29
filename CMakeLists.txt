cmake_minimum_required (VERSION 3.10)

project (sample_game)

set(HALLEY_PROJECT_EMBED 1)
set(HALLEY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/halley)
set(HOTRELOAD 0 CACHE BOOL "Sets whether to hot-reload this project")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${HALLEY_PATH}/cmake/")

include(HalleyProject)

set (SOURCES
    src/main.cpp
    src/MyStage.cpp
    src/types/GridAnimationPlayer.cpp
)

set (HEADERS
    src/MyStage.hpp
)

set (GENS
	#    gen_src/trapped.yaml  # ????
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src) 


halleyProject(sample_game "${SOURCES}" "${HEADERS}" "${GENS}" ${CMAKE_CURRENT_SOURCE_DIR}/bin)
