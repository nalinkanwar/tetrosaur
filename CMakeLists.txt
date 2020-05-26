cmake_minimum_required(VERSION 2.8)

project(Tetrosaur)
file(GLOB SRC . *.cpp)
add_executable(${PROJECT_NAME} ${SRC})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_ttf REQUIRED SDL2_ttf)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2_ttf_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_ttf_LIBRARIES})

# we don't want to copy if we're building in the source dir
if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)

    # list of files for which we add a copy rule
    set(data_SHADOW FreeSans.ttf)

    foreach(item IN LISTS data_SHADOW)
        message(STATUS ${item})
        add_custom_command(
            OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
            COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
            DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}"
        )
    endforeach()
endif()

# files are only copied if a target depends on them
add_custom_target(data-target ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/FreeSans.ttf")

# Display font files in projects view
FILE(GLOB_RECURSE FontFiles "*.ttf")
add_custom_target(fonts SOURCES ${FontFiles})
add_custom_target(LICENSE SOURCES LICENSE README.md)

