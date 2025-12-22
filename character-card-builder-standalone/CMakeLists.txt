cmake_minimum_required(VERSION 3.15)
project(CharacterCardBuilder VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options
option(BUILD_INSTALLER "Build installer package" ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network Gui)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find OpenSSL for secure connections
find_package(OpenSSL REQUIRED)

# Find cURL for HTTP requests
find_package(CURL REQUIRED)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/character_card
)

# Character Card Builder library
add_library(character_card_lib STATIC
    src/character_card/card_data.cpp
    src/character_card/card_validator.cpp
    src/character_card/web_scraper.cpp
    src/character_card/card_importer.cpp
    src/character_card/character_builder_window.cpp
    src/character_card/basic_info_panel.cpp
    src/character_card/personality_panel.cpp
    src/character_card/memory_lore_panel.cpp
    src/character_card/dialogue_panel.cpp
    src/character_card/world_builder_panel.cpp
    src/character_card/portrait_panel.cpp
    src/character_card/export_dialog.cpp
    src/character_card/wizard_dialog.cpp
    src/character_card/preset_manager.cpp
)

# Link Qt to Character Card library
target_link_libraries(character_card_lib
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    Qt6::Gui
    CURL::libcurl
)

# Main executable
add_executable(character-card-builder
    src/main.cpp
)

# Link libraries
target_link_libraries(character-card-builder
    character_card_lib
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    OpenSSL::SSL
    OpenSSL::Crypto
    CURL::libcurl
    pthread
    dl
)

# Installation
install(TARGETS character-card-builder DESTINATION bin)
install(FILES CHARACTER_BUILDER.md DESTINATION share/character-card-builder)

# CPack configuration for installer
if(BUILD_INSTALLER)
    include(InstallRequiredSystemLibraries)
    set(CPACK_PACKAGE_NAME "CharacterCardBuilder")
    set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
    set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SillyTavern Character Card Builder")
    set(CPACK_PACKAGE_VENDOR "Character Card Builder Team")
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
    set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

    # Platform-specific settings
    if(WIN32)
        set(CPACK_GENERATOR "NSIS")
        set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
        set(CPACK_NSIS_MODIFY_PATH ON)
        set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/resources/icon.ico")
    elseif(APPLE)
        set(CPACK_GENERATOR "DragNDrop")
        set(CPACK_DMG_VOLUME_NAME "Character Card Builder")
    else()
        set(CPACK_GENERATOR "DEB;RPM")
        set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Character Card Builder Team")
        set(CPACK_DEBIAN_PACKAGE_DEPENDS "qt6-base, libcurl4, libssl3")
    endif()

    include(CPack)
endif()
