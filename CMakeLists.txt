#
# Copyright (C) 2020 Adrian Carpenter
#
# This file is part of the Nedrysoft Ribbon library. (https://github.com/nedrysoft/qt-ribbon)
#
# A cross-platform ribbon bar for Qt applications.
#
# Created by Adrian Carpenter on 02/12/2020.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

cmake_minimum_required(VERSION 3.21)

project(Ribbon
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include(cmake/get_cpm.cmake)

# ThemeSupport dependency — try an already-available target first, then CPM
set(RIBBON_THEMESUPPORT_GITHUB_REPO "nedrysoft/qt-themesupport"
    CACHE STRING "GitHub repository for ThemeSupport (owner/repo)")
set(RIBBON_THEMESUPPORT_GIT_TAG "main"
    CACHE STRING "Git tag/branch for ThemeSupport")

if(NOT TARGET ThemeSupport)
    find_package(ThemeSupport QUIET)
    if(NOT ThemeSupport_FOUND)
        CPMAddPackage(
            NAME ThemeSupport
            GITHUB_REPOSITORY "${RIBBON_THEMESUPPORT_GITHUB_REPO}"
            GIT_TAG "${RIBBON_THEMESUPPORT_GIT_TAG}"
        )
    endif()
endif()

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

set(library_SOURCES
    src/RibbonAction.h
    src/RibbonButton.cpp
    src/RibbonButton.h
    src/RibbonCheckBox.cpp
    src/RibbonCheckBox.h
    src/RibbonComboBox.cpp
    src/RibbonComboBox.h
    src/RibbonDropButton.cpp
    src/RibbonDropButton.h
    src/RibbonFontManager.cpp
    src/RibbonFontManager.h
    src/RibbonGroup.cpp
    src/RibbonGroup.h
    src/RibbonLineEdit.cpp
    src/RibbonLineEdit.h
    src/RibbonPushButton.cpp
    src/RibbonPushButton.h
    src/RibbonResources.qrc
    src/RibbonSlider.cpp
    src/RibbonSlider.h
    src/RibbonSpec.h
    src/RibbonTabBar.cpp
    src/RibbonTabBar.h
    src/RibbonToolButton.cpp
    src/RibbonToolButton.h
    src/RibbonWidget.cpp
    src/RibbonWidget.h
)

if(WIN32)
    configure_file("src/Version.h.in" "Version.h")
    list(APPEND library_SOURCES "src/version.rc")
    add_definitions("-DNEDRYSOFT_MODULE_FILENAME=\"Ribbon.dll\"")
    add_definitions("-DNEDRYSOFT_MODULE_NAME=\"Ribbon\"")
endif()

add_library(Ribbon SHARED ${library_SOURCES})
add_library(Ribbon::Ribbon ALIAS Ribbon)

target_compile_features(Ribbon PUBLIC cxx_std_20)

set_target_properties(Ribbon PROPERTIES
    CXX_EXTENSIONS OFF
)

target_compile_definitions(Ribbon PRIVATE
    QT_NO_KEYWORDS
    NEDRYSOFT_LIBRARY_RIBBON_EXPORT
)

target_include_directories(Ribbon
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Ribbon
    PUBLIC
        Qt6::Core
        Qt6::Widgets
    PRIVATE
        ThemeSupport
)

if(APPLE)
    target_link_libraries(Ribbon PRIVATE
        "-framework AppKit"
        "-framework Cocoa"
        stdc++
        objc
    )
endif()

if(DEFINED NEDRYSOFT_RIBBON_LIBRARY_DIR)
    set_target_properties(Ribbon PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${NEDRYSOFT_RIBBON_LIBRARY_DIR}"
        RUNTIME_OUTPUT_DIRECTORY "${NEDRYSOFT_RIBBON_LIBRARY_DIR}"
    )
endif()

# Designer plugin (optional)

option(NEDRYSOFT_RIBBON_BUILD_DESIGNER_PLUGIN "Build Ribbon QtDesigner Plugin" OFF)

if(NEDRYSOFT_RIBBON_BUILD_DESIGNER_PLUGIN)
    find_package(Qt6 COMPONENTS Widgets UiPlugin REQUIRED)

    add_library(RibbonDesigner SHARED
        ${library_SOURCES}
        src/RibbonButtonPlugin.cpp
        src/RibbonButtonPlugin.h
        src/RibbonCheckBoxPlugin.cpp
        src/RibbonCheckBoxPlugin.h
        src/RibbonComboBoxPlugin.cpp
        src/RibbonComboBoxPlugin.h
        src/RibbonDropButtonPlugin.cpp
        src/RibbonDropButtonPlugin.h
        src/RibbonGroupPlugin.cpp
        src/RibbonGroupPlugin.h
        src/RibbonLineEditPlugin.cpp
        src/RibbonLineEditPlugin.h
        src/RibbonPushButtonPlugin.cpp
        src/RibbonPushButtonPlugin.h
        src/RibbonSliderPlugin.cpp
        src/RibbonSliderPlugin.h
        src/RibbonToolButtonPlugin.cpp
        src/RibbonToolButtonPlugin.h
        src/RibbonWidgetsCollection.cpp
        src/RibbonWidgetsCollection.h
        src/RibbonWidgetPlugin.cpp
        src/RibbonWidgetPlugin.h
    )

    target_compile_features(RibbonDesigner PUBLIC cxx_std_20)

    set_target_properties(RibbonDesigner PROPERTIES
        CXX_EXTENSIONS OFF
    )

    target_compile_definitions(RibbonDesigner PRIVATE
        QT_NO_KEYWORDS
        NEDRYSOFT_LIBRARY_RIBBON_EXPORT
        NEDRYSOFT_RIBBON_DESIGNER_EXPORT
    )

    target_include_directories(RibbonDesigner PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

    target_link_libraries(RibbonDesigner PRIVATE
        Qt6::Widgets
        Qt6::UiPlugin
        ThemeSupport
    )

    if(APPLE)
        target_link_libraries(RibbonDesigner PRIVATE
            "-framework AppKit"
            "-framework Cocoa"
        )
    endif()

    if(DEFINED NEDRYSOFT_RIBBON_DESIGNER_DIR)
        file(MAKE_DIRECTORY ${NEDRYSOFT_RIBBON_DESIGNER_DIR})
        set_target_properties(RibbonDesigner PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY "${NEDRYSOFT_RIBBON_DESIGNER_DIR}"
            RUNTIME_OUTPUT_DIRECTORY "${NEDRYSOFT_RIBBON_DESIGNER_DIR}"
        )
    endif()
else()
    message(STATUS "Set NEDRYSOFT_RIBBON_BUILD_DESIGNER_PLUGIN=ON to build the designer plugin.")
endif()
