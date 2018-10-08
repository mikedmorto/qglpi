cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(QtCommon)
include(GetGitVersion)

# Set additional project information
set(COMPANY "MDM-service")
set(COPYRIGHT "Copyright (c) 2018 ${COMPANY}. All rights reserved.")
set(IDENTIFIER "org.konkordo.qglpi")

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)

# Getting our repository version
get_git_version(GIT_VERSION)
string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" VERSION ${GIT_VERSION})

configure_file(def.h.in ${CMAKE_CURRENT_BINARY_DIR}/def.h)

message("-- Version: ${VERSION}")
message("-- Company: ${COMPANY}")
message(STATUS "Generating build using CMake v${CMAKE_VERSION}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

include_directories(
    models
    ui
    inc
    inc/aqp
    obj)
# Get source files list
file(GLOB SRC_LIST
    *.cpp
    models/*.cpp
    ui/*.cpp
    inc/*.cpp
    obj/*.cpp
    inc/aqp/*.cpp
    )
# Get UI files list
file(GLOB UI_LIST
    ui/*.ui
    inc/*.ui
    )
file(GLOB H_LIST
    *.h
    models/*.h
    ui/*.h
    inc/*.h
    obj/*.h
    inc/aqp/*.hpp
    inc/aqp/*.h
    )

file(GLOB RC_LIST *.qrc)

add_project_meta(META_FILES_TO_INCLUDE)

add_executable(qglpi ${OS_BUNDLE} ${SRC_LIST}
    ${UI_LIST} ${H_LIST} ${RC_LIST}
    ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES}
    )
target_link_libraries(qglpi Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network)
