cmake_minimum_required(VERSION 3.15)
project(AutoCoder VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Options
option(BUILD_TESTS "Build tests" ON)
option(BUILD_INSTALLER "Build installer package" ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network WebSockets Gui)
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
    ${CMAKE_SOURCE_DIR}/include/core
    ${CMAKE_SOURCE_DIR}/include/ai_engine
    ${CMAKE_SOURCE_DIR}/include/debugger
    ${CMAKE_SOURCE_DIR}/include/chatbot
    ${CMAKE_SOURCE_DIR}/include/codegen
    ${CMAKE_SOURCE_DIR}/include/spellchecker
    ${CMAKE_SOURCE_DIR}/include/gui_maker
    ${CMAKE_SOURCE_DIR}/include/compiler
    ${CMAKE_SOURCE_DIR}/include/gui
)

# Core library
add_library(autocoder_core STATIC
    src/core/application.cpp
    src/core/config_manager.cpp
    src/core/logger.cpp
    src/core/plugin_manager.cpp
)

target_link_libraries(autocoder_core
    Qt6::Core
    Qt6::Widgets
)

# AI Engine library (DeepSeeker integration)
add_library(ai_engine STATIC
    src/ai_engine/deepseeker_client.cpp
    src/ai_engine/model_manager.cpp
    src/ai_engine/inference_engine.cpp
    src/ai_engine/self_improvement.cpp
)

target_link_libraries(ai_engine
    CURL::libcurl
    Qt6::Core
)

# Debugger library
add_library(debugger_engine STATIC
    src/debugger/continuous_debugger.cpp
    src/debugger/breakpoint_manager.cpp
    src/debugger/stack_tracer.cpp
    src/debugger/variable_inspector.cpp
)

# Chatbot library
add_library(chatbot STATIC
    src/chatbot/chat_interface.cpp
    src/chatbot/intent_parser.cpp
    src/chatbot/response_generator.cpp
)

# Code Generator library
add_library(codegen STATIC
    src/codegen/code_generator.cpp
    src/codegen/language_detector.cpp
    src/codegen/syntax_validator.cpp
    src/codegen/multi_language_support.cpp
)

# Spellchecker library
add_library(spellchecker STATIC
    src/spellchecker/enhanced_spellchecker.cpp
    src/spellchecker/dictionary_manager.cpp
    src/spellchecker/context_analyzer.cpp
)

# GUI Maker library
add_library(gui_maker STATIC
    src/gui_maker/gui_builder.cpp
    src/gui_maker/widget_library.cpp
    src/gui_maker/layout_manager.cpp
    src/gui_maker/code_exporter.cpp
)

# Compiler integration library
add_library(compiler STATIC
    src/compiler/compiler_interface.cpp
    src/compiler/gcc_wrapper.cpp
    src/compiler/clang_wrapper.cpp
    src/compiler/msvc_wrapper.cpp
    src/compiler/build_manager.cpp
)

# GUI library
add_library(gui STATIC
    src/gui/main_window.cpp
    src/gui/code_editor.cpp
    src/gui/chat_panel.cpp
    src/gui/debugger_panel.cpp
    src/gui/output_panel.cpp
    src/gui/settings_dialog.cpp
    src/gui/theme_manager.cpp
)

# Link Qt to GUI library
target_link_libraries(gui
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    Qt6::WebSockets
    Qt6::Gui
)

# Main executable
add_executable(autocoder
    src/main.cpp
)

# Link all libraries
target_link_libraries(autocoder
    autocoder_core
    ai_engine
    debugger_engine
    chatbot
    codegen
    spellchecker
    gui_maker
    compiler
    gui
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    Qt6::WebSockets
    OpenSSL::SSL
    OpenSSL::Crypto
    CURL::libcurl
)

# Platform-specific libraries
if(UNIX)
    target_link_libraries(autocoder pthread dl)
endif()

# Tests
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Installation
install(TARGETS autocoder DESTINATION bin)

# Install desktop file for Linux
if(UNIX AND NOT APPLE)
    install(FILES ${CMAKE_SOURCE_DIR}/resources/autocoder.desktop
            DESTINATION share/applications)
    install(FILES ${CMAKE_SOURCE_DIR}/resources/autocoder.svg
            DESTINATION share/pixmaps)
    install(FILES ${CMAKE_SOURCE_DIR}/resources/autocoder.svg
            DESTINATION share/icons/hicolor/scalable/apps)
endif()

# Install other resources
install(DIRECTORY resources/ DESTINATION share/autocoder
        PATTERN "*.desktop" EXCLUDE)

# CPack configuration for installer
if(BUILD_INSTALLER)
    include(InstallRequiredSystemLibraries)
    set(CPACK_PACKAGE_NAME "AutoCoder")
    set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
    set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Self-Improving AutoCoder with AI Integration")
    set(CPACK_PACKAGE_VENDOR "AutoCoder Team")
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
    set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

    # Platform-specific settings
    if(WIN32)
        set(CPACK_GENERATOR "NSIS")
        set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
        set(CPACK_NSIS_MODIFY_PATH ON)
    elseif(APPLE)
        set(CPACK_GENERATOR "DragNDrop")
    else()
        set(CPACK_GENERATOR "DEB;RPM")
        set(CPACK_DEBIAN_PACKAGE_MAINTAINER "AutoCoder Team")

        # Debian package settings
        set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
        set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
        set(CPACK_DEBIAN_PACKAGE_DEPENDS "qt6-base-gui, libqt6core6, libqt6widgets6, libqt6network6, libssl3 | libssl1.1, libcurl4")

        # Update desktop database after install/uninstall
        set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
            "${CMAKE_SOURCE_DIR}/packaging/postinst;${CMAKE_SOURCE_DIR}/packaging/postrm")

        # RPM package settings
        set(CPACK_RPM_PACKAGE_GROUP "Development/Tools")
        set(CPACK_RPM_PACKAGE_LICENSE "MIT")
        set(CPACK_RPM_PACKAGE_REQUIRES "qt6-qtbase >= 6.0, openssl-libs, libcurl")

        # RPM post-install scripts
        set(CPACK_RPM_POST_INSTALL_SCRIPT_FILE "${CMAKE_SOURCE_DIR}/packaging/postinst")
        set(CPACK_RPM_POST_UNINSTALL_SCRIPT_FILE "${CMAKE_SOURCE_DIR}/packaging/postrm")
    endif()

    include(CPack)
endif()
